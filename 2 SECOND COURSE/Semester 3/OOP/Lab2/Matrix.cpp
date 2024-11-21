#include <iostream>
#include "Header.h"
#include <string>

namespace AreaMatrix
{
	// инициализация id
	int Matrix::m_value = 1;

	// Конструктор прямоугольной матрицы с задаными значеними
	Matrix::Matrix(int ROWS, int COLUMNS, const double *array) : m_ROWS{ ROWS }, m_COLUMNS{ COLUMNS }, m_id{ m_value++ }
	{
		if (m_ROWS <= 0 || m_COLUMNS <= 0)
		{
			throw std::logic_error{ "Данные размерности Matrix #" + std::to_string(m_id) + "не корректы !!!" +
									"\nСоздаем матрицу по умолчанию 3х3" };
			
			/*std::cout << "Данные размерности Matrix #" << m_id << "не корректы !!!" << std::endl;
			std::cout << "Создаем матрицу по умолчанию 3х3" << std::endl;*/
		}

		std::cout << "\nMatrix #" << m_id << std::endl;
		std::cout << "Number of rows = " << m_ROWS << std::endl;
		std::cout << "Number of columns = " << m_COLUMNS << std::endl;

		m_digit = new double[m_ROWS * m_COLUMNS];

		if (!m_digit)
		{
			throw std::logic_error{ "Матрица не имеет заданных значений !!!\nТогда их передадим уже из заполненного массива" };

			/*std::cout << "Матрица не имеет заданных значений !!!" << std::endl;
			std::cout << "Тогда их передадим уже из заполненного массива" << std::endl;*/
		}

		for (int i = 0; i < m_ROWS * m_COLUMNS; ++i)
			m_digit[i] = array[i];
	}

	// Конструктор по умолчанию
	Matrix::Matrix() : Matrix(3, 3)
	{
		// std::cout << "Произошло делегирование матрицы по умолчанию 3х3" << std::endl;
	}

	// Конструктор квадратной матрицы без заданых значений
	Matrix::Matrix(int ROWS) : Matrix(ROWS, ROWS)
	{
		// std::cout << "Произошло делегирование квадратной матрицы без заданных значений" << std::endl;	
	}

	// Конструктор квадратной матрицы с задаными значеними
	Matrix::Matrix(int ROWS, const double *array) : Matrix(ROWS, ROWS, array)
	{
		// std::cout << "Произошло делегирование квадратной матрицы c заданными значениями" << std::endl;
	}

	// Конструктор прямоугольной матрицы без заданых значений
	Matrix::Matrix(int ROWS, int COLUMNS) : Matrix(ROWS, COLUMNS, new double[m_ROWS * m_COLUMNS])
	{
		// std::cout << "Произошло делегирование прямоугольной матрицы без заданных значений" << std::endl;

		for (int i = 0; i < m_ROWS * m_COLUMNS; ++i)
			m_digit[i] = std::rand() % 30 - 10;
	}

	// Конструктор копирования
	Matrix::Matrix(const Matrix& copy) : Matrix(copy.m_ROWS, copy.m_COLUMNS, copy.m_digit)
	{
		// std::cout << "Произошло делегирование копирования матрицы" << std::endl;
	}

	Matrix::Matrix(Matrix&& A) : m_id{ m_value++ }
	{
		this->m_ROWS = A.m_ROWS;
		this->m_COLUMNS = A.m_COLUMNS;
		this->m_digit = A.m_digit;

		A.m_ROWS = 0;
		A.m_COLUMNS = 0;
		A.m_digit = NULL;

		std::cout << *this;
	}

	// Деструктор
	Matrix::~Matrix()
	{
		std::cout << "Destructor #" << m_id << std::endl;

		if (m_digit != nullptr)
		{
			delete[] m_digit;
		}
	}

	int Matrix::Get_Rows() const
	{
		return m_ROWS;
	}

	int Matrix::Get_Columns() const
	{
		return m_COLUMNS;
	}

	// Проверка сложения матриц
	bool Matrix::Addition(const Matrix& A)
	{
		return (m_ROWS == A.Get_Rows() && m_COLUMNS == A.Get_Columns());
	}

	// Проверка умножения матриц
	bool Matrix::Multiplication(const Matrix& A)
	{
		return (m_ROWS == A.Get_Columns());
	}

	// Максимальный элемент
	double Matrix::Maxim(const Matrix& A)
	{
		double maxim = A.m_digit[0];

		for (int i = 0; i < A.Get_Rows() * A.Get_Columns(); ++i)
		{
			if (maxim < A.m_digit[i])
				maxim = A.m_digit[i];
		}

		std::cout << "Максимальный элемент Matrix #" << m_id << " = ";
		return maxim;
	}

	// Минимальный элемент
	double Matrix::Minim(const Matrix& A)
	{
		double minim = A.m_digit[0];

		for (int i = 0; i < A.Get_Rows() * A.Get_Columns(); ++i)
		{
			if (minim > A.m_digit[i])
				minim = A.m_digit[i];
		}

		std::cout << "Минимальный элемент Matrix #" << m_id << " = ";
		return minim;
	}

	// Вывод
	std::ostream& operator<<(std::ostream& output, const Matrix& A)
	{
		for (int i = 0; i < A.m_ROWS; ++i)
		{
			std::cout << "[ ";
			for (int j = 0; j < A.m_COLUMNS; ++j)
			{
				output << A.m_digit[i * A.m_COLUMNS + j] << " ";
			}
			std::cout << "]" << std::endl;
		}

		return output;
	}


	double Matrix::Rows::operator[](int p_COLUMNS)
	{
		return p_ROWS[p_COLUMNS];
	}

	Matrix::Rows Matrix::operator[](int p_COLUMNS)
	{
		Matrix::Rows p_R;
		p_R.p_ROWS = &m_digit[p_COLUMNS * m_COLUMNS];
		return p_R;
	}

	const Matrix::Rows Matrix::operator[](int p_COLUMNS) const
	{
		Matrix::Rows p_R;
		p_R.p_ROWS = &m_digit[p_COLUMNS * m_COLUMNS];
		return p_R;
	}

	const Matrix& Matrix::operator=(const Matrix& A)
	{
		std::cout << "------------------------ Assignment Matrix -------------------\n" << std::endl;
		if (this == &A) { return *this; }

		if (m_ROWS * m_COLUMNS != A.m_ROWS * A.m_COLUMNS)
		{
			this->m_ROWS = A.m_ROWS;
			this->m_COLUMNS = A.m_COLUMNS;

			delete[] m_digit;
			m_digit = new double[m_ROWS * m_COLUMNS];
		}

		for (int i = 0; i < m_ROWS * m_COLUMNS; ++i)
			m_digit[i] = A.m_digit[i];

		return *this;
	}

	Matrix& Matrix::operator=(Matrix&& A)
	{
		std::cout << "\n\n------------------------ Swap -------------------" << std::endl;
		if (&A == this) { return *this; }

		int temp_ROWS_COLUMNS = A.m_ROWS;
		A.m_ROWS = m_ROWS;
		m_ROWS = temp_ROWS_COLUMNS;

		temp_ROWS_COLUMNS = A.m_COLUMNS;
		A.m_COLUMNS = m_COLUMNS;
		m_COLUMNS = temp_ROWS_COLUMNS;

		double *temp_digit = A.m_digit;
		A.m_digit = m_digit;
		m_digit = temp_digit;

		return *this;
	}

	const Matrix & Matrix::operator+=(const Matrix& A)
	{
		std::cout << "\n\n------------------------ Addition Matrix -------------------" << std::endl;
		if (!Addition(A))
		{
			std::cout << "Matrix #" << m_id << std::endl;
			std::cout << "Number of rows = " << m_ROWS << std::endl;
			std::cout << "Number of columns = " << m_COLUMNS << std::endl;

			std::cout << "\nMatrix #" << A.m_id << std::endl;
			std::cout << "Number of rows = " << A.m_ROWS << std::endl;
			std::cout << "Number of columns = " << A.m_COLUMNS << std::endl;

			throw std::logic_error{ "Matrix #" + std::to_string(m_id) + "\n" +
									"Number of rows = " + std::to_string(m_ROWS) + "\n" +
									"Number of columns = " + std::to_string(m_COLUMNS) + "\n" +
									"\nMatrix #" + std::to_string(m_id) + "\n" +
									"Number of rows = " + std::to_string(A.m_ROWS) + "\n" +
									"Number of columns = " + std::to_string(A.m_COLUMNS) + "\n" +
									+"\nNot be add!!!" };

			// std::cout << "\nNot be add!!!" << std::endl;
		}

		std::cout << "Matrixes have been added\n" << std::endl;
		for (int i = 0; i < m_ROWS * m_COLUMNS; ++i)
			m_digit[i] += A.m_digit[i];

		return *this;
	}

	const Matrix & Matrix::operator-=(const Matrix& A)
	{
		std::cout << "\n\n------------------------ Subtraction Matrix -------------------" << std::endl;
		if (!Addition(A))
		{
			std::cout << "Matrix #" << m_id << std::endl;
			std::cout << "Number of rows = " << m_ROWS << std::endl;
			std::cout << "Number of columns = " << m_COLUMNS << std::endl;

			std::cout << "Мatrix #" << A.m_id << std::endl;
			std::cout << "Number of rows = " << A.m_ROWS << std::endl;
			std::cout << "Number of columns = " << A.m_COLUMNS << std::endl;
				
			throw std::logic_error{ "Matrix #" + std::to_string(m_id) + "\n" +
									"Number of rows = " + std::to_string(m_ROWS) + "\n" +
									"Number of columns = " + std::to_string(m_COLUMNS) + "\n" +
									"\nMatrix #" + std::to_string(m_id) + "\n" +
									"Number of rows = " + std::to_string(A.m_ROWS) + "\n" +
									"Number of columns = " + std::to_string(A.m_COLUMNS) + "\n" +
									+"\nNot be sub!!!" };

			// std::cout << "\nNot be add!!!" << std::endl;
		}

		std::cout << "Matrixes have been subtracted\n" << std::endl;
		for (int i = 0; i < m_ROWS * m_COLUMNS; ++i)
			m_digit[i] -= A.m_digit[i];

		return *this;
	}

	const Matrix& Matrix::operator*=(const Matrix& A)
	{
		std::cout << "\n\n------------------------ Multiplication Matrix -------------------" << std::endl;
		if (!Multiplication(A))
		{/*
			std::cout << "Matrix #" << m_id << std::endl;
			std::cout << "Number of rows = " << m_ROWS << std::endl;
			std::cout << "Number of columns = " << m_COLUMNS << std::endl;

			std::cout << "\nMatrix #" << A.m_id << std::endl;
			std::cout << "Number of rows = " << A.m_ROWS << std::endl;
			std::cout << "Number of columns = " << A.m_COLUMNS << std::endl;*/

			throw std::logic_error{ "Matrix #" + std::to_string(m_id) + "\n" +
									"Number of rows = " + std::to_string(m_ROWS) + "\n" +
									"Number of columns = " + std::to_string(m_COLUMNS) + "\n" +
									"\nMatrix #" + std::to_string(m_id) + "\n" +
									"Number of rows = " + std::to_string(A.m_ROWS) + "\n" +
									"Number of columns = " + std::to_string(A.m_COLUMNS) + "\n" +
									+ "\nNot be multiplicate!!!" };

			// std::cout << "\nNot be multiplicate!!!" << std::endl;
		}

		std::cout << "Matrixes have been multiplicated\n" << std::endl;

		double *array = new double[m_ROWS * A.Get_Columns()];
		for (int i = 0; i < m_ROWS; i++)
		{
			for (int j = 0; j < A.Get_Columns(); j++)
			{
				array[i * A.Get_Columns() + j] = 0;
				for (int k = 0; k < m_COLUMNS; k++)
				{
					array[i * A.Get_Columns() + j] += (m_digit[i * m_COLUMNS + k] * A[k][j]);
				}
			}
		}

		delete[] m_digit;
		m_digit = array;

		m_COLUMNS = A.Get_Columns();
		//m_ROWS = A.Get_Rows();
		return *this;
	}

	const Matrix& Matrix::operator*=(const double scalar)
	{
		std::cout << "\n\n------------------------ Scalar Matrix -------------------" << std::endl;
		for (int i = 0; i < m_ROWS; ++i)
		{
			for (int j = 0; j < m_COLUMNS; ++j)
				m_digit[i * m_COLUMNS + j] *= scalar;
		}

		return *this;
	}

	Matrix operator+(Matrix& A, Matrix& B)
	{
		if (!A.Addition(B)) { throw std::logic_error{ "\nNot be add!!!" }; }

		Matrix C(A);
		C += B;
		return C;
	}

	Matrix operator-(Matrix& A, Matrix& B)
	{
		if (!A.Addition(B)) { throw std::logic_error{ "\nNot be sub!!!" }; }

		Matrix C(A);
		C -= B;
		return C;
	}

	Matrix operator*(Matrix& A, Matrix& B)
	{
		if (!A.Multiplication(B)) { throw std::logic_error{ "\nNot be multiplicate!!!" };}

		Matrix C(A);
		C *= B;
		return C;
	}

	Matrix operator*(Matrix& A, double scalar)
	{
		Matrix C(A);
		C *= scalar;
		return C;
	}
}
