#include <iostream>


void binary(unsigned char *ptr, int bites)
{
	for (int i = bites - 1; i >= 0; -- i)
	{
		for (int j = 8 - 1; j >= 0; -- j)
			std::cout << (ptr[i] >> j) % 2;

		std::cout << " ";
	}

	std::cout << std::endl;
}
