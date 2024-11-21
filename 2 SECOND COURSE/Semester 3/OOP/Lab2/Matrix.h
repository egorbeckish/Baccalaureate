#pragma once
#include <iostream>


namespace AreaMatrix
{
	class Matrix
	{
	public:

		// Конструктор по умолчанию
		explicit Matrix();

		// Конструктор квадратной матрицы без заданых значений
		Matrix(int ROWS);

		// Конструктор квадратной матрицы с задаными значеними
		Matrix(int ROWS, const double *array);

		// Конструктор прямоугольной матрицы без заданых значений
		Matrix(int ROWS, int COLUMNS);

		// Конструктор прямоугольной матрицы с задаными значеними
		Matrix(int ROWS, int COLUMNS, const double *array);

		// Конструктор копирования
		Matrix(const Matrix& copy);
		
		// Конструктор перемещения
		Matrix(Matrix&& A) noexcept;

		// Деструктор
		~Matrix();

		// Геттер строк
		int Get_Rows() const;

		// Геттер столбцов
		int Get_Columns() const;

		// Проверка сложения матриц
		bool Addition(const Matrix& A);

		// Проверка умножения матриц
		bool Multiplication(const Matrix& A);

		// Максимальный элемент
		double Maxim(const Matrix& A);

		// Минимальный элемент
		double Minim(const Matrix& A);

		// Перегрузка оператора << вывода
		friend std::ostream& operator<<(std::ostream& output, const Matrix& A);

		class Rows
		{
		public:

			double *p_ROWS;
			double operator[](int p_COLUMNS);
		};

		// Перегрузка оператора []
		Rows operator[](int p_COLUMNS);

		const Rows operator[](int p_COLUMNS) const;

		// Перегрузка оператора = присваивания
		const Matrix& operator=(const Matrix& A);

		Matrix& operator=(Matrix&& A);

		// Перегрузка оператора += сложение
		const Matrix& operator+=(const Matrix& A);

		// Перегрузка оператора -= вычитание
		const Matrix& operator-=(const Matrix& A);

		// Перегрузка оператора *= умножение
		const Matrix& operator*=(const Matrix& A);

		// Перегрузка оператора *= умножение на скаляр
		const Matrix& operator*=(const double scalar);


	private:
		int m_ROWS, m_COLUMNS, m_id;
		double *m_digit;
		static int m_value;
	};

	// Перегрузка оператора + сложения (внешний оператор)
	Matrix operator+(Matrix& A, Matrix& B);

	// Перегрузка оператора - вычитания (внешний оператор)
	Matrix operator-(Matrix& A, Matrix& B);

	// Перегрузка оператора * умножения (внешний оператор)
	Matrix operator*(Matrix& A, Matrix& B);

	// Перегрузка оператора * умножения на скаляр (внешний оператор)
	Matrix operator*(Matrix& A, double scalar);
}
