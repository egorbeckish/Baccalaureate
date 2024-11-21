#include <iostream>
#include <time.h>
#include "Header.h"
using namespace AreaMatrix;

int main()
{
	try
	{
		srand(time(NULL));
		std::cout << "Class Matrix\n" << std::endl;

		Matrix A;
		std::cout << A << std::endl;

		Matrix B(3, 3);
		std::cout << B << std::endl;

		A = B;
		std::cout << A;
		std::cout << "------------------------ Assignment Matrix -------------------";

		Matrix C;
		std::cout << C;

		C += B;
		std::cout << C;
		std::cout << "------------------------ Addition Matrix -------------------\n" << std::endl;

		Matrix D;
		std::cout << D;

		D -= C;
		std::cout << D;
		std::cout << "------------------------ Substraction Matrix -------------------" << std::endl;

		Matrix E;
		std::cout << E;

		E *= D;
		std::cout << E;
		std::cout << "------------------------ Multiplication Matrix -------------------" << std::endl;

		int scalar = std::rand() % 10;
		Matrix F;
		std::cout << F;

		F *= scalar;
		std::cout << F;
		std::cout << "------------------------ Scalar Matrix -------------------" << std::endl;

		Matrix H(3, 4), I(3, 4);
		std::cout << H << "\n\n";
		std::cout << I;

		std::cout << H + I;
		std::cout << "------------------------Addition Matrix--------------------" << std::endl;

		Matrix G(3, 4), K(3, 4);
		std::cout << G << "\n\n";
		std::cout << K;

		std::cout << G - K;
		std::cout << "------------------------Substraction Matrix--------------------" << std::endl;



		Matrix L(3, 4), M(4, 3);
		std::cout << L << "\n\n";
		std::cout << M;

		std::cout << L * M;
		//M *= L;
		//std::cout << M;
		std::cout << "------------------------Multiplicated Matrix--------------------" << std::endl;

		std::cout << M * scalar;
		std::cout << "------------------------ Scalar Matrix -------------------\n\n" << std::endl;


		std::cout << L << '\n' << M << std::endl;
		L = std::move(M);
		std::cout << L << '\n' << M;
		std::cout << "------------------------ Swap -------------------" << std::endl;
		std::cout << "\n\n\n";
	}


	catch (std::logic_error& error) { std::cout << "Error..."; }
	
	return 0;
}
