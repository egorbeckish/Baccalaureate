#pragma once
#include <iostream>
#include <math.h>

namespace VectorMatrix
{
	class Base
	{
		private:
			static int m_value;

		protected:
			double* m_digit;
			int m_ROWS, m_COLUMNS, m_id;

		public:

			Base();
			Base(int ROWS);
			Base(int ROWS, const double* array);
			Base(int ROWS, int COLUMNS);
			Base(int ROWS, int COLUMNS, const double* array);
			Base(const Base& copy) noexcept;
			Base(Base&& copy) noexcept;
			virtual ~Base();
			
			virtual int GET_ROWS() = 0;
			virtual int GET_COLUMNS() = 0;
			virtual bool Addition(const Base& A) = 0;
			virtual bool Multiplication(const Base& A) = 0;
			virtual double Maxim(const Base& A) const = 0;
			virtual double Minim(const Base& A) const = 0;
			virtual double Module() const = 0;
			

			friend std::ostream& operator<<(std::ostream& output, const Base& data);

			class Rows
			{
				public:

					double* p_ROWS;
					double operator[](int p_COLUMNS);
			};

			Rows operator[](int p_COLUMNS);
			const Rows operator[](int p_COLUMNS) const;

			const Base& operator=(Base&& A) noexcept;

			virtual const Base& operator=(const Base& A) = 0;
			virtual const Base& operator+=(const Base& A) = 0;
			virtual const Base& operator-=(const Base& A) = 0;
			virtual const Base& operator*=(const Base& A) = 0;
			virtual const Base& operator*=(const double scalar) = 0;

			

			/*friend virtual Base operator+(const Base& A, const Base& B);
			friend virtual Base operator-(const Base& A, const Base& B);
			friend virtual Base operator*(const Base& A, const Base& B);
			friend virtual Base operator*(const Base& A, const double scalar);*/
	};

	


	class MyVector : virtual public Base
	{
		private:
			static int mvalue_id;
			unsigned m_len;

		public:

			Base::m_ROWS;
			Base::m_COLUMNS;
			Base::m_digit;
			Base::m_id;

			MyVector();
			MyVector(int ROWS);
			MyVector(int ROWS, const double* array);
			MyVector(int ROWS, int COLUMNS);
			MyVector(int ROWS, int COLUMNS, const double* array);
			MyVector(const MyVector& copy);
			~MyVector();

			int GET_ROWS() override;
			int GET_COLUMNS() override;
			bool Addition(const Base& A) override;
			bool Multiplication(const Base& A) override;
			double Maxim(const Base& A) const override;
			double Minim(const Base& A) const override;
			double Module() const override;

			const MyVector& operator=(const Base& A) override;
			const MyVector& operator+=(const Base& A) override;
			const MyVector& operator-=(const Base& A) override;
			const MyVector& operator*=(const Base& A) override;
			const MyVector& operator*=(const double scalar) override;

			/*const MyVector& operator[](int p_COLUMNS) const override;
			MyVector& operator[](int p_COLUMNS) override;*/


			const MyVector& NormalizedVector();
			const MyVector& Transposition();
	};


	class MyMatrix : virtual public Base
	{
		private:
			static int mvalue_id;

		public:

			Base::m_ROWS;
			Base::m_COLUMNS;
			Base::m_digit;
			Base::m_id;

			MyMatrix();
			MyMatrix(int ROWS);
			MyMatrix(int ROWS, const double* array);
			MyMatrix(int ROWS, int COLUMNS);
			MyMatrix(int ROWS, int COLUMNS, const double* array);
			MyMatrix(const MyMatrix& copy);
			~MyMatrix();

			int GET_ROWS() override;
			int GET_COLUMNS() override;
			bool Addition(const Base& A) override;
			bool Multiplication(const Base& A) override;
			double Maxim(const Base& A) const override;
			double Minim(const Base& A) const override;
			double Module() const override;


			const MyMatrix& operator=(const Base& A) override;
			const MyMatrix& operator+=(const Base& A) override;
			const MyMatrix& operator-=(const Base& A) override;
			const MyMatrix& operator*=(const Base& A) override;
			const MyMatrix& operator*=(const double scalar) override;

			/*const MyMatrix& operator[](int p_COLUMNS) const override;
			MyMatrix& operator[](int p_COLUMNS) override;*/

			const MyMatrix& Transposition() const;
	};

}
