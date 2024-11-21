#pragma once

#include "Base.h"

namespace Base
{
    template <class T> class Matrix
        : virtual public Base<T>
    {
    private:
        template <class T> class Row
        {
        private:
            T* r_row;
            unsigned r_cols;
            std::string r_id;
        public:
            Row(unsigned cols, T* row, std::string id)
                : r_row(row), r_cols(cols), r_id(id) { }

            T& operator[](int col)
            {
                if (col >= static_cast<int>(r_cols) || static_cast<int>(r_cols) + col < 0)
                    throw std::out_of_range("Номер строки выходит за пределы матрицы №" + r_id + '\n');
                else if (col < 0)
                    col = r_cols + col;
                return  r_row[col];
            }

            const T& operator[](int col) const
            {
                if (col >= static_cast<int>(r_cols) || static_cast<int>(r_cols) + col < 0)
                    throw std::out_of_range("Номер строки выходит за пределы матрицы №" + r_id + '\n');
                else if (col < 0)
                    col = r_cols + col;
                return  r_row[col];
            }
        };
    public:
        using Base<T>::m_rows;
        using Base<T>::m_cols;
        using Base<T>::m_item;
        using Base<T>::m_id;

        Matrix() : Base<T>()
        {
            //std::cout << "Конструктор #1 -> Матрица №" << m_id << std::endl;
        }
        explicit Matrix(int rows, int cols, const T* array = NULL)
            : Base<T>(rows, cols, array)
        {
            //std::cout << "Конструктор #2 -> Матрица №" << m_id << std::endl;
        }

        explicit Matrix(int size, const T* array = NULL)
            : Base<T>(size, size, array)
        {
            //std::cout << "Конструктор #3 -> Матрица №" << m_id << std::endl;
        }

        Matrix(const std::initializer_list<T> list, int rows = 0, int cols = 0)
            : Base<T>(list, rows, cols)
        {
            //std::cout << "Конструктор #4 -> Матрица №" << m_id << std::endl;
        }

        Matrix(int size, T(*func)(T, T), T min = 0, T max = 100)
            : Matrix<T>(size, size, func, min, max)
        {
            //std::cout << "Конструктор #5 -> Матрица №" << m_id << std::endl;
        }


        Matrix(int rows, int cols, T(*func)(T, T), T min = 0, T max = 100)
            : Base<T>(rows, cols)
        {
            for (unsigned iii = 0; iii < m_rows; ++iii)
                for (unsigned jjj = 0; jjj < m_cols; ++jjj)
                    m_item[iii * m_cols + jjj] = func(min, max);
            //std::cout << "Конструктор #6 -> Матрица №" << m_id << std::endl;
        }

        Matrix(int size, T(*func)(size_t, size_t, size_t, size_t))
            : Matrix<T>(size, size, func)
        {
            //std::cout << "Конструктор #7 -> Матрица №" << m_id << std::endl;
        }

        Matrix(int rows, int cols, T(*func)(size_t, size_t, size_t, size_t))
            : Base<T>(rows, cols)
        {
            for (unsigned iii = 0; iii < m_rows; ++iii)
                for (unsigned jjj = 0; jjj < m_cols; ++jjj)
                    m_item[iii * m_cols + jjj] = func(m_rows, m_cols, iii, jjj);
            //std::cout << "Конструктор #8 -> Матрица №" << m_id << std::endl;
        }

        Matrix(const Matrix<T>& fromMatrix)
            : Base<T>(fromMatrix.m_rows, fromMatrix.m_cols, fromMatrix.m_item)
        {
            //std::cout << "Конструктор #9 -> Матрица №" << m_id << std::endl;
        }

        Matrix(Matrix<T>&& fromMatrix) noexcept
            : Base<T>(fromMatrix)
        {
            //std::cout << "Конструктор #10 -> Матрица №" << m_id << std::endl;
        }

        Matrix(const Base<T>& fromBase)
            : Base<T>(fromBase)
        {
            //std::cout << "Конструктор #11 -> Матрица №" << m_id << std::endl;
        }

        Matrix(Base<T>&& fromBase) noexcept
            : Base<T>(std::move(fromBase))
        {
            //std::cout << "Конструктор #12 -> Матрица №" << m_id << std::endl;
        }



        virtual ~Matrix() noexcept
        {
            //std::cout << "Деструктор матрицы №" << m_id << std::endl;
        }

        unsigned getRows() const
        {
            return m_rows;
        }
        unsigned getCols() const
        {
            return m_cols;
        }

        Matrix<T> transposition() const
        {
            Matrix<T> Tran(*this);
            for (int i = 0; i < m_rows; i++)
                for (int j = i + 1; j < m_cols; j++)
                    std::swap(Tran.m_item[i * m_cols + j], Tran.m_item[j * m_cols + i]);
            return Tran;
        }

        Row<T> operator[](int row)
        {
            if (row >= static_cast<int>(m_rows) || static_cast<int>(m_rows) + row < 0)
                throw std::out_of_range("Номер строки выходит за пределы матрицы №" + std::to_string(m_id) + '\n');
            else if (row < 0)
                row = m_rows + row;
            return  Row<T>(m_cols, m_item + (row * m_cols), std::to_string(m_id));
        }

        const Row<T> operator[](int row) const
        {
            if (row >= static_cast<int>(m_rows) || static_cast<int>(m_rows) + row < 0)
                throw std::out_of_range("Номер строки выходит за пределы матрицы №" + std::to_string(m_id) + '\n');
            else if (row < 0)
                row = m_rows + row;
            return  Row<T>(m_cols, m_item + (row * m_cols), std::to_string(m_id));
        }

        const Matrix<T>& operator=(const Matrix<T>& matrix)
        {
            return Base<T>::operator=(matrix);
        }

        const Matrix<T>& operator=(int x)
        {
            return Base<T>::operator=(x);
        }

        const Matrix<T>& operator=(Matrix<T>&& matrix) noexcept
        {
            return Base<T>::operator=(std::move(matrix));
        }

    };

}