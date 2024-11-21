#include <iostream>

int main()
{
	long int A = 0x11223344;
	int B = 0x5566;

	std::cout.unsetf(std::ios::dec);
	std::cout.setf(std::ios::hex);

	std::cout << A << "\n" << B << "\n\n";
	asm
	{
		mov al, byte ptr A[1]   ; //A(33) = 2-байт => AL(1 байт)
		xchg byte ptr B[1], al  ; //AL(33) <=> B(55) = 2-й байт // B = 33'66, AL(55)
		xchg byte ptr A[3], al  ; //AL(55) <=> A(11) = 3-й байт // A = 55'22'33'44, AL(11)
		xchg byte ptr B,   al  ; //AL(11) <=> B(66) = 1-й байт // B = 33'11, AL(66)
		mov byte ptr A[1],  al  ; //AL(66) <=> A(33) = 2-й байт // A = 55'22'66'44, AL(66)
	};


	A = 0x55226644;
	B = 0x3311;

	std::cout.unsetf(std::ios::dec);
	std::cout.setf(std::ios::hex);

	std::cout << A << "\n" << B << "\n";
	
	
	return 0;
}
