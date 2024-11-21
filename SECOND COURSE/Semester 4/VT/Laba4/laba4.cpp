#include <iostream>

/*
На промежутке от -128 до 127. 
Подсчитать количество таких пар чисел X и У,
что (Х * У - (X div 2)) = 0. Ответ вывести на экран.
*/

int main()
{

	__int16 counter = 0;
	__int8 X, Y;
	__int8 X_temp, Y_temp;
	bool flag = false;
	const char* msg = "\nThe number of pairs is less than 200";

	_asm
	{
		        
        mov X, -128 // X = [-128; 127]
        M1:
            
            mov Y, -128 // Y = [-128; 127]  
            M2:
                
                mov al, X   // для (->_X_ div    2 )
                cbw
                mov dl, 2;           // для (   X  div ->_2_)
                idiv dl             // (even part)AL = AX / DL---> AL (X div 2)
                cbw
                // сохраняем (X div 2)
                push ax     // --------------------------> AX (X div 2)
               
                mov al, X // X(byte) 
                cbw
                imul Y // AL * Y(byte) => AX
                pop dx // pop (X div 2)
                //sub ax, dx
                sub al, dl // (Х * У) – (X div 2)
                sbb ah, dh
                cmp ax, 0
                jne M3
                    inc counter
                    cmp counter, 200
                    jne M3
                        cmp flag, 1
                        je M3
                            mov flag, 1
                            mov al, X
                            mov X_r, al
                            mov al, Y
                            mov Y_r, al
                M3:
                
            inc Y
            cmp Y, -128
                jne M2
              
        inc X
        cmp X, -128
        jne M1
	};

	std::cout << "\nNumber of pairs: " << static_cast<int>(counter);
	if (flag)
		std::cout << "\n200-th pair\nx = " << static_cast<int>(X_r) << "; y = " << static_cast<int>(Y_r) << std::endl;
	else
		std::cout << msg;


	flag = false;
	counter = 0;
	int RX, RY;
	for (int i = -128; i < 128; ++i)
		for (int j = -128; j < 128; ++j)
			if ((i * j - (i / 2)) == 0)
			{
				counter++;
				if (counter == 200 && flag == false)
				{
					flag = true;
					RX = i; RY = j;
				}
			}

	std::cout << "\nNumber of pairs: " << counter;
	if (flag)
		std::cout << "\n200-th pair\nx = " << RX << "; y = " << RY << std::endl;
	else
		std::cout << msg;
}
