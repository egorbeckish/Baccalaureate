#include "queueNode.h"
#include <iostream>

namespace StructureData
{
	//Указатель на начальный элемент очереди
	QueueNode* QueueNode::q_BeginEven{ nullptr };
	QueueNode* QueueNode::q_BeginOdd{ nullptr };

	//Указатель на конечный элемент очереди
	QueueNode* QueueNode::q_EndEven{ nullptr };
	QueueNode* QueueNode::q_EndOdd{ nullptr };

	
	QueueNode::QueueNode() : q_info{ 0 }, q_next{nullptr}{}
	

	// Добавить элемент в очередь
	const QueueNode& QueueNode::EnQueueEven(int x)
	{
		QueueNode* p = new QueueNode;
		if (p)
		{
			p -> q_info = x;
			p -> q_next = nullptr;

			if (q_BeginEven == nullptr) { q_BeginEven = p; }
			else { q_EndEven -> q_next = p; }
			q_EndEven = p;
		}

		else exit(EOF);
		return *this;
	}

	const QueueNode& QueueNode::EnQueueOdd(int x)
	{
		QueueNode* p = new QueueNode;
		if (p)
		{
			p -> q_info = x;
			p -> q_next = nullptr;

			if (q_BeginOdd == nullptr) { q_BeginOdd = p; }
			else { q_EndOdd -> q_next = p; }
			q_EndOdd = p;
		}

		else exit(EOF);
		return *this;
	}


	// Возвратить первый элемент очереди
	int QueueNode::DeQueueEven()
	{
		int value;
		QueueNode* p = new QueueNode;
		if (p)
		{
			p = q_BeginEven;
			if (q_BeginEven == nullptr)
			{
				std::cout << "\nОчередь закончилась\n";
				return 0;
			}

			else
			{
				value = q_BeginEven -> q_info;
				q_BeginEven = p -> q_next;
				if (q_BeginEven == nullptr) { q_EndEven = nullptr; }
			}
			
			delete p;
		}

		else exit(EOF);
		return value;
	}

	int QueueNode::DeQueueOdd()
	{
		int value;
		QueueNode* p = new QueueNode;
		if (p)
		{
			p = q_BeginOdd;
			if (q_BeginOdd == nullptr)
			{
				std::cout << "\nОчередь закончилась\n";
				return 0;
			}

			else
			{
				value = q_BeginOdd -> q_info;
				q_BeginOdd = p -> q_next;
				if (q_BeginOdd == nullptr) { q_EndOdd = nullptr; }
			}
			
			delete p;
		}

		else exit(EOF);
		return value;
	}

	bool QueueNode::IsEmptyEven()
	{
		if (q_BeginEven == nullptr) { return true; }
		else { return false; }
	}

	bool QueueNode::IsEmptyOdd()
	{
		if (q_BeginOdd == nullptr) { return true; }
		else { return false; }
	}

	bool QueueNode::IsFullEven()
	{
		if (q_BeginEven == 0) { return true; }
		else { return false; }
	}

	bool QueueNode::IsFullOdd()
	{
		if (q_BeginOdd == 0) { return true; }
		else { return false; }
	}

	int QueueNode::Top()
	{
		if (IsEmptyEven() && IsEmptyOdd())
		{
			exit(EXIT_FAILURE);
		}

		return q_info;
	}
}
