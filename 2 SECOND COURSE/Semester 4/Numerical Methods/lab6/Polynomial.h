#pragma once
#include <iostream>
#include <sstream>


namespace luMath
{
	template <class T> class Polynomial
	{
	private:
		static unsigned s_idCounter;
		unsigned m_id;
		unsigned m_length;
		T* m_coeff;

	public:
		explicit Polynomial(unsigned length = 1, T* coeff = nullptr)
			: m_id{ s_idCounter++ }, m_length{ length }
		{
			if (m_length < 0)
				throw  std::invalid_argument("Степень полинома отрицательна.");

			m_coeff = new T[m_length];
			if (coeff)
			{
				for (unsigned i = 0; i < m_length; i++)
					m_coeff[i] = coeff[i];
				reduce();
			}
			else for (unsigned i = 0; i < m_length; i++)
				m_coeff[i] = 0.0;
		}


		Polynomial(T number)
			: m_id{ s_idCounter++ }, m_length{ 1 }, m_coeff{ new T[m_length] }
		{ 
			m_coeff[0] = number; 
		}

		Polynomial(std::initializer_list<T> list)
			: m_id{ s_idCounter++ }
		{
			m_length = static_cast<unsigned>(list.size());
			m_coeff = new T[m_length];
				
			unsigned count = 0;
			for (auto& element : list)
				m_coeff[count++] = (T)element;
		}
		Polynomial(const Polynomial<T>& polynomial)
			: Polynomial<T>(polynomial.m_length, polynomial.m_coeff) 
		{	}

		Polynomial(Polynomial&& polynomial) noexcept
			: m_id{ polynomial.m_id }, m_length{ polynomial.m_length }
		{
			m_coeff = polynomial.m_coeff;
			polynomial.m_coeff = nullptr;
		}

		~Polynomial()
		{
			delete[] m_coeff;
		}

		const Polynomial& reduce()
		{

			for (int max_index = m_length-1; max_index >= 0; max_index--)
				if (m_coeff[max_index] != 0)
				{
					if (m_length != max_index+1)
					{
						m_length = max_index + 1;
						T* new_coeff = new T[m_length];
						std::swap(new_coeff, m_coeff);
						for (unsigned j = 0; j < m_length; j++) m_coeff[j] = new_coeff[j];
						delete[] new_coeff;
					}
					break;
				}
			return *this;
		}

		const Polynomial& operator+=(const Polynomial<T>& polynomial)
		{
			unsigned i = 0;
			if (m_length >= polynomial.m_length)
			{
				for (; i < polynomial.m_length; i++)
					m_coeff[i] += polynomial.m_coeff[i];
				reduce();
			}
			else
			{
				T* temp_array = new T[polynomial.m_length];
				for (; i < m_length; i++)
					temp_array[i] = m_coeff[i] + polynomial.m_coeff[i];
				delete[] m_coeff;
				m_length = polynomial.m_length;
				for (; i < m_length; i++)
					temp_array[i] = polynomial.m_coeff[i];
				m_coeff = temp_array;
				temp_array = nullptr;
			}
			return *this;
		}
		const Polynomial& operator-=(const Polynomial<T>& polynomial)
		{
			unsigned i = 0;
			if (m_length >= polynomial.m_length)
			{
				for (; i < polynomial.m_length; i++)
					m_coeff[i] -= polynomial.m_coeff[i];
				reduce();
			}
			else
			{
				T* temp_array = new T[polynomial.m_length];
				for (; i < m_length; i++)
					temp_array[i] = m_coeff[i] - polynomial.m_coeff[i];
				delete[] m_coeff;
				m_length = polynomial.m_length;
				for (; i < m_length; i++)
					temp_array[i] = -polynomial.m_coeff[i];
				m_coeff = temp_array;
				temp_array = nullptr;
			}
			return *this;
		}
		const Polynomial& operator*=(const Polynomial<T>& polynomial)
		{
			unsigned power_of_new = m_length * polynomial.m_length;
			T* new_coeff = new T[power_of_new];
			memset(new_coeff, 0, power_of_new * sizeof(T));
			for (unsigned i = 0; i < m_length; i++)
				for (unsigned j = 0; j < polynomial.m_length; j++)
					new_coeff[i + j] += (T)(m_coeff[i] * polynomial.m_coeff[j]);
			m_length = power_of_new;
			delete[]  m_coeff;
			m_coeff = new_coeff;
			new_coeff = nullptr;
			return *this;
		}

		const Polynomial& operator/=(const Polynomial<T>& polynomial)
		{
			if (polynomial.m_coeff[polynomial.m_length - 1] == 0)
				throw std::logic_error("Деление на ноль\n");

			int new_power = getPower() - polynomial.getPower();
			if (new_power < 0) return *this = 0.0;
			T* new_coeff = new T[new_power+1];

			int i = -1, j = -1;
			for ( i = 0; i < new_power + 1; i++)
			{
				new_coeff[new_power - i] = m_coeff[m_length - i - 1] / polynomial.m_coeff[polynomial.m_length - 1];
				for ( j = 0; j < static_cast<int>(polynomial.m_length); j++)
					m_coeff[m_length - j - i - 1] -= polynomial.m_coeff[polynomial.m_length - j - 1] * new_coeff[new_power - i];
				j = 0;
			}
			m_length = new_power+1;
			delete[] m_coeff;
			m_coeff = new_coeff;
			reduce();
			return *this;
		}

		const Polynomial& operator%=(const Polynomial<T>& polynomial)
		{
			if (!polynomial.getPower() && 
				 polynomial.m_coeff[polynomial.m_length - 1] == 0)
				throw std::logic_error("Деление на ноль\n");

			int new_power = getPower() - polynomial.getPower();

			if (new_power < 0) return *this;
			int i=-1, j=-1;
			for (i = 0; i < new_power + 1; i++)
			{
				T element = m_coeff[m_length - 1 - i] / polynomial.m_coeff[polynomial.m_length - 1];
				for (j = 0; j < static_cast<int>(polynomial.m_length); j++)
					m_coeff[m_length - 1 - j - i] -= polynomial.m_coeff[polynomial.m_length - 1 - j] * element;
				j=0;
				
			}
			m_length = m_length - j - i;
			reduce();
			return *this;
		}

		const Polynomial& operator=(const Polynomial<T>& polynomial)
		{
			if (this == &polynomial)
				return *this;

			if (m_length != polynomial.m_length)
			{
				delete[] m_coeff;
				m_length = polynomial.m_length;
				m_coeff = new T[m_length];
			}

			for (unsigned i = 0; i < m_length; i++)
				m_coeff[i] = polynomial.m_coeff[i];
			return *this;
		}

		const Polynomial& operator=(T number)
		{
			if (m_length != 1)
			{
				delete[] m_coeff;
				m_length = 1;
				m_coeff = new T[1];
			}

			m_coeff[0] = number;
			return *this;
		}
		const Polynomial& operator=(Polynomial<T>&& polynomial) noexcept
		{
			if (this == &polynomial)
				return *this;
			std::swap(m_length, polynomial.m_length);
			std::swap(m_coeff, polynomial.m_coeff);
			return *this;
		}

		double operator()(T arg) const
		{
			T res = 0.0;
			for (unsigned i = 0; i < m_length; i++)
				res += m_coeff[i] * std::pow(arg, i);
			return res;
		}
		T& operator[](int index)
		{
			if (index >= static_cast<int>(m_length) || static_cast<int>(m_length) + index < 0)
				throw std::invalid_argument("Индекс члена полинома больше количества членов");
			else if (index < 0)
				index += m_length;
			return m_coeff[index];
		}
		const T& operator[](int index) const
		{
			if (index >= static_cast<int>(m_length) || static_cast<int>(m_length) + index < 0)
				throw std::invalid_argument("Индекс члена полинома больше количества членов");
			else if (index < 0)
				index += m_length;
			return m_coeff[index];
		}

		friend std::ostream& operator<<(std::ostream& out, const Polynomial<T>& polynomial)
		{
			std::streamsize width = out.width();

			out.width(width);

			if (polynomial.getPower() + 1 == 1) { std::cout << polynomial.m_coeff[0]; return out; }
			//out << " ( ";
			bool flag = false;

			for (unsigned i = 0; i < polynomial.m_length; i++)
			{
				if (polynomial.m_coeff[i] == 0)
					continue;

				if (flag)
				{
					out << (polynomial.m_coeff[i] > 0 ? " + " : " - ");
					if ((polynomial.m_coeff[i] > 0 ? polynomial.m_coeff[i] : -polynomial.m_coeff[i]) /*!= 1*/)
						out << std::setw(width) << (polynomial.m_coeff[i] > 0 ? polynomial.m_coeff[i] : -polynomial.m_coeff[i]);
				}
				else
				{
					if ((polynomial.m_coeff[i] > 0 ? polynomial.m_coeff[i] : -polynomial.m_coeff[i]) /*!= 1 */|| !i)
						out << std::setw(width) << polynomial.m_coeff[i];
					flag = true;
				}

				if (i == 1)     out << "*x";
				else if (i > 1)
				{
					for (unsigned j = 0; j < i; j++)
						out << "*x";
				}
			}
			// out << " ) ";
			return out;
		}

		std::string to_string() 
		{
			std::stringstream ss;
		
			ss << *this;
			return ss.str();
		}

		friend std::istream& operator>>(std::istream& in, const Polynomial<T>& polynomial)
		{
			for (unsigned i = 0; i <= polynomial.m_length; ++i)
				in >> polynomial.m_coeff[i];
			return in;
		}

		unsigned getId() const
		{
			return m_id;
		}
		int getPower() const
		{
			return m_length-1;
		}

		friend Polynomial operator*(const Polynomial<T>& p1, const Polynomial<T>& p2)
		{
			return Polynomial<T>(p1) *= p2;
		}
		friend Polynomial operator/(const Polynomial<T>& p1, const Polynomial<T>& p2)
		{
			return Polynomial<T>(p1) /= p2;
		}
		friend Polynomial operator%(const Polynomial<T>& p1, const Polynomial<T>& p2)
		{
			return Polynomial<T>(p1) %= p2;
		}
		friend Polynomial operator+(const Polynomial<T>& p1, const Polynomial<T>& p2)
		{
			return Polynomial<T>(p1) += p2;
		}
		friend Polynomial operator-(const Polynomial<T>& p1, const Polynomial<T>& p2)
		{
			return Polynomial<T>(p1) -= p2;
		}
		
	};

	template <class T> unsigned Polynomial<T>::s_idCounter = 0;
}