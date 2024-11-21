#ifndef EIGENVALUE_H
#define EIGENVALUE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


#include "Matrix.h"
#include "Vector.h"
#include "Fraction.h"
#include "Polynomial.h"
#include "PolStr.h"

#define EPS_B 1E-1
#define EPS 1E-4
#define MAX 31

namespace Math
{
    double unit_matrix_initer(size_t m, size_t n, size_t r, size_t c)
    {
        return r == c;
    }
    double zero_vector_initer(double m, double n)
    {
        return 0;
    }

    template<class T>
    class Eigenvalue
    {
    public:
        enum class TASK
        {
            EIGENVALUES = 1,
            EIGENVECTORS,
            ROOTS
        };
    private:
        TASK _task;
        int        m;           // размерность квадратной матрицы
        Matrix<T>* A;           // исходная матрица
        Matrix<T>* P;           // матрица Фробениуса
        Matrix<T>* S;           // вспомогательная матрица при вычислении матрицы Фробениуса
        Vector<T>* x;           // собственные вектора 
        Vector<T>* eigenvalues; // собственные числа
        std::vector<T> k;       // кратность собственных чисел/векторов
        std::ofstream* _fout;

    public:

        Eigenvalue()
        {
            std::ifstream _fin("input.txt");
            _fout = new std::ofstream("output.txt");
            int c;
            _fin >> c; // считывается тип задачи
            _task = static_cast<TASK>(c);

            _fin >> m;

            T* array = new T[m * m];
            for (int i = 0; i < m * m; i++)
                _fin >> array[i];
            _fin.close();

            A = new Matrix<T>(m, array);
            delete[] array;
            P = new Matrix<T>(m);

            x = new Vector<T>[m];
            for (int i = 0; i < m; i++)
                x[i] = Vector<T>(m);
            eigenvalues = new Vector<T>(m);
            S = new Matrix<T>(m, unit_matrix_initer);

        }

        ~Eigenvalue()
        {
            delete A;
            delete P;
            delete[] x;
            delete eigenvalues;
            delete S;
        }

        TASK getTask() { return _task; }

        static T getDeterminant(const Matrix<T>& _Matrix) // Через метод Гаусса
        {
            Matrix<T> A(_Matrix);
            T determinant = 1;
            // Прямой ход метода Гаусса - преобразование матрицы к треугольному виду
            for (int i = 0; i < A.getRows(); i++) // проходим по всем строкам
            {
                T coeff = A[i][i]; // запоминаем коэффициент по диагонали
                determinant *= coeff;
                for (int j = i; j < A.getRows(); j++) // проходим по всем элементам текущей строки, включая вектор коэффициентов
                    A[i][j] /= coeff;
                for (int j = i + 1; j < A.getRows(); j++)
                {
                    coeff = A[j][i];
                    for (int k = i; k < A.getCols(); k++)
                        A[j][k] -= coeff * A[i][k];
                }
            }
            return determinant;
        }

        // Получение собственных чисел методом Данилевского
        Vector<T> getEigenvalues()
        {
            *_fout << "\t\tМетод Данилевского для нахождения собственных чисел.\n";
            *P = GetFrobenius();
            *_fout << "\n\tМатрица Фробениуса:\n" << std::setw(10) << *P;

            int sign = (m % 2 == 0) ? 1 : -1;

            Fraction<int>* item = new Fraction<int>[m + 1];
            item[m] = sign;
            for (int i = m - 1; i >= 0; i--)
                item[i] = sign * -(*P)[0][m - i - 1];
            Polynomial<Fraction<int>> pol(m + 1, item);
            delete[] item;

            *_fout << "\n\tПолученный полином:\t" << pol;
            std::string ss = pol.to_string();
            const char* polStr = CreatePolStr(ss.c_str(), 0);

            if (GetError() == ERR_OK && polStr)
            {
                int n = 0;     // номер корня
                double x0 = 0; // Начальное приближение
                double x1 = x0;
                bool flag = false; // было ли на предыдущей итерации найдено приближение корня в промежутке (-EPS, EPS)
                T root1 = EvalPolStr(polStr, x0, 0);
                T root2 = root1;
                for (x1 = EPS; n < m && x1 < MAX; x1 += EPS)
                {
                    root1 = root2;
                    root2 = EvalPolStr(polStr, x1, 0);
                    if (abs(root2) <= EPS_B && abs(root2) < abs(root1))
                    {
                        x0 = x1;
                        flag = true;
                    }
                    else if (flag == true || root1 * root2 < 0)
                    {
                        int multiplicity = 0;
                        flag = false;
                        (*eigenvalues)[n] = x0;
                        multiplicity++; n++;
                        double eps_b = EPS_B;
                        while (abs(EvalPolStr(polStr, x0, multiplicity)) < eps_b)
                        {
                            multiplicity++;
                            eps_b *= 10;
                        }
                        for (int i = 0; i < multiplicity - 1; i++)
                            (*eigenvalues)[n++] = x0;
                    }
                }
                for (x1 = EPS; n < m && x1 > -MAX; x1 -= EPS)
                {
                    root1 = root2;
                    root2 = EvalPolStr(polStr, x1, 0);
                    if (abs(root2) <= EPS_B && abs(root2) < abs(root1))
                    {
                        x0 = x1;
                        flag = true;
                    }
                    else if (flag == true)
                    {
                        int multiplicity = 0;
                        flag = false;
                        (*eigenvalues)[n] = x0;
                        multiplicity++; n++;
                        double eps_b = EPS_B;
                        while (abs(EvalPolStr(polStr, x0, multiplicity)) < eps_b)
                        {
                            multiplicity++;
                            eps_b *= 10;
                        }
                        for (int i = 0; i < multiplicity - 1; i++)
                            (*eigenvalues)[n++] = x0;
                    }
                }
                delete polStr;
                n = 1;
                int _k;
                int i;
                Matrix<T> E(m, unit_matrix_initer);
                for (i = 1; i < m; i++)
                {
                    _k = 1;
                    if ((*eigenvalues)[i] == (*eigenvalues)[i - 1])
                        _k++;
                    else
                    {
                        *_fout << "\n\tСобственное число #" << n++ << ": " << (*eigenvalues)[i - 1] << "\n\t-> Кратность: " << _k;
                        k.push_back(_k);
                        *_fout << "\n\tПроверка: " << getDeterminant(((*A) - E * (*eigenvalues)[i - 1]));
                        _k = 1;
                    }
                }
                *_fout << "\n\n\tСобственное число #" << n << ": " << (*eigenvalues)[i - 1] << "\n\t-> Кратность: " << _k;
                k.push_back(_k);
                *_fout << "\n\tПроверка: " << getDeterminant(((*A) - E * (*eigenvalues)[i - 1])) << "\n";
            }
            return (*eigenvalues);
        }

        // Получение собственных векторов методом Данилевского 
        Vector<T>* getEigenvectors()
        {
            Vector<T>* y = new Vector<T>[m];
            for (int i = 0; i < m; i++)
            {
                y[i] = Vector<T>(m);
                // Находим собственные вектора для матрицы Фробениуса
                for (int j = m - 1; j >= 0; j--)
                    y[i][j] = pow((*eigenvalues)[i], m - j - 1);
                y[i].transposition();
                // Вычисляем собственные вектора исходной матрицы
                x[i] = (*S) * y[i];
            }
            delete[] y;
            int index = 0;
            for (int i = 0; i < m; i += k[index++])
            {
                *_fout << "\n\tСобственное число #" << index + 1 << " : " << (*eigenvalues)[i] << "\n\t-> Кратность: " << k[index]
                    << "\n\tСоответствующий собственный вектор:\n" << x[i];
                *_fout << "\nПроверка:\n" << (*A) * x[i] - (*eigenvalues)[i] * x[i];
            }
            return x;
        }

        Matrix<T> GetRoots()
        {
            std::ifstream _fin("input2.txt");
            int n;
            double _k;
            _fin >> n;
            m = 0;
            delete eigenvalues;
            eigenvalues = new Vector<T>(n);
            k.clear();
            for (int i = 0; i < n; i++)
            {
                _fin >> (*eigenvalues)[i] >> _k;
                k.push_back(_k);
                m += _k;
            }
            Polynomial<T> pol({ 1 });
            std::string ss = "";
            for (int i = 0; i < n; i++)
            {
                *_fout << "\n\tСобственное число #" << i + 1 << ": " << (*eigenvalues)[i] << "\n\t-> Кратность: " << k[i] << "\n";
                Polynomial<T> temp_pol({ -(*eigenvalues)[i], 1 });
                pol *= temp_pol;

                for (int j = 1; j < k[i]; j++)
                {
                    temp_pol = Polynomial<T>({ -(*eigenvalues)[i], 1 });
                    pol *= temp_pol;
                }
            }
            int sign;
            if (pol[m] < 0)
                sign = (m % 2 == 0) ? 1 : -1;
            else
                sign = ((m + 1) % 2 == 0) ? 1 : -1;

            Matrix<T> F(m, zero_vector_initer);
            for (int i = 0; i < m; i++)
            {
                F[0][i] = sign * -pol[m - i - 1];
                if (i < m - 1)
                    F[i + 1][i] = 1;
            }
            *_fout << "\n\tПолученная матрица Фробениуса:\n" << std::setw(10) << F;
            return F;
        }

        Matrix<T> GetFrobenius()
        {
            Matrix<T> P(*A);
            Matrix<T> tempA(*A);
            Matrix<T> M(m), M_1(m);
            Matrix<T> E(m, unit_matrix_initer);
            for (int k = m - 1; k >= 0; k--)
            {
                // Вычисляем M(k)
                for (int i = 0; i < m; i++)
                    for (int j = 0; j < m; j++)
                    {
                        if (i == (k - 1) && j == (k - 1)) // m(k,k) = 1 / a^(n-k-1)_(k+1,k)
                            M[i][j] = 1 / tempA[k][k - 1];
                        else if (i == (k - 1)) // m(k,j) = -a^(n-k-1)_(k+1,j) / a^(n-k-1)_(k+1,k); j = 1,2,...,n; j != k
                            M[i][j] = -tempA[k][j] / tempA[k][k - 1];
                        else //m(i,j) = e(i,j); i = 1,2,...,n; j = 1,2,...,n; i!=k
                            M[i][j] = E[i][j];
                    }
                P *= M; // ~A^k = A^(k-1) * M_(n-k)
                (*S) *= M;

                // Вычисляем M^-1(k)
                for (int i = 0; i < m; i++)
                    for (int j = 0; j < m; j++)
                    {
                        if (i == (k - 1)) // m(k,j) = a^(n-k-1)_(k+1,j); j = 1,2,...,n
                            M_1[i][j] = tempA[k][j];
                        else //m(i,j) = e(i,j); i = 1,2,...,n; j = 1,2,...,n; i!=k
                            M_1[i][j] = E[i][j];
                    }
                P = M_1 * P; // A^k = M^(-1)_(n-k) * ~A^k 
                tempA = P;
            }
            return P;
        }
    };
}
#endif