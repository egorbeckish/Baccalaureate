#pragma once
#include <iostream>
#include <cassert> 
#include <utility>

namespace Graphs
{
	template <class T>
	class ListNode
	{
	private:
		T* _info;                
		ListNode<T>* _next;      
		ListNode<T>* _endList;   
		size_t _size;
	public:
		ListNode() : _info{ NULL }, _next{ NULL }, _endList{ NULL } { }

		ListNode(T info) : ListNode<T>()
		{
			_info = new T;
			*_info = info;
			_size++;
		}

		ListNode(const ListNode<T>& List) : ListNode<T>()
		{
			const ListNode<T>* temp = &List;
			while (temp != NULL)
			{
				append(*(temp->_info));
				temp = temp->_next;
			}
		}

		~ListNode()
		{
			while (this->_next != NULL) deleteNode(this);
			delete _info;
		}
		bool isEmpty() { return !_info; }

		ListNode* getNext() { return _next; }
		size_t getSize() const { return _size; }

		
		ListNode* append(T item)
		{
			ListNode<T>* currentItem = new ListNode<T>(item);
			_size++;
			if (!_info)
			{
				*this = *currentItem;
				_endList = this;
			}
			else
			{
				_endList->_next = currentItem; 
				_endList = _endList->_next;    
			}
			return this;
		}


		
		ListNode* insert(ListNode<T>* p, T i)
		{
			_size++;
			ListNode<T>* q = new ListNode<T>;
			assert(q && "Ïàìÿòü íå âûäåëèëàñü!!!");
			q->l_info = i;
			if (!p)
				p = q;
			else
			{
				q->l_next = p->l_next;
				p->l_next = q;
			}
			return this;
		}

		
		ListNode<T>* find(const T& element)
		{
			ListNode<T>* prev_temp = this;
			if (*(prev_temp->_info) == element)
				return prev_temp;

			const ListNode<T>* curr_temp = this;
			for (int i = 1; i < _size; i++)
			{
				curr_temp = curr_temp->_next;
				if (*(curr_temp->_info) == element)
					return prev_temp;
				prev_temp = prev_temp->_next;
			}
			return NULL;
		}

		T& operator[](int index) const
		{
			const ListNode<T>* temp = this;
			for (int i = 0; i < index; i++)
				temp = temp->_next;

			return *(temp->_info);
		}

		
		T deleteNode(ListNode<T>* p)
		{
			if (p && p->_next)
			{
				_size--;
				T val = *(p->_next->_info);
				delete p->_next->_info;
				p->_next = p->_next->_next;
				return val;
			}
			else return -1;
		}

		
		friend std::ostream& operator<<(std::ostream& out, const ListNode<T>& node)
		{
			const ListNode<T>* temp = &node;
			std::cout << "_|" << *(temp->_info) << "| -> ";
			temp = temp->_next;
			while (temp)
			{
				std::cout << *(temp->_info) << " -> ";
				temp = temp->_next;
			}
			std::cout << "NULL\n_|_\n";
			return out;
		}

		const ListNode<T>& operator=(T item)
		{
			if (!_info) _info = new T;
			*_info = item;
			return *this;
		}
	};


	template <class T>
	class ListNode<std::pair<T, T>>
	{
	private:
		std::pair<T, T>* _info;                
		ListNode<std::pair<T, T>>* _next;      
		ListNode<std::pair<T, T>>* _endList;   
		size_t _size;
	public:
		ListNode() : _info{ NULL }, _next{ NULL }, _endList{ NULL } { }

		ListNode(std::pair<T, T> info) : ListNode<std::pair<T, T>>()
		{
			_info = new std::pair<T, T>;
			*_info = info;
			_size++;
		}

		ListNode(const ListNode<std::pair<T, T>>& List) : ListNode<std::pair<T, T>>()
		{
			const ListNode<std::pair<T, T>>* temp = &List;
			while (temp != NULL)
			{
				append(*(temp->_info));
				temp = temp->_next;
			}
		}

		~ListNode()
		{
			while (this->_next != NULL) deleteNode(this);
			delete _info;
		}
		bool isEmpty() { return !_info; }

		ListNode<std::pair<T, T>>* getNext() { return _next; }
		size_t getSize() const { return _size; }

		
		ListNode<std::pair<T, T>>* append(std::pair<T, T> item)
		{
			ListNode<std::pair<T, T>>* currentItem = new ListNode<std::pair<T, T>>(item);
			_size++;
			if (!_info)
			{
				*this = *currentItem;
				_endList = this;
			}
			else
			{
				_endList->_next = currentItem; 
				_endList = _endList->_next;   
			}
			return this;
		}


		
		ListNode<std::pair<T, T>>* insert(ListNode<std::pair<T, T>>* p, std::pair<T, T> i)
		{
			_size++;
			ListNode<std::pair<T, T>>* q = new ListNode<std::pair<T, T>>;
			assert(q && "Ïàìÿòü íå âûäåëèëàñü!!!");
			q->l_info = i;
			if (!p) 
				p = q;
			else
			{
				q->l_next = p->l_next;
				p->l_next = q;
			}
			return this;
		}

		
		ListNode<std::pair<T, T>>* find(const std::pair<T, T>& element)
		{
			ListNode<std::pair<T, T>>* prev_temp = this;
			if (*(prev_temp->_info) == element)
				return prev_temp;

			const ListNode<std::pair<T, T>>* curr_temp = this;
			for (int i = 1; i < _size; i++)
			{
				curr_temp = curr_temp->_next;
				if (*(curr_temp->_info) == element)
					return prev_temp;
				prev_temp = prev_temp->_next;
			}
			return NULL;
		}

		std::pair<T, T> find(const T& element)
		{
			ListNode<std::pair<T, T>>* prev_temp = this;
			if (prev_temp->_info->first == element)
				return *(prev_temp->_info);

			prev_temp = prev_temp->_next;
			for (int i = 1; i < _size && prev_temp; i++)
			{
				if (prev_temp->_info->first == element)
					return *(prev_temp->_info);
				prev_temp = prev_temp->_next;
			}
			return std::pair<T, T>(INT_MAX, INT_MAX);
		}

		std::pair<T, T>& operator[](int index) const
		{
			const ListNode<std::pair<T, T>>* temp = this;
			for (int i = 0; i < index; i++)
			{
				if (temp->_next) temp = temp->_next;
				else
				{
					std::pair<T, T>* t = new std::pair<T, T>(0, 0);
					return *t;
				}
			}
			return *(temp->_info);
		}

		
		std::pair<T, T> deleteNode(ListNode<std::pair<T, T>>* p)
		{
			if (p && p->_next)
			{
				_size--;
				std::pair<T, T> val = *(p->_next->_info);
				delete p->_next->_info;
				p->_next = p->_next->_next;
				return val;
			}
			else return std::pair<T, T>();
		}

		friend std::ostream& operator<<(std::ostream& out, const ListNode<std::pair<T, T>>& node)
		{
			const ListNode<std::pair<T, T>>* temp = &node;
			out << "_|" << temp->_info->first << "| -> ";
			temp = temp->_next;
			while (temp)
			{
				out << '\'' << temp->_info->first << "\': " << temp->_info->second << "\t -> ";
				temp = temp->_next;
			}
			out << "NULL\n_|_\n";
			return out;
		}


		const ListNode<std::pair<T, T>>& operator=(std::pair<T, T> item)
		{
			if (!_info) _info = new std::pair<T, T>;
			*_info = item;
			return *this;
		}
	};
}
