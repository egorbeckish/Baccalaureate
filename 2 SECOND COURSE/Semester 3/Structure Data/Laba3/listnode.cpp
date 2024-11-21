#include "listnode.h"
#include <iostream>

namespace StructureData
{
	int ListNode::l_value_id = 1;

	ListNode::ListNode() : l_id{l_value_id++}
	{
		// std::cout << "init list №" << l_id << "\n";
		Begin = NULL;
	}

	ListNode::~ListNode()
	{
		// std::cout << "delete list №" << l_id << "\n";
		Node* p = Begin;
		while (p)
		{
			Node* q = p->l_next;
			p->l_info = 0;
			p->l_next = NULL;
			p = q;
		}
	}

	void ListNode::Insert_Begin(Node* p, int element)
	{
		Node* q = new Node;
		q->l_info = element;
		q->l_next = p;
		Begin = q;
	}

	void ListNode::Insert(int element)
	{
		if (Begin) { Insert_Begin(Begin, element); }
		else
		{
			Begin = new Node;
			Begin->l_info = element;
			Begin->l_next = NULL;
		}
	}

	void ListNode::Show(Node* p)
	{
		while (p)
		{
			std::cout << p->l_info << " ";
			p = p->l_next;
		}
	}

	int ListNode::Delete(Node* p)
	{
		Node* q = p->l_next;
		int value = q->l_info;
		p->l_next = q->l_next;
		delete q;

		return value;
	}
	
	Node* ListNode::FindItem(int element)
	{
		Node* p = Begin;
		while (p)
		{
			if (p->l_info == element) { std::cout << "Congratulations item is found\n"; return p; }
			p = p->l_next;
		}

		std::cout << "Not found this is item!!!\n";
		exit(0);
	}
}
