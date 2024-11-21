#include <iostream>
#include <fstream>
#include "QueueNode.cpp"

using namespace StructureData;

int main(int argc, char const *argv[])
{
	std::ifstream input("input.txt");
	if (!input.is_open())
	{
		std::cout << "File is close, can't be work!" << std::endl;
	}

	else
	{
		std::cout << "File is open, can be work!" << std::endl;	

		QueueNode queuenode_even;
		QueueNode queuenode_odd;
 
		int number, counter_even = 0, counter_odd = 0;
		std::cout << "\nFile contents - ";
		while (!input.eof())
		{
			input >> number;

			if (number % 2 == 0)
			{
				// std::cout << number << " ";
				queuenode_even.EnQueueEven(number);
				counter_even ++;
			}

			else
			{
				queuenode_odd.EnQueueOdd(number);
				counter_odd ++;
			}

			std::cout << number << " ";
		}
		std::cout << std::endl;

		std::cout << "\nCounter even elements - " << counter_even << std::endl;
		std::cout << "Counter odd elements - " << counter_odd << std::endl;


		std::cout << "\nQueue even elements - [ ";
		for (; counter_even; -- counter_even)
			std::cout << queuenode_even.DeQueueEven() << " ";
		std::cout << "]";


		std::cout << "\nQueue odd elements - [ ";
		for (; counter_odd; -- counter_odd)
			std::cout << queuenode_odd.DeQueueOdd() << " ";
		std::cout << "]\n\n";

	}
	return 0;
}
