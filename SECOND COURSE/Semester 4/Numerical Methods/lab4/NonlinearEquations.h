#pragma once
#include <fstream>
#include <string>
#include <iomanip>

#include "Matrix.h"
#include "Vector.h"
#include "PolStr.h"

#define MAX_ITER 100000

namespace Math
{
    template<class T>
    class NonlinearEquations
    {
    public:
        enum class METHOD
        {
            NEWTON = 1,
            STEEPESTDESCENT,
        };
    private:
        METHOD              _method; // Требуемый метод решения СНУ
        int                 n;       // Размерность СНУ
        Vector<T>           x0;      // Начальное приближение
        T                   eps;     // Требуемая погрешность решения
        Vector<std::string> FunSys;  // Система функций
        std::ofstream       _fout;   // Выходной файл
    public:

        NonlinearEquations()
        {

            std::ifstream _fin("input.txt");
            _fout = std::ofstream("output.txt");
            T c;
            _fin >> c >> n;
            _method = static_cast<METHOD>(c);
            x0 = Vector<T>(n);
            x0.transposition();
            for (int i = 0; i < n; i++)
            {
                _fin >> c;
                x0[i] = c;
            }
            _fin >> eps;
            FunSys = Vector<std::string>(n);

            _fin.seekg(2, std::ios_base::cur);
            for (int i = 0; i < n; i++)
                getline(_fin, FunSys[i]);

            FunSys.transposition();
            _fout << "\n\tСистема Нелинейных Уравнений:\n" << std::setw(5) << FunSys << '\n';
            _fin.close();
        }
        ~NonlinearEquations()
        {
            _fout.close();
        }

        METHOD getMethod() { return _method; }

        static Vector<T> GaussMethod(const Matrix<T>& A, const Vector<T>& b)
        {
            Matrix<T> expandedMatrix(A.getRows(), A.getCols() + 1);
            for (int i = 0; i < expandedMatrix.getRows(); i++)
                for (int j = 0; j < expandedMatrix.getCols(); j++)
                    if (j == expandedMatrix.getCols() - 1)
                        expandedMatrix[i][j] = b[i];
                    else
                        expandedMatrix[i][j] = A[i][j];
            return GaussMethod(expandedMatrix);
        }

        static Vector<T> GaussMethod(const Matrix<T>& expandedMatrix)
        {
            Matrix<T> tempMatrix(expandedMatrix);

            for (int i = 0; i < tempMatrix.getRows(); i++)
            {
                T coeff = tempMatrix[i][i];
                for (int j = i; j < tempMatrix.getRows() + 1; j++)
                    tempMatrix[i][j] /= coeff;

                for (int j = i + 1; j < tempMatrix.getRows(); j++)
                {
                    coeff = tempMatrix[j][i];
                    for (int k = i; k < tempMatrix.getCols(); k++)
                        tempMatrix[j][k] -= coeff * tempMatrix[i][k];
                }
            }

            Vector<T> result(tempMatrix.getRows());
            result.transposition();

            for (int i = result.getLength() - 1; i >= 0; i--)
            {
                T sumCoeff = 0;
                for (int j = i + 1; j < result.getLength(); j++)
                    sumCoeff += tempMatrix[i][j] * result[j];

                result[i] = tempMatrix[i][result.getLength()] - sumCoeff;
            }
            return result;
        }

        static Matrix<T> getInverseMatrixByMethod(Vector<T>(*Method)(const Matrix<T>&, const Vector<T>&), Matrix<T> matrix)
        {
            int m = matrix.getCols();
            Matrix<T> inverseMatrix(m);
            Vector<Vector<T>> x_temp(m);
            Vector<Vector<T>> E(m);
            for (int i = 0; i < m; i++)
            {
                E[i] = Vector<T>(m);
                E[i][i] = 1;
                E[i].transposition();
            }

            for (int i = 0; i < m; i++)
                x_temp[i] = Method(matrix, E[i]);

            for (int i = 0; i < m; i++)
                for (int j = 0; j < m; j++)
                    inverseMatrix[i][j] = x_temp[j][i];

            return inverseMatrix;
        }

        static Matrix<T>* getJacobi(Vector<std::string> FunSys, Vector<T> x)
        {
            int n = x.getLength();
            Matrix<T>* J = new Matrix<T>(n);
            for (int i = 0; i < n; i++)
            {
                const char* polStr = CreatePolStr(FunSys[i].c_str(), n);
                if (GetError() == ERR_OK)
                    for (int j = 0; j < n; j++)
                    {
                        const double* x_p = x.getPointer();
                        (*J)[i][j] = EvalPolStr(polStr, x_p, 1, j + 1);
                        if (isnan((*J)[i][j]))   return NULL;
                    }
                else std::cerr << "Error: " << GetError();
            }
            return J;
        }

        // Вектор-столбец значений системы функций при заданных аргументах
        static Vector<T> getFunctionValues(Vector<std::string> FunSys, Vector<T> arg)
        {
            int n = FunSys.getLength();
            Vector<T> f_x(n);
            f_x.transposition();
            for (int i = 0; i < n; i++)
            {
                const char* polStr = CreatePolStr(FunSys[i].c_str(), n);
                if (GetError() == ERR_OK)
                {
                    const double* arg_p = arg.getPointer();
                    f_x[i] = EvalPolStr(polStr, arg_p);
                }
                else std::cerr << "Error: " << GetError();
            }
            return f_x;
        }

        // Вектор столбец направления градиента 
        // при заданной матрице Якоби, вектор-столбце значений системы функций при текущем приближении и сам вектол-столбец аргументов приближения
        static Vector<T> getGradientDirection(const Matrix<T>& Jacobi, const Vector<T>& FunctionValues, const Vector<T>& x0)
        {
            Matrix<T> Jacobi_T(Jacobi);
            Jacobi_T.transposition();
            return 2 * Jacobi_T * x0;
        }

        // Поиск параметра 'lambda'
        static const T& getMinimizingValue(const Matrix<T>& Jacobi, const Vector<T>& FunctionValues, const Vector<T>& x0)
        {
            Matrix<T> Jacobi_T(Jacobi);
            Jacobi_T.transposition();
            Vector<T> g(Jacobi_T * FunctionValues);
            Vector<T> g_T(g);
            g_T.transposition();
            return *((g_T * g).getPointer())
                / *((2 * g_T * Jacobi_T * Jacobi * g).getPointer());
        }

        // Метод Ньютона (модицицированный)
        Vector<T> Newton()
        {
            _fout << "\n\tМетод Ньютона:\n\t";
            Vector<T> x1(x0);
            int index = 0;
            _fout << "x^[" << index << "]:\n" << x1 << "\n";

            Matrix<T>* J = new Matrix<T>(n), * tempJ;
            bool flag = true;
            do {
                index++;
                x0 = x1;
                if (flag)
                {
                    tempJ = getJacobi(FunSys, x0);
                    if (tempJ) J = tempJ;
                    else       flag = false;
                }
                x1 = x0
                    - getInverseMatrixByMethod(NonlinearEquations::GaussMethod, *J)
                    * getFunctionValues(FunSys, x0);
                _fout.width(10);
                printIter(_fout, x1, index);

            } while ((x1 - x0).getModule() >= eps && index < MAX_ITER);
            delete[] J, tempJ;
            return x1;
        }

        // Метод Наискорейшего спуска
        Vector<T> SteepestDescent()
        {
            _fout << "\n\tМетод Наискорейшего спуска:\n\t";

            Vector<T> x1(x0), f_x;
            int index = 0;
            _fout << "x^[" << index << "]:\n" << x1 << "\n";

            Matrix<T>* J = new Matrix<T>(n), * tempJ;
            bool flag = true;
            do {
                index++;
                x0 = x1;
                if (flag)
                {
                    tempJ = getJacobi(FunSys, x0);
                    if (tempJ) J = tempJ;
                    else       flag = false;
                }
                f_x = Vector<T>(getFunctionValues(FunSys, x0));
                x1 = x0
                    - getMinimizingValue(*J, f_x, x0)
                    * getGradientDirection(*J, f_x, x0);
                _fout.width(10);
                printIter(_fout, x1, index);

            } while ((x1 - x0).getModule() >= eps && index < MAX_ITER);
            delete J, tempJ;
            return x1;
        }


        std::ostream& printIter(std::ostream& out, const Vector<T>& x1, int index)
        {
            std::streamsize width = out.width(), precision = out.precision();
            if (!width) width = 5;

            out << "\tx^[" << index << "]:\n" << std::setw(width) << std::setprecision(precision) << x1
                << "\t\t\t\t\t\t\tПогрешность \n\tВектор невязки:\n"
                << std::setw(width) << std::setprecision(precision) << (x1 - x0)
                << "\tНорма вектора невязки:\t"
                << (x1 - x0).getModule() << "\n_\t_\t_\t_\t_\t_\t_\t_\t_\t_\t_\t\n\n";
            return out;
        }

    };
}