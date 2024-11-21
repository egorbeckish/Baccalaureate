#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#define INDEX_NOT_FOUND -1

class HashTable
{
private:
	std::vector<std::pair<std::string, bool>> _table;
public:
	HashTable()
	{
	}

	size_t size() const
	{
		return _table.size();
	}
	HashTable& resize(size_t size)
	{
		_table.resize(size);
		return *this;
	}
	HashTable& reserve(size_t capacity)
	{
		_table.reserve(capacity);
		return *this;
	}


	static unsigned string_to_int(std::string string)
	{
		unsigned stringInt = 0;
		for (auto it = string.begin(); it != string.end(); it++)
			stringInt += (unsigned char)*it;
		return stringInt;
	}
	unsigned hash(std::string element) const { return string_to_int(element) % _table.capacity(); }
	unsigned hashLinear(unsigned hash, unsigned index) const { return (hash + index) % _table.capacity(); }

	unsigned hashQuadratic(unsigned hash, unsigned index) const { return (hash + index * index) % _table.capacity(); }

	unsigned hashDouble(unsigned hash, unsigned index) const { return (hash + index * (1 + hash)) % _table.capacity(); }


	const std::string& operator[](int index) const
	{
		return _table[index].first;
	}
	std::string& operator[](int index)
	{
		return _table[index].first;
	}

	HashTable& insert(std::string string)
	{
		int hash_i = hash(string), index;
		for (int i = 0; i != _table.capacity(); i++)
		{
			index = hashQuadratic(hash_i, i);
			if (_table[index].first == "")
			{
				_table[index].first = string;
				_table[index].second = true;
				std::cout << "Количество проб: " << i << std::endl;
				return *this;
			}
		}
		std::cout << "Таблица переполнена\n";
		return *this;
	}

	HashTable& del(std::string string)
	{
		int index = search(string);
		if (index != INDEX_NOT_FOUND)
		{
			_table[index].first = "";
			_table[index].second = false;
		}
		return *this;
	}
	int search(std::string string)
	{
		int index, i = 0, hash_i = hash(string);
		do {
			index = hashQuadratic(hash_i, i);
			if (_table[index].first == string)
			{
				std::cout << "Количество проб: " << i << std::endl;
				return index;
			}
			i++;
		} while ((i < _table.capacity()) && (_table[index].first != "" || _table[index].second == false));
		std::cerr << "Данное слово не найдено в хеш-таблице\n";
		return INDEX_NOT_FOUND;
	}



	friend std::ostream& operator<<(std::ostream& out, const HashTable& T)
	{
		for (int i = 0; i < T.size(); i++)
			out << i << ": " << T[i] << std::endl;

		return out;
	}

	friend std::istream& operator>>(std::istream& in, HashTable& T)
	{
		std::string word;
		in >> word;
		if (!word.empty())
			T.insert(word);
		return in;
	}

	friend std::ofstream& operator<<(std::ofstream& out, const HashTable& T)
	{
		for (int i = 0; i < T.size(); i++)
			out << i << ": " << T[i] << std::endl;

		return out;
	}
	friend std::ifstream& operator>>(std::ifstream& in, HashTable& T)
	{
		std::string word;
		in >> word;
		if (!word.empty())
			T.insert(word);
		return in;
	}
};
