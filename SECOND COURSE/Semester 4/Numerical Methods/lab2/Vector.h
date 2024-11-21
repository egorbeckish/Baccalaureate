#pragma once

#include "Base.h"

namespace Base
{
	template <class T> class Vector
		: virtual public Base<T>
	{
	private:
		unsigned m_length;

	public:
		using Base<T>::m_rows;
		using Base<T>::m_cols;
		using Base<T>::m_item;
		using Base<T>::m_id;

		Vector() : Base<T>(), m_length(0) {}

		Vector(int length, const T* items = NULL, bool transpose = false) //если transpose=true - то вектор-столбец
			: Base<T>(1, length, items), m_length(length)
		{
			if (transpose)
				transposition();
		}

		Vector(const std::initializer_list<T> list, bool transpose = false)
			: Base<T>(list, 1, list.size()), m_length(list.size())
		{
			if (transpose)
				transposition();
		}

		Vector(int length, T(*func)(T, T), T min = 0, T max = 100, bool transpose = false)
			: Base<T>(1, length), m_length(length)
		{
			for (unsigned iii = 0; iii < m_length; ++iii)
				m_item[iii] = func(min, max);
			if (transpose)
				transposition();
		}


		Vector(const Vector<T>& fromVector) noexcept
		{
			Vector<T>::operator=(fromVector);
		}
		Vector(Vector<T>&& fromVector) noexcept
		{
			Vector<T>::operator=(std::move(fromVector));
		}
		Vector(const Base<T>& fromBase) noexcept
		{
			Vector<T>::operator=(fromBase);
		}
		Vector(Base<T>&& fromBase) noexcept
		{
			Vector<T>::operator=(std::move(fromBase));
		}
		virtual ~Vector() noexcept {	}

		unsigned getLength(void) const
		{
			return m_length;
		}


		const Vector& normVec()
		{
			T _module = Base<T>::getModule();
			for (unsigned iii = 0; iii < m_length; ++iii)
				m_item[iii] /= _module;
			return *this;
		}
		const Vector& transposition()
		{
			std::swap(m_rows, m_cols);
			return *this;
		}

		const T& operator[](int index) const
		{
			if (index >= m_length || m_length + index < 0)
				throw std::out_of_range("Номер индекса выходит за пределы вектора №" + std::to_string(m_id) + '\n');
			else if (index < 0)
				index += m_length;
			return m_item[index];
		}

		T& operator[](int index)
		{
			if (index >= static_cast<int>(m_length) || static_cast<int>(m_length) + index < 0)
				throw std::out_of_range("Номер индекса выходит за пределы вектора №" + std::to_string(m_id) + '\n');
			else if (index < 0)
				index += m_length;
			return m_item[index];
		}


		const Vector& operator*=(const Vector<T>& onVector)
		{
			if (m_cols == 1 && onVector.m_rows == 1)
				throw std::logic_error("Преобразования вектора в матрицу\n");
			else
				Base<T>::operator*=(onVector);
			return *this;
		}
		const Vector<T>& operator*=(const Base<T>& onBase)
		{
			if (isMatrix(onBase))
				throw std::logic_error("Преобразования вектора в матрицу\n");
			Vector<T>::operator*=(Vector<T>(onBase));
			return *this;
		}

		const Vector<T>& operator=(int x) noexcept
		{
			for (unsigned iii = 0; iii < m_length; iii++)
				m_item[iii] = x;
			return *this;
		}

		const Vector<T>& operator=(const Vector<T>& fromVector) noexcept
		{
			Base<T>::operator=(fromVector);
			m_length = fromVector.m_length;
			return *this;
		}

		const Vector<T>& operator=(Vector<T>&& fromVector) noexcept
		{
			Base<T>::operator=(fromVector);
			std::swap(m_length, fromVector.m_length);
			return *this;
		}

		const Vector<T>& operator=(const Base<T>& fromBase) noexcept
		{
			if (isMatrix(fromBase))
				throw std::invalid_argument("Вектор не может быть инициализирован матрицей\n");
			Base<T>::operator=(fromBase);
			m_length = m_rows > 1 ? m_rows : m_cols;
			return *this;
		}

		const Vector<T>& operator=(Base<T>&& fromBase)
		{
			if (isMatrix(fromBase))
				throw std::invalid_argument("Обмен данными невозможен!\n");
			Base<T>::operator=(std::move(fromBase));
			m_length = m_rows > 1 ? m_rows : m_cols;
			return *this;
		}

	};

}