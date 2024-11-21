#pragma once

#include <iostream>
#include <iomanip>
#include <string>

namespace Math
{
	template <class T> class Base
	{
	private:
		static unsigned s_idCounter;
	protected:
		unsigned m_id, m_rows, m_cols;
		T* m_item;

		Base()
			: m_rows(0), m_cols(0), m_item(NULL), m_id(s_idCounter++)
		{
		}

		Base(int rows, int cols, const T* items = NULL)
			: Base<T>()
		{
			m_item = (rows <= 0 || cols <= 0)
				? throw std::length_error("Íåóäîâëåòâîðèòåëüíàÿ ðàçìåðíîñòü îáúåêòà ¹" + std::to_string(m_id) + '\n')
				: new T[rows * cols];
			m_rows = rows;
			m_cols = cols;

			if (items)
				for (unsigned iii = 0; iii < m_rows * m_cols; iii++)
					m_item[iii] = items[iii];
			else
				for (unsigned iii = 0; iii < m_rows * m_cols; iii++)
					m_item[iii] = 0;
		}

		Base(const std::initializer_list<T> list, int rows = 0, int cols = 0)
			: Base<T>()
		{
			if (list.size() == rows * cols)
				*this = std::move(Base<T>(rows, cols));
			else if (list.size() == rows * rows)
				*this = std::move(Base<T>(rows, rows));
			else
			{
				double new_size = sqrt(list.size());
				if (new_size - static_cast<int>(new_size) == 0)
					*this = std::move(Base<T>(static_cast<int>(new_size), static_cast<int>(new_size)));
				else
					throw std::length_error("Íåóäîâëåòâîðèòåëüíàÿ ðàçìåðíîñòü îáúåêòà\n");
			}
			unsigned count = 0;
			for (auto& element : list)
			{
				m_item[count] = element;
				count++;
			}
		}

		Base(const Base<T>& base) noexcept
			: Base<T>(base.m_rows, base.m_cols, base.m_item)
		{}

		Base(Base<T>&& base) noexcept
			: Base<T>()
		{
			operator = (std::move(base));
		}

	public:
		virtual ~Base()
		{
			delete[] m_item;
		}

		friend bool canMltpl(const Base<T>& A, const Base<T>& B) throw()
		{
			return A.m_cols == B.m_rows;
		}

		friend bool canAdd(const Base<T>& A, const Base<T>& B) throw()
		{
			return A.m_rows == B.m_rows
				&& A.m_cols == B.m_cols;
		}

		friend bool isMatrix(const Base<T>& X) throw()
		{
			return X.m_rows > 1 && X.m_cols > 1;
		}

		T getMax() const throw()
		{
			T max = m_item[0];
			for (unsigned iii = 0; iii < m_rows * m_cols; ++iii)
				if (max < m_item[iii])
					max = m_item[iii];
			return max;
		}
		T getMin() const throw()
		{
			T min = m_item[0];
			for (unsigned iii = 0; iii < m_rows * m_cols; ++iii)
				if (min > m_item[iii])
					min = m_item[iii];
			return min;
		}
		unsigned getId() const throw()
		{
			return m_id;
		}

		T getModule() const
		{
			T _module = 0;
			for (unsigned iii = 0; iii < m_cols * m_rows; ++iii)
				_module += m_item[iii] * m_item[iii];
			_module = sqrt(_module);
			return _module;
		}

		const Base<T>& operator=(const Base<T>& base) throw()
		{
			if (this == &base)
				return *this;

			if (m_rows * m_cols != base.m_rows * base.m_cols)
			{
				m_cols = base.m_cols;
				m_rows = base.m_rows;
				delete[] m_item;
				m_item = new T[m_rows * m_cols];
			}
			else if (m_rows != base.m_rows || m_cols != base.m_cols)
			{
				m_cols = base.m_cols;
				m_rows = base.m_rows;
			}


			for (unsigned iii = 0; iii < m_rows * m_cols; ++iii)
				m_item[iii] = base.m_item[iii];
			return *this;
		}

		const Base<T>& operator=(int x)
		{
			for (unsigned iii = 0; iii < m_rows; ++iii)
				for (unsigned jjj = 0; jjj < m_cols; ++jjj)
					if (iii == jjj)
						m_item[iii * m_rows + jjj] = x;
			return *this;

		}


		const Base<T>& operator=(Base<T>&& base) noexcept
		{
			if (this == &base)
				return *this;

			std::swap(m_rows, base.m_rows);
			std::swap(m_cols, base.m_cols);
			std::swap(m_id, base.m_id);
			std::swap(m_item, base.m_item);

			return *this;
		}

		const Base<T>& operator+=(const Base<T>& base)
		{
			if (!canAdd(*this, base))
				throw std::logic_error("\nÎïåðàöèÿ ñëîæåíèÿ íåâîçìîæíà ñ îáúåêòàìè: id:" + std::to_string(m_id)
					+ "; id:" + std::to_string(base.m_id));

			for (unsigned iii = 0; iii < m_rows * m_cols; ++iii)
				m_item[iii] += base.m_item[iii];

			return *this;
		}

		const Base<T>& operator-=(const Base<T>& base)
		{
			if (!canAdd(*this, base))
				throw std::logic_error("\nÎïåðàöèÿ ðàçíîñòè íåâîçìîæíà ñ îáúåêòàìè: id:" + std::to_string(m_id)
					+ "; id:" + std::to_string(base.m_id));

			for (unsigned iii = 0; iii < m_rows * m_cols; ++iii)
				m_item[iii] -= base.m_item[iii];

			return *this;
		}

		const Base<T>& operator%=(const Base<T>& base)
		{
			if (!canAdd(*this, base))
				throw std::logic_error("\nÎïåðàöèÿ âçÿòèÿ îñòàòêà îò äåëåíèÿ ïî êàæäîìó ýëåìåíòó íåâîçìîæíà ñ îáúåêòàìè: id:" + std::to_string(m_id)
					+ "; id:" + std::to_string(base.m_id));

			for (unsigned iii = 0; iii < m_rows * m_cols; ++iii)
				m_item[iii] %= base.m_item[iii];

			return *this;
		}

		const Base<T>& operator*=(const Base<T>& base)
		{
			if (!(canMltpl(*this, base)))
				throw std::logic_error("\nÎïåðàöèÿ óìíîæåíèÿ íåâîçìîæíà ñ îáúåêòàìè: id:" + std::to_string(m_id)
					+ "; id:" + std::to_string(base.m_id));

			T temp = 0;
			T* new_array = new T[m_rows * base.m_cols];
			for (unsigned iii = 0; iii < m_rows; ++iii)
				for (unsigned jjj = 0; jjj < base.m_cols; ++jjj)
				{
					for (unsigned kkk = 0; kkk < base.m_rows; ++kkk)
						if (kkk)
							temp += m_item[iii * m_cols + kkk]
							* base.m_item[kkk * base.m_cols + jjj];
						else
							temp = m_item[iii * m_cols + kkk]
							* base.m_item[kkk * base.m_cols + jjj];
					new_array[iii * base.m_cols + jjj] = temp;
				}
			delete[] m_item;
			m_item = new_array;
			m_cols = base.m_cols;
			return *this;
		}

		const Base<T>& operator*=(T k)
		{
			for (unsigned iii = 0; iii < m_rows * m_cols; ++iii)
				m_item[iii] *= k;
			return *this;
		}

		friend Base<T> operator+(const Base<T>& A, const Base<T>& B)
		{
			return Base<T>(A) += B;
		}

		friend Base<T> operator-(const Base<T>& A, const Base<T>& B)
		{
			return Base<T>(A) -= B;
		}

		friend Base<T> operator%(const Base<T>& A, const Base<T>& B)
		{
			return Base<T>(A) %= B;
		}

		friend Base<T> operator*(const Base<T>& A, const Base<T>& B)
		{
			return Base<T>(A) *= B;
		}

		friend Base<T> operator*(const Base<T>& A, T k)
		{
			return Base<T>(A) *= k;
		}

		friend Base<T> operator*(T k, const Base<T>& A)
		{
			return Base<T>(A) *= k;
		}

		friend std::ostream& operator<<(std::ostream& out, const Base<T>& X)
		{
			std::streamsize width = out.width(), precision = out.precision();
			if (!width) width = 5;
			for (unsigned iii = 0; iii < X.m_rows; iii++)
			{
				for (unsigned jjj = 0; jjj < X.m_cols; jjj++)
					out << std::setw(width) << std::setprecision(precision) << X.m_item[iii * X.m_cols + jjj];
				out << "\n";
			}
			return out;
		}
		friend std::istream& operator>>(std::istream& in, const Base<T>& X)
		{
			for (unsigned iii = 0; iii < X.m_rows * X.m_cols; ++iii)
				in >> X.m_item[iii];
			return in;
		}

		T* getPointer() const
		{
			T* arr = new T[m_cols * m_rows];
			for (int i = 0; i < m_cols * m_rows; i++)
				arr[i] = m_item[i];
			return arr;
		}
	};

	template <class T> unsigned Base<T>::s_idCounter = 0;

	template<> class Base<std::string>
	{
	private:
		static unsigned s_idCounter;
	protected:
		unsigned m_id, m_rows, m_cols;
		std::string* m_item;

		Base()
			: m_rows(0), m_cols(0), m_item(NULL), m_id(s_idCounter++)
		{
		}

		Base(int rows, int cols, const std::string* items = NULL)
			: Base <std::string>()
		{
			m_item = (rows <= 0 || cols <= 0)
				? throw std::length_error("Íåóäîâëåòâîðèòåëüíàÿ ðàçìåðíîñòü îáúåêòà ¹" + std::to_string(m_id) + '\n')
				: new std::string[rows * cols];
			m_rows = rows;
			m_cols = cols;

			if (items)
				for (unsigned iii = 0; iii < m_rows * m_cols; iii++)
					m_item[iii] = items[iii];
		}

		Base(const std::initializer_list<std::string> list, int rows = 0, int cols = 0)
			: Base<std::string>()
		{
			if (list.size() == rows * cols)
				*this = std::move(Base<std::string>(rows, cols));
			else if (list.size() == rows * rows)
				*this = std::move(Base<std::string>(rows, rows));
			else
			{
				double new_size = sqrt(list.size());
				if (new_size - static_cast<int>(new_size) == 0)
					*this = std::move(Base<std::string>(static_cast<int>(new_size), static_cast<int>(new_size)));
				else
					throw std::length_error("Íåóäîâëåòâîðèòåëüíàÿ ðàçìåðíîñòü îáúåêòà\n");
			}
			unsigned count = 0;
			for (auto& element : list)
			{
				m_item[count] = element;
				count++;
			}
		}

		Base(const Base<std::string>& base) noexcept
			: Base<std::string>(base.m_rows, base.m_cols, base.m_item)
		{}

		Base(Base<std::string>&& base) noexcept
			: Base<std::string>()
		{
			operator = (std::move(base));
		}

	public:
		virtual ~Base()
		{
			delete[] m_item;
		}

		friend bool isMatrix(const Base<std::string>& X) throw()
		{
			return X.m_rows > 1 && X.m_cols > 1;
		}

		std::string getMax() const throw()
		{
			std::string max = m_item[0];
			for (unsigned iii = 0; iii < m_rows * m_cols; ++iii)
				if (max < m_item[iii])
					max = m_item[iii];
			return max;
		}

		std::string getMin() const throw()
		{
			std::string min = m_item[0];
			for (unsigned iii = 0; iii < m_rows * m_cols; ++iii)
				if (min > m_item[iii])
					min = m_item[iii];
			return min;
		}

		unsigned getId() const throw()
		{
			return m_id;
		}

		const Base<std::string>& operator=(const Base<std::string>& base) throw()
		{
			if (this == &base)
				return *this;

			if (m_rows * m_cols != base.m_rows * base.m_cols)
			{
				m_cols = base.m_cols;
				m_rows = base.m_rows;
				delete[] m_item;
				m_item = new std::string[m_rows * m_cols];
			}
			else if (m_rows != base.m_rows || m_cols != base.m_cols)
			{
				m_cols = base.m_cols;
				m_rows = base.m_rows;
			}


			for (unsigned iii = 0; iii < m_rows * m_cols; ++iii)
				m_item[iii] = base.m_item[iii];
			return *this;
		}

		const Base<std::string>& operator=(int x)
		{
			for (unsigned iii = 0; iii < m_rows; ++iii)
				for (unsigned jjj = 0; jjj < m_cols; ++jjj)
					if (iii == jjj)
						m_item[iii * m_rows + jjj] = std::to_string(x);
			return *this;

		}

		const Base<std::string>& operator=(Base<std::string>&& base) noexcept
		{
			if (this == &base)
				return *this;

			std::swap(m_rows, base.m_rows);
			std::swap(m_cols, base.m_cols);
			std::swap(m_id, base.m_id);
			std::swap(m_item, base.m_item);

			return *this;
		}

		const Base<std::string>& operator+=(const Base<std::string>& base)
		{
			for (unsigned iii = 0; iii < m_rows * m_cols; ++iii)
				m_item[iii] += base.m_item[iii];

			return *this;
		}

		friend Base<std::string> operator+(const Base<std::string>& A, const Base<std::string>& B)
		{
			return Base<std::string>(A) += B;
		}

		friend std::ostream& operator<<(std::ostream& out, const Base<std::string>& X)
		{
			std::streamsize width = out.width(), precision = out.precision();
			if (!width) width = 5;
			for (unsigned iii = 0; iii < X.m_rows; iii++)
			{
				for (unsigned jjj = 0; jjj < X.m_cols; jjj++)
					out << std::setw(width) << std::setprecision(precision) << X.m_item[iii * X.m_cols + jjj];
				out << "\n";
			}
			return out;
		}

		friend std::istream& operator>>(std::istream& in, const Base<std::string>& X)
		{
			for (unsigned iii = 0; iii < X.m_rows * X.m_cols; ++iii)
				in >> X.m_item[iii];
			return in;
		}
	};

	//template<> unsigned Base<std::string>::s_idCounter = 0;
}