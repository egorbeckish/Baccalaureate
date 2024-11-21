#include <iostream>
#include <time.h>
#include "listnode.cpp"

using namespace StructureData;


int main(int argc, char const *argv[])
{
	srand(time(NULL));
	ListNode L1;
	ListNode L2;
	ListNode L;
	
	
	for (int i = 0 ; i < std::rand() % 30 + 10; ++ i)
	{
		L1.Insert(std::rand() % 30);
		L2.Insert(std::rand() % 40);
	}


	Node* l1 = L1.Begin;
	Node* l2 = L2.Begin;

	std::cout << "List L1 - [ ";
	L1.Show(l1);
	std::cout << "]" << std::endl;

	std::cout << "List L2 - [ ";
	L2.Show(l2);
	std::cout << "]" << std::endl;

	l1 = L1.Begin;
	l2 = L2.Begin;
	
	while (l1)
	{
		bool flag = true;
		while (l2)
		{
			if (l1->l_info == l2->l_info) 
			{
				Node* l = L.Begin;
				while (l)
				{
					if (l1->l_info == l->l_info) { flag = false; break; }
					l = l->l_next;
				}
				// L.Insert(l1->l_info);
				if (flag) { L.Insert(l1->l_info); }
			}
			// std::cout << q->l_info << " ";
			l2 = l2->l_next;
		}
		l2 = L2.Begin;
		// std::cout << p->l_info << " ";
		// std::cout << std::endl;
		
		l1 = l1->l_next;
	}


	Node* l = L.Begin;
	std::cout << "List L - [ ";
	L.Show(l);
	std::cout << "]" << std::endl;

	int finditem = std::rand() % 30;
	std::cout << "\nFind item - " << finditem << std::endl;
	L.FindItem(finditem);

	return 0;
}
