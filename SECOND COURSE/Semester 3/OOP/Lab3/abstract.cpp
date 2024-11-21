#include "abstract.h"
#include <string>


namespace VectorMatrix
{
	int Base::m_value = 0;
	Base::Base(int ROWS, int COLUMNS, const double* array) : m_ROWS{ ROWS }, m_COLUMNS{ COLUMNS }, m_id{ ++m_value }
	{
		if (m_ROWS <= 0 || m_COLUMNS <= 0)
		{
			throw std::logic_error{ "Данные размерности Базового класс #" + std::to_string(m_id) + "не корректы !!!" +
									"\nСоздаем базовый класс по умолчанию 3х3" };
		}

		m_digit = new double[m_ROWS * m_COLUMNS];

		if (!m_digit)
		{
			throw std::logic_error{ "Базовый класса не имеет заданных значений !!!\nТогда их передадим уже из заполненного массива" };
		}

		for (int i = 0; i < m_ROWS * m_COLUMNS; ++i)
			m_digit[i] = array[i];
	}

	Base::Base() : Base(3, 3) {}
	Base::Base(int ROWS) : Base(ROWS, ROWS) {}
	Base::Base(int ROWS, const double* array) : Base(ROWS, ROWS, array) {}
	Base::Base(int ROWS, int COLUMNS) : Base(ROWS, COLUMNS, new double[m_ROWS * m_COLUMNS])
	{
		for (int i = 0; i < m_ROWS * m_COLUMNS; ++i)
			m_digit[i] = std::rand() % 30 - 10;
	}

	Base::Base(const Base& copy) noexcept : Base(copy.m_ROWS, copy.m_COLUMNS, copy.m_digit) {}

	
	Base::Base(Base&& A) noexcept : m_id{ ++m_value }
	{
		this->m_ROWS = A.m_ROWS;
		this->m_COLUMNS = A.m_COLUMNS;
		this->m_digit = A.m_digit;

		A.m_ROWS = 0;
		A.m_COLUMNS = 0;
		A.m_digit = NULL;

		std::cout << *this;
	}

	const Base& Base::operator=(Base&& A) noexcept
	{
		std::cout << "\n\n------------------------ Swap -------------------" << std::endl;
		if (&A == this) { return *this; }

		int temp_ROWS_COLUMNS = A.m_ROWS;
		A.m_ROWS = m_ROWS;
		m_ROWS = temp_ROWS_COLUMNS;

		temp_ROWS_COLUMNS = A.m_COLUMNS;
		A.m_COLUMNS = m_COLUMNS;
		m_COLUMNS = temp_ROWS_COLUMNS;

		double* temp_digit = A.m_digit;
		A.m_digit = m_digit;
		m_digit = temp_digit;

		return *this;
	}

	Base::~Base()
	{
		//std::cout << "Destructor #" << m_id << std::endl;

		if (m_digit != nullptr)
		{
			delete[] m_digit;
		}
	}

	int Base::GET_ROWS() { return m_ROWS; }
	int Base::GET_COLUMNS() { return m_COLUMNS; }
	bool Base::Addition(const Base& A) { return (m_ROWS == A.m_COLUMNS && m_COLUMNS == A.m_ROWS); }
	bool Base::Multiplication(const Base& A) { return (m_ROWS == A.m_COLUMNS); }

	double Base::Maxim(const Base& A) const
	{
		double maxim = A.m_digit[0];

		for (int i = 0; i < A.m_ROWS * A.m_COLUMNS; ++i)
		{
			if (maxim < A.m_digit[i])
				maxim = A.m_digit[i];
		}

		std::cout << "Максимальный элемент = ";
		return maxim;
	}

	double Base::Minim(const Base& A) const
	{
		double minim = A.m_digit[0];

		for (int i = 0; i < A.m_ROWS * A.m_COLUMNS; ++i)
		{
			if (minim > A.m_digit[i])
				minim = A.m_digit[i];
		}

		std::cout << "Минимальный элемент = ";
		return minim;
	}

	double Base::Module() const
	{
		double _module = 0;
		for (int i = 0; i < m_ROWS * m_COLUMNS; ++i)
		{
			_module += m_digit[i] * m_digit[i];
		}

		_module = sqrt(_module);

		return _module;
	}

	double Base::Rows::operator[](int p_COLUMNS)
	{

		return p_ROWS[p_COLUMNS];
	}

	Base::Rows Base::operator[](int p_COLUMNS)
	{
		//std::cout << p_COLUMNS << '\n';
		if (p_COLUMNS >= m_ROWS)
		{
			throw std::out_of_range("Номер индекса выходит за пределы вектора №" + std::to_string(m_id) + '\n');
		}

		Base::Rows p_R;
		p_R.p_ROWS = &m_digit[p_COLUMNS * m_COLUMNS];
		return p_R;
	}

	const Base::Rows Base::operator[](int p_COLUMNS) const
	{
		if (p_COLUMNS >= m_ROWS && p_COLUMNS >= m_COLUMNS)
		{
			throw std::out_of_range("Номер индекса выходит за пределы вектора №" + std::to_string(m_id) + '\n');
		}


		Base::Rows p_R;
		p_R.p_ROWS = &m_digit[p_COLUMNS * m_COLUMNS];
		return p_R;
	}

	

	const Base& Base::operator=(const Base& A)
	{
		std::cout << "\n------------------------ Assignmentx -------------------\n" << std::endl;
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

	const Base& Base::operator+=(const Base& A)
	{
		std::cout << "\n\n------------------------ Addition -------------------" << std::endl;
		if (!Addition(A))
		{
			/*std::cout << "Matrix #" << m_id << std::endl;
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
									+"\nNot be add!!!" };

			// std::cout << "\nNot be add!!!" << std::endl;
		}

		for (int i = 0; i < m_ROWS * m_COLUMNS; ++i)
			m_digit[i] += A.m_digit[i];

		return *this;
	}

	const Base& Base::operator-=(const Base& A)
	{
		std::cout << "\n\n------------------------ Subtraction -------------------" << std::endl;
		if (!Addition(A))
		{
			/*std::cout << "Matrix #" << m_id << std::endl;
			std::cout << "Number of rows = " << m_ROWS << std::endl;
			std::cout << "Number of columns = " << m_COLUMNS << std::endl;

			std::cout << "Мatrix #" << A.m_id << std::endl;
			std::cout << "Number of rows = " << A.m_ROWS << std::endl;
			std::cout << "Number of columns = " << A.m_COLUMNS << std::endl;*/

			throw std::logic_error{ "Matrix #" + std::to_string(m_id) + "\n" +
									"Number of rows = " + std::to_string(m_ROWS) + "\n" +
									"Number of columns = " + std::to_string(m_COLUMNS) + "\n" +
									"\nMatrix #" + std::to_string(m_id) + "\n" +
									"Number of rows = " + std::to_string(A.m_ROWS) + "\n" +
									"Number of columns = " + std::to_string(A.m_COLUMNS) + "\n" +
									+"\nNot be sub!!!" };

			// std::cout << "\nNot be add!!!" << std::endl;
		}

		for (int i = 0; i < m_ROWS * m_COLUMNS; ++i)
			m_digit[i] -= A.m_digit[i];

		return *this;
	}

	const Base& Base::operator*=(const Base& A)
	{
		std::cout << "\n\n------------------------ Multiplication -------------------" << std::endl;
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
									+"\nNot be multiplicate!!!" };

			// std::cout << "\nNot be multiplicate!!!" << std::endl;
		}

		std::cout << "Have been multiplicated\n" << std::endl;

		double* array = new double[m_ROWS * A.m_COLUMNS];
		for (int i = 0; i < m_ROWS; i++)
		{
			for (int j = 0; j < A.m_COLUMNS; j++)
			{
				array[i * A.m_COLUMNS + j] = 0;
				for (int k = 0; k < m_COLUMNS; k++)
				{
					array[i * A.m_COLUMNS + j] += (m_digit[i * m_COLUMNS + k] * A.m_digit[k * A.m_COLUMNS + j]);
				}
			}
		}

		delete[] m_digit;
		m_digit = array;

		m_COLUMNS = A.m_COLUMNS;
		return *this;
	}

	const Base& Base::operator*=(const double scalar)
	{
		std::cout << "\n\n------------------------ Scalar -------------------" << std::endl;
		for (int i = 0; i < m_ROWS; ++i)
		{
			for (int j = 0; j < m_COLUMNS; ++j)
				m_digit[i * m_COLUMNS + j] *= scalar;
		}

		return *this;
	}

	/*Base operator+(const Base& A, const Base& B)
	{
		return Base(A) += B;
	}*/

	//Base operator-(const Base& A, const Base& B)
	//{
	//	return Base(A) -= B;
	//}

	//Base operator*(const Base& A, const Base& B)
	//{
	//	return Base(A) *= B;
	//}

	//Base operator+(const Base& A, const double scalar)
	//{
	//	return Base(A) *= scalar;
	//}

	std::ostream& operator<<(std::ostream& output, const Base& data)
	{
		for (int i = 0; i < data.m_ROWS; ++i)
		{
			std::cout << "[ ";
			for (int j = 0; j < data.m_COLUMNS; ++j)
			{
				output << data.m_digit[i * data.m_COLUMNS + j] << " ";
			}
			std::cout << "]" << std::endl;
		}

		return output;
	}

	

	



	
	// -------------------- Вектор -----------------------------------
	int MyVector::mvalue_id = 0;
	MyVector::MyVector() : Base(3, 1)
	{
		std::cout << "\n\nVirtual class for vector #" << m_id << std::endl;
	}

	MyVector::MyVector(int ROWS) : Base(ROWS, 1)
	{
		std::cout << "\n\nVirtual class for vector #" << m_id << std::endl;
	}

	MyVector::MyVector(int ROWS, const double* array) : Base(ROWS, 1, array)
	{
		std::cout << "\n\nVirtual class for vector #" << m_id << std::endl;
	}

	MyVector::MyVector(int ROWS, int COLUMNS) : Base(ROWS, COLUMNS = 1)
	{
		std::cout << "\n\nVirtual class for vector #" << m_id << std::endl;
	}

	MyVector::MyVector(int ROWS, int COLUMNS, const double* array) : Base(ROWS, 1, array)
	{
		std::cout << "\n\nVirtual class for vector #" << m_id << std::endl;
	}

	MyVector::MyVector(const MyVector& copy) : Base(copy) 
	{
		std::cout << "Произошло копирование вектора #" << m_id << std::endl;
	}

	const MyVector& MyVector::NormalizedVector()
	{
		double _module = Base::Module();
		for (int i = 0; i < m_ROWS * m_COLUMNS; ++i)
		{
			m_digit[i] /= _module;
		}

		return *this;
	}

	const MyVector& MyVector::Transposition()
	{
		std::swap(m_ROWS, m_COLUMNS);
		return *this;
	}


	MyVector::~MyVector() { std::cout << "\n\nDestructor vector #" << m_id << std::endl; }


	int MyVector::GET_ROWS() { return Base::GET_ROWS(); }
	int MyVector::GET_COLUMNS() { return Base::GET_COLUMNS(); }
	bool MyVector::Addition(const Base& A) { return Base::Addition(A); }
	bool MyVector::Multiplication(const Base& A) { return Base::Multiplication(A); }
	double MyVector::Maxim(const Base& A) const { return Base::Maxim(A); }
	double MyVector::Minim(const Base& A) const { return Base::Minim(A); }
	double MyVector::Module() const { return Base::Module(); }

	const MyVector& MyVector::operator=(const Base& A)
	{
		Base::operator=(A);
		return *this;
	}

	const MyVector& MyVector::operator+=(const Base& A)
	{
		if (!Addition(A))
			throw std::logic_error("Ошибка сложения");
		else
			Base::operator+=(A);
		return *this;
	}

	const MyVector& MyVector::operator-=(const Base& A)
	{
		if (!Addition(A))
			throw std::logic_error("Ошибка вычитания");
		else
			Base::operator-=(A);
		return *this;
	}

	const MyVector& MyVector::operator*=(const Base& A)
	{
		if (!Multiplication(A))
			throw std::logic_error("Ошибка умножения");
		else
			Base::operator*=(A);
		return *this;
	}

	const MyVector& MyVector::operator*=(const double scalar)
	{
	
		Base::operator*=(scalar);
		return *this;
	}
	// -------------------- Вектор -----------------------------------




	// -------------------- Матрица -----------------------------------
	int MyMatrix::mvalue_id = 0;
	MyMatrix::MyMatrix() : Base()
	{
		std::cout << "\n\nVirtual class for matrix #" << m_id << std::endl;
	}

	MyMatrix::MyMatrix(int ROWS) : Base(ROWS)
	{ 
		std::cout << "\n\nVirtual class for matrix #" << m_id << std::endl;
	}

	MyMatrix::MyMatrix(int ROWS, const double* array) : Base(ROWS, array)
	{
		std::cout << "\n\nVirtual class for matrix #" << m_id << std::endl;
	}

	MyMatrix::MyMatrix(int ROWS, int COLUMNS) : Base(ROWS, COLUMNS)
	{ 
		std::cout << "\n\nVirtual class for matrix #" << m_id << std::endl;
	}

	MyMatrix::MyMatrix(int ROWS, int COLUMNS, const double* array) : Base(ROWS, COLUMNS, array)
	{
		std::cout << "\n\nVirtual class for matrix #" << m_id << std::endl;
	}

	MyMatrix::MyMatrix(const MyMatrix& copy) : Base(copy)
	{
		std::cout << "Произошло копирование матрицы #" << m_id << std::endl;
	}

	MyMatrix::~MyMatrix() { std::cout << "\n\nDestructor matrix #" << m_id << std::endl; }


	int MyMatrix::GET_ROWS() { return Base::GET_ROWS(); }
	int MyMatrix::GET_COLUMNS() { return Base::GET_COLUMNS(); }
	bool MyMatrix::Addition(const Base& A) { return Base::Addition(A); }
	bool MyMatrix::Multiplication(const Base& A) { return Base::Multiplication(A); }
	double MyMatrix::Minim(const Base& A) const { return Base::Minim(A); }
	double MyMatrix::Maxim(const Base& A) const { return Base::Maxim(A); }
	double MyMatrix::Module() const { return Base::Module(); }

	const MyMatrix& MyMatrix::operator=(const Base& A)
	{
		Base::operator=(A);
		return *this;
	}

	const MyMatrix& MyMatrix::operator+=(const Base& A)
	{
		if (!Addition(A))
			throw std::logic_error("Ошибка сложения");
		else
			Base::operator+=(A);
		return *this;
	}

	const MyMatrix& MyMatrix::operator-=(const Base& A)
	{
		if (!Addition(A))
			throw std::logic_error("Ошибка вычитания");
		else
			Base::operator-=(A);
		return *this;
	}

	const MyMatrix& MyMatrix::operator*=(const Base& A)
	{
		if (!Multiplication(A))
			throw std::logic_error("Ошибка умножения");
		else
			Base::operator*=(A);
		return *this;
	}

	const MyMatrix& MyMatrix::operator*=(const double scalar)
	{

		Base::operator*=(scalar);
		return *this;
	}

	const MyMatrix& MyMatrix::Transposition() const
	{
		MyMatrix A(*this);
		for (int i = 0; i < m_ROWS; i++)
			for (int j = i + 1; j < m_COLUMNS; j++)
				std::swap(A.m_digit[i * m_COLUMNS + j], A.m_digit[j * m_COLUMNS + i]);
		return A;
	}
	// -------------------- Матрица -----------------------------------

}
