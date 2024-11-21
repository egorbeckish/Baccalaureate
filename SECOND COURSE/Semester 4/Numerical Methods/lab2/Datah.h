#ifndef INPUTDATA_H
#define INPUTDATA_H
#include <iostream>
#include <fstream>
#include <cmath>
#include "Matrix.h"
#include "Vector.h"
#define MAX_ITER 10000
#define EPS 0.00000001

namespace Base
{
    double invert_unit_matrix_initer(size_t m, size_t n, size_t r, size_t c);
    double unit_matrix_initer(size_t m, size_t n, size_t r, size_t c);
    double zero_matrix_initer(size_t m, size_t n, size_t r, size_t c);

    char getSymbol(std::initializer_list<char> list,
        std::string notification_message = "",
        std::string error_message = "Недопустимое значение, попробуйте ещё раз.\n->");

    double getDouble(double min = -DBL_MAX,
        double max = DBL_MAX,
        std::string notification_message = "",
        std::string error_message = "Недопустимое значение, попробуйте ещё раз.\n->");

    template <class T>
    class InputData
    {
    public:
        enum class METHOD
        {
            GAUSS = 1,
            DECOMPOSOTION,
            SIMPLEITERATION,
            SEIDEL
        };

        enum class TASK
        {
            ROOT = 1,
            DETERMINANT,
            INVERS
        };

    private:

        std::ofstream* _fout;
        // основные данные
        Matrix<T>* _expandedMatrix;
        Matrix<T>* _inverseMatrix;
        Matrix<T>* A;
        Vector<T>* b;
        Vector<T>* x;
        int m; // размерность квадратной матрицы
        int eps;

        // проверка и точность
        Vector<T>* ResidualVector;
        Matrix<T>* ResidualMatrix;

        METHOD _method;
        TASK _task;
        T _determinant = 0;

        int _NAfterComma;
    public:


        InputData()
        {
            std::ifstream* _fin = new std::ifstream("input.txt");
            _fout = new std::ofstream("output.txt");
            int c;
            *_fin >> c; // считывается метод
            _method = static_cast<METHOD>(c);
            *_fin >> c; // считывается тип задачи
            _task = static_cast<TASK>(c);


            *_fin >> m;

            std::cout << "\n\tПорядок матрицы: " << m;

            T* array = new T[m * (m + 1)];
            for (int i = 0; i < (m + 1) * m; i++)
                *_fin >> array[i];

            delete _fin;

            _expandedMatrix = new Matrix<T>(m, m + 1, array);
            _inverseMatrix = new Matrix<T>(m);
            delete[] array;
            std::cout << "\n\tКоэффициенты считанной матрицы и вектор свободных коэффициентов (последний стоблик):\n\n" << *_expandedMatrix;
            setA(*_expandedMatrix, m);
            setB(*_expandedMatrix, m);
            x = new Vector<T>(m);
            (*x).transposition();

            ResidualVector = new Vector<T>(m);
            (*ResidualVector).transposition();
            ResidualMatrix = new Matrix<T>(m);
        }

        InputData(const Matrix<T>& matrix, std::ofstream* out)
        {
            m = matrix.getRows();
            A = new Matrix<T>(m);
            *A = matrix;

            _inverseMatrix = new Matrix<T>(m);
            ResidualMatrix = new Matrix<T>(m);
            _fout = out;
        }


        METHOD getMethod() { return _method; }
        TASK getTask() { return _task; }

        // инициализация квадратной матрицы
        void setA(const Matrix<T>& matrix, size_t size)
        {
            A = new Matrix<T>(size);
            for (int i = 0; i < size; i++)
                for (int j = 0; j < size; j++)
                    (*A)[i][j] = matrix[i][j];
        }

        // инициализация вектора свободных коэффициентов - initialization of the vector of free coefficients
        void setB(const Matrix<T>& matrix, size_t size) // size - number of rows 
        {
            b = new Vector<T>(size);
            for (int i = 0; i < size; i++)
                (*b)[i] = matrix[i][size];
            (*b).transposition();
        }

        ~InputData()
        {
            delete _expandedMatrix;
            delete _inverseMatrix;
            delete A;
            delete x;
            delete b;
            delete ResidualVector;
            delete ResidualMatrix;
            delete _fout;
        }


        Matrix<T>& getExpandedMatrix() { return *_expandedMatrix; }

        //вектор невязки
        void setResidualVector(const Matrix<T>& _A, const Vector<T>& _x, const Vector<T>& _b)
        {
            *_fout << "\nВектор невязки e*:\n" << (_A * _x) - _b;
            (*ResidualVector) = (_A * _x) - _b;
        }

        const Matrix<T>& getInverseMatrix() const { return *_inverseMatrix; }
        const Matrix<T>& getMainMatrix() const { return *A; }

        void setInverseMatrixByMethod(Vector<T>(*Method)(const Matrix<T>&, const Vector<T>&, T& determinant, std::ofstream&))
        {
            Vector<Vector<T>> x_temp(m);
            Vector<Vector<T>> E(m);
            for (int i = 0; i < m; i++)
            {
                E[i] = Vector<T>(m);
                for (int j = 0; j < m; j++)
                    if (i == j)
                        E[i][j] = 1;
                    else
                        E[i][j] = 0;
                E[i].transposition();
            }

            for (int i = 0; i < m; i++)
            {
                x_temp[i] = Method(*A, E[i], _determinant, *_fout);
                std::cout << "\nx'[" << i << "]=\n" << x_temp[i];
            }
            for (int i = 0; i < m; i++)
                for (int j = 0; j < m; j++)
                    (*_inverseMatrix)[i][j] = x_temp[j][i];
            *_fout << "\nОбратная матрица:\n" << std::setw(10) << (*_inverseMatrix);

            *ResidualMatrix = (*_inverseMatrix) * (*A) - Matrix<double>(m, unit_matrix_initer);
            *_fout << "\nМатрица невязки:\n" << std::setprecision(5) << std::setw(15) << *ResidualMatrix;
            *_fout << "\nЕвклидова норма матрицы невязки: " << (*ResidualMatrix).getModule() << "\n";

        }

        void setRoot(Vector<T>(*Method)(const Matrix<T>&, const Vector<T>&, T& determinant, std::ofstream&))
        {
            (*x) = Method(*A, *b, _determinant, *_fout);
        }

        void getRoot(Vector<T>(*Method)(const Matrix<T>&, const Vector<T>&, T& determinant, std::ofstream&))
        {
            if (Method == InputData::GaussMethod)
                *_fout << "\nМетод Гаусса:\n";
            else if (Method == InputData::DecompositionMethod)
                *_fout << "\nМетод ДЕКОМПОЗИЦИИ:\n";
            else if (Method == InputData::SimpleIterationMethod)
                *_fout << "\nМетод Простой Итерации\n";
            else if (Method == InputData::SeidelMethod)
                *_fout << "\nМетод Зейделя\n";

            setRoot(Method);
            *_fout << "\nРезультат:\n" << (*x);
            setResidualVector(*A, *x, *b);
            *_fout << "\nЕвклидова норма вектора невязки: " << (*ResidualVector).getModule() << "\n";
        }

        T getDeterminant()
        {
            if (_determinant == 0)
            {
                switch (_method)
                {
                case METHOD::GAUSS:
                    setRoot(InputData::GaussMethod);
                    break;
                case METHOD::DECOMPOSOTION:
                    setRoot(InputData::DecompositionMethod);
                    break;
                case METHOD::SIMPLEITERATION:
                    setRoot(InputData::SimpleIterationMethod);
                    break;
                }
            }
            *_fout << "\nОпределитель: " << _determinant << "\n";
            return _determinant;
        }


        static Vector<T> GaussMethod(const Matrix<T>& A, const Vector<T>& b, T& determinant, std::ofstream& out = std::cout)
        {
            Matrix<T> expandedMatrix(A.getRows(), A.getCols() + 1);
            for (int i = 0; i < expandedMatrix.getRows(); i++)
                for (int j = 0; j < expandedMatrix.getCols(); j++)
                    if (j == expandedMatrix.getCols() - 1)
                        expandedMatrix[i][j] = b[i];
                    else
                        expandedMatrix[i][j] = A[i][j];
            return GaussMethod(expandedMatrix, determinant, out);
        }

        static Vector<T> GaussMethod(const Matrix<T>& expandedMatrix, T& determinant, std::ofstream& out = std::cout)
        {
            // удобнее использовать расширенную матрицу, поэтому зафиксируем её
            Matrix<T> tempMatrix(expandedMatrix);
            determinant = 1;
            // Прямой ход метода Гаусса - преобразование матрицы к треугольному виду
            for (int i = 0; i < tempMatrix.getRows(); i++) // проходим по всем строкам
            {
                out << "i = " << i << "\n" << std::setw(10) << tempMatrix << "\n";
                T coeff = tempMatrix[i][i]; // запоминаем коэффициент по диагонали
                determinant *= coeff;

                for (int j = i; j < tempMatrix.getRows() + 1; j++) // проходим по всем элементам текущей строки, включая вектор коэффициентов
                {
                    // если это элемент на диагонали, то он вырождается в единицу, 
                    // а если любой другой на текущей строке, то просто делится на этот коэффициент
                    tempMatrix[i][j] /= coeff;
                }
                out << '\n' << std::setw(10) << tempMatrix;
                for (int j = i + 1; j < tempMatrix.getRows(); j++)
                {
                    coeff = tempMatrix[j][i]; // запоминаем коэффициент умножения 
                    for (int k = i; k < tempMatrix.getCols(); k++) // проходим по всем элементам строки, некоторые элементы которой будут обнуляться
                        tempMatrix[j][k] -= coeff * tempMatrix[i][k]; // вычитаем из текущей строки верхнюю i-ю строку помноженную на coeff
                    // в результате получим некоторое количество нулей под единицей

                }
            }

            Vector<T> result(tempMatrix.getRows());
            result.transposition();
            // Обратный ход метода Гаусса
            for (int i = result.getLength() - 1; i >= 0; i--)
            {
                T sumCoeff = 0;
                for (int j = i + 1; j < result.getLength(); j++)
                    sumCoeff += tempMatrix[i][j] * result[j];

                result[i] = tempMatrix[i][result.getLength()] - sumCoeff;
            }
            return result;
        }


        static Vector<T> DecompositionMethod(const Matrix<T>& A, const Vector<T>& b, T& determinant, std::ofstream& out = std::cout)
        {
            // Раскладываем матрицу _matrix на матрицы B и C так, что A = B * C
            Matrix<T> B(A.getRows(), unit_matrix_initer);
            Matrix<T> C(A.getRows(), unit_matrix_initer);
            std::cout << "A: \n" << B << "\nB:\n" << C << "\n";
            unsigned m = B.getRows();
            for (int j = 0; j < m; j++)
            {

                for (int i = j; i < m; i++)// проходим по элементам столбца матрицы B
                {
                    T sumCoeff = 0;
                    for (int k = 0; k <= j - 1; k++)
                        sumCoeff += B[i][k] * C[k][j];

                    B[i][j] = A[i][j] - sumCoeff;
                }
                for (int i = j + 1; i < m; i++)
                {
                    T sumCoeff = 0;
                    for (int k = 0; k <= j - 1; k++)
                        sumCoeff += B[j][k] * C[k][i];
                    C[j][i] = (1 / B[j][j]) * (A[j][i] - sumCoeff);
                }
                out << "\n\ti = " << j << "\n\tМатрица A : \n" << std::setprecision(5) << std::setw(15) << B << "\n\tМатрица B : \n" << std::setw(15) << C;
            }
            Vector<T> y(m);
            determinant = 1;
            for (int i = 0; i < m; i++)
            {
                T sumCoeff = 0;
                for (int k = 0; k <= i - 1; k++)
                    sumCoeff += B[i][k] * y[k];
                y[i] = (b[i] - sumCoeff) / B[i][i];
                determinant *= B[i][i];
            }
            out << "\ny' = \n" << y.transposition() << "\n";
            Vector<T> x(m);
            for (int i = m - 1; i >= 0; i--)
            {
                T sumCoeff = 0;
                for (int k = i + 1; k < m; k++)
                    sumCoeff += C[i][k] * x[k];
                x[i] = y[i] - sumCoeff;
            }
            x.transposition();
            return x;
        }


        static bool converge(const Matrix<T>& A, std::ofstream& out = std::cout)
        {
            int n = A.getCols();
            double sum = 0;
            for (int i = 0; i < n; i++)
            {
                sum = 0;
                for (int j = 0; j < n; j++)
                    if (i != j)
                        sum += A[i][j];
                if (abs(A[i][i]) <= abs(sum))
                {
                    out << "\n\tНеобходимость не выполняется\n";
                    return false;
                }
            }
            return true;
        }


        static Vector<T> SimpleIterationMethod(const Matrix<T>& A, const Vector<T>& B, T& determinant, std::ofstream& out = std::cout)
        {
            int m = A.getRows();
            Matrix<double> a(m);
            Vector<double> b(m);
            b.transposition();

            if (!converge(A, out))
                return B;

            Vector<double> x0(b);
            x0.transposition();
            Vector<double> x1(b);
            x1.transposition();

            for (int i = 0; i < m; i++)
            {
                b[i] = B[i] / A[i][i];
                for (int j = 0; j < m; j++)
                    if (i == j)
                        a[i][j] = 0;
                    else
                        a[i][j] = -A[i][j] / A[i][i];
            }
            out << "\nb=\n" << std::setw(10) << b << "\na=\n" << std::setw(10) << a;
            x0 = b;
            x1 = x0;
            do
            {
                x0 = x1;
                x1 = b + a * x1;
            } while ((x1 - x0).getModule() >= abs((1 - a.getModule()) / a.getModule()));
            return x1;
        }

        static Vector<T> SeidelMethod(const Matrix<T>& A, const Vector<T>& B, T& determinant, std::ofstream& out = std::cout)
        {
            int m = A.getRows();
            Matrix<T> a0(A);
            Vector<T> b0(B);

            if (!converge(A, out))
            {
                out << "\nПреобразуем матрицу к симметрично положительно определённой.";
                Matrix<T> a_T(a0.transposition());
                out << "\na^T:\n" << a_T;
                a0 = a_T * a0;
                out << "\n a^T * a = \n" << a0;
                b0 = a_T * b0;
                out << "\n a^T * b = \n" << b0;
            }

            Vector<double> x0(b0);
            x0.transposition();
            Vector<double> x1(b0);
            x1.transposition();

            Matrix<T> a(A);
            Vector<T> b(B);
            for (int i = 0; i < m; i++)
            {
                b[i] = b0[i] / a0[i][i];
                for (int j = 0; j < m; j++)
                    if (i == j)
                        a[i][j] = 0;
                    else
                        a[i][j] = -a0[i][j] / a0[i][i];
            }
            out << "\nb=\n" << std::setprecision(7) << std::setw(10) << b << "\na=\n" << std::setw(10) << a;
            x0 = b;
            x1 = x0;
            unsigned count = 0;
            do
            {
                x0 = x1;
                for (int i = 0; i < m; i++)
                {
                    double sum1 = 0;
                    for (int j = 0; j < i; j++)
                        sum1 += a[i][j] * x1[j];
                    double sum2 = 0;
                    for (int j = i + 1; j < m; j++)
                        sum2 += a[i][j] * x0[j];
                    x1[i] = b[i] + sum1 + sum2;
                }
                count++;
            } while ((x1 - x0).getModule() >= abs((1 - a.getModule()) / a.getModule() * EPS));
            return x1;
        }
    };
}
#endif