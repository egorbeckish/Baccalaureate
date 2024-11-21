#include <iostream>
#include "abstract.h"


using namespace VectorMatrix;

int main()
{
	setlocale(LC_ALL, "Russian");
	std::srand(time(NULL));
	std::cout << "Succses" << std::endl;



	MyVector a;
	MyMatrix b(1, 3);

	std::cout << a << '\n' << b << '\n';
	std::cout << a[2][0] << '\n';
	a *= b;

	std::cout << a;
}
