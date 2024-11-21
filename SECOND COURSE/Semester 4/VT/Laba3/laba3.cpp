#include <iostream>
#include <time.h>

int main()
{
	srand(time(NULL));

	/*
	11) A(dword), B(word), C(byte)
		D = (B * C) + A
		E = (B - C) / (B - A)
	*/

	__int32 A = std::rand() % 10000 - 7000;
	__int16 B = std::rand() % 1000 - 500;
	__int8 C = std::rand() % 100 - 50;

	int a = A, b = B, c = C, d, e;

	d = (b * c) + a;
	e = ((b - c) / b) - a;
	
	std::cout << "A = " << A << std::endl;
	std::cout << "B = " << B << std::endl;
	std::cout << "C = " << static_cast<int>(C) << std::endl;

	std::cout.unsetf(std::ios::dec);
    std::cout.setf(std::ios::hex);


	std::cout << "\nA = " << A << std::endl;
	std::cout << "B = " << B << std::endl;
	std::cout << "C = " << static_cast<int>(C) << std::endl;


	__int32 D; // (B * C) + A
	__int32 E; // ((B - C) / B) - A

	
	__asm
	{
		// Число D

		mov al, byte ptr C;		// В регистр AL поместили значение C
		cbw;					// Расширили AL до AX, т.к B занимает AX
		imul B;					// Умножаем B * C
		mov B, ax;				// Помещаем результат (B * C) в регистр АХ

		add ax, word ptr A; 	// Добавляем в регистр AX = (B * C), число А
		adc dx, word ptr A[2];	// Выполняем сложение с переносом, записываем старшую часть числа А
								// Команда ADD выполняет целочисленное сложение двух операндов и флага переноса CF. 
								// Результат сложения помещается в первый операнд и выполняется соответствующая установка флагов. 
								// Команда ADC обычно выполняется как часть операции сложения, 
								// работающей с несколькими байтами или словами.

		mov word ptr D, ax; 	// помещаем в D результат (B * C) + А младшую часть
		mov word ptr D[2], dx;	// помещаем в D результат (B * C) + А старшую часть

		// -----------------------------------------------------------------------------------

		// Число Е
		mov ax, word ptr B;		// Помещаем значение B в регистр АХ
		movsx dx, byte ptr C;	// копируем байт(значение С) из С в регистр DX
								// Команда MOVSB копирует один байт из ячейки памяти по адресу DS:SI
								// в ячейку памяти по адресу ES:DI.
								// После выполнения команды, регистры SI и DI увеличиваются на 1, если флаг DF = 0, 
								// или уменьшаются на 1, если DF = 1.
								// Если команда используется в 32-разрядном режиме адресации,
								// то используются регистры ESI и EDI соответственно.

		sub ax, dx; 			// Делаем вычитание (B - C)
		cwd;					// AX = (DX : AX) - переводим в число double для дальнейшего деления
		idiv B; 				// Делим AX = (AX - DX) = (B - C) на B
		cwde;					// то же самое, что и cwd только со знаковым значением
		sub eax, A;				// Полученное значение ((B - C) - B) делаем вычитание с А
		mov E, eax;				// помещаем результат в Е
	};

	std::cout << "\nD = " << D << std::endl;
	std::cout << "E = " << E << std::endl;

	std::cout.unsetf(std::ios::hex);
	std::cout.setf(std::ios::dec);

	std::cout << "\nD = " << D << std::endl;
	std::cout << "E = " << E << std::endl;

	std::cout << "\nd = " << d << std::endl;
	std::cout << "e = " << e << std::endl;
	
	system("pause");
	return 0;
}
