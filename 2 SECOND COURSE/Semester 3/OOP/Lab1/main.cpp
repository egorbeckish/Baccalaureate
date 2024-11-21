#include <iostream>
#include "Vector3D.cpp"
#include <time.h>

using namespace Vector3D;

int main(int argc, char const *argv[])
{
	srand(time(NULL));

	Vector3D::Vector3D A;

	std::cout << "A" << A;

	A.set_X(5);
	A.set_Y(-2);
	A.set_Z(3);

	std::cout << "\nVector A after using set and get - ";
	std::cout << "(" << A.get_X() << ", " << A.get_Y() << ", " << A.get_Z() << ")\n\n" << std::endl;

	Vector3D::Vector3D B;
	std::cout << "B" << B;
	std::cout << "\nCopy vector with help used constructor class - ";
	B = A;
	std::cout << B;

	A.set_X(std::rand() % 20 - 10);
	A.set_Y(std::rand() % 20 - 10);
	A.set_Z(std::rand() % 20 - 10);

	std::cout << "\nCopy vector with help used method class - ";
	B = A;
	std::cout << B;

	std::cout << "\n\nLenght vector B = " << B.Lenght() << std::endl;

	A.set_X(std::rand() % 20 - 10);
	A.set_Y(std::rand() % 20 - 10);
	A.set_Z(std::rand() % 20 - 10);

	std::cout << "\nMultiplying a vector B" << B << " by a scalar:" << std::endl;
	
	double scalar = std::rand() % 3 + 1;
	std::cout << "Scalar = " << scalar << std::endl;
	
	std::cout << "Resualt = " << B.MultiplicatioScalar(scalar);

	std::cout << "\n\nA" << A << "  B" << B << std::endl;
	Vector3D::Vector3D C;
	std::cout << "\n\nC" << C << "\nAddition of vector with help method class (A + B) = " << C.AddVector(A, B);
	std::cout << "\nAddition of vector with help external function (A + B) = " << AdditionVector(A, B);

	std::cout << "\n\nSubstraction of vector with help method class (A - B) = " << C.SubVector(A, B);
	std::cout << "\nSubstraction of vector with help external function (A - B) = " << SubstractionVector(A, B);

	std::cout << "\n\nMultiplication of vector with help method class [A, B] = " << C.MultVector(A, B);
	std::cout << "\nMultiplication of vector with help external function [A, B] = " << MultiplicationVector(A, B);

	std::cout << "\n\nScalar product of vector (A ^ B) = " << ScalarProduct(A, B);

	std::cout << "\n\nSin angel beetwen vectors |A * B| / (|A| * |B|) = " << Sin(A, B);

	std::cout << "\n\nCos angel beetwen vectors (A ^ B) / (|A| * |B|) = " << Cos(A, B);

	std::cout << "\n\nValue angel vectors tg(|A * B|, (A ^ B)) * 180 / pi = " << Angle(A, B);

	std::cout << "\n\nNormalized vector B - " << C.NormalizedVector();
	std::cout << "\n" << std::endl;

	return 0;
}
