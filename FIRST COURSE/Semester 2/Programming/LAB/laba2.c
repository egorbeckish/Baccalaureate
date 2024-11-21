#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <locale.h>
#include <stdint.h>
#include <time.h>




                                          // 1. Написать функцию char *stoupper( char *str ), приводящую все содержащиеся
                                          // в строке буквы (как латинские, так и кириллицу) к верхнему регистру. Функция
                                          // возвращает значение str.		


                                          // 2. Написать функцию int stonum( char *str ), преобразующую строку цифр str
                                          // (возможен ведущий знак ‘+’ или ‘-‘) в число типа int.


                                          //3. Написать функцию char *numtos ( int num ), преобразующую число типа int в его
                                          // цифровую запись str (возможен ведущий знак ‘+’ или ‘-‘).




char* stoupper(char *str)
{	
	int i = 0;

	while (str[i] != '\0')
	{

		if (((str[i] >= (char)(97)) && (str[i] <= (char)(122))) || ((str[i] >= (char)(224)) && (str[i] <= (char)(255))))
		{
			str[i] = (char)(str[i] - 32);
		}

		if (str[i] == (char)(184))
		{
			str[i] = (char)(168);
		}

		i ++;
	}

	return str;
}


int stonum(char *str)
{
	int znak = 1,
        i = 0,
		digit = 0;

	if (str[0] == '-')
	{
		i ++;
		znak = -1;
	}

	if (str[0] == '+')
    {
        i ++;
    }

	for (i; i < strlen(str); i ++)
	{
		digit = (digit * 10) + (int)(str[i] - '0');
	}

	return (digit * znak);
}



char *numtos(int num)
{
	int temp = num,
		counter = 0;

	if (num < 0) temp *= -1;

	while (temp != 0)
	{
		counter ++;
		temp /= 10;
	}

	char *str = (char *)calloc(counter + 2, sizeof(char));
	str[counter + 1] = '\0';

	str[0] = '+';
	if (num < 0) {str[0] = '-'; num *= - 1;}
	if (num == 0) {str[0] = '0'; return str;}

	for (int i = counter; i > 0; i --)
	{
		str[i] = (num % 10) + '0';
		num /= 10;
	}

	return str;
}



char *bintoced(char *num)
{	
	int temp = 0,
		power = 0,
		znak = 1;

	if (num[0] == '-') znak = -1;

	for (int i = strlen(num) - 1; i > -1; i --)	
	{
		if (num[i] == '1')
		{
			temp += pow(2, power);
		}
		power += 1;
	}

	char *string_bin = numtos(temp * znak);
	return string_bin;
}




int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

	int choise;
	printf("Select tasks:\n" 
			"\t1 - stoupper\n\t2 - stonum\n\t3 - numtos\n\t4 - bintodec\n\t0 - close\n\n");
	scanf("%i", &choise);


    if (choise == 1)
    {
		// 1. Написать функцию char *stoupper( char *str ), приводящую все содержащиеся
		// в строке буквы (как латинские, так и кириллицу) к верхнему регистру. Функция
		// возвращает значение str.		
        
		char *string = (char *)calloc(100, sizeof(char));

        printf("Originall string - ");
        fflush(stdin);		// очистка буфера перед вводом
        gets(string);

        char *up_string = stoupper(string);
        printf("Conversion string - ");
        puts(up_string);

        free(string);
        free(up_string);
    }

    if (choise == 2)
    {
		// 2. Написать функцию int stonum( char *str ), преобразующую строку цифр str
		// (возможен ведущий знак ‘+’ или ‘-‘) в число типа int.

    	char *string_numbers = (char *)calloc(100, sizeof(char));

    	printf("Originall digit string - ");
        fflush(stdin);
        gets(string_numbers);
        fflush(stdin);

        printf("Conversion digit string - %i", stonum(string_numbers));

        free(string_numbers);
    }

    if (choise == 3)
    {
  		//3. Написать функцию char *numtos ( int num ), преобразующую число типа int в его
		// цифровую запись str (возможен ведущий знак ‘+’ или ‘-‘).

    	int digit;
    	// printf("Select types number: +/-\n");
    	// getchar();
    	// fflush(stdin);

    	// if (getchar() == '+') {digit = rand() % 100000000;}
    	// else {digit = -100000000 + rand() % 10000000;}
    	scanf("%i", &digit);
    	printf("Number is integer - %i\n", digit);

    	char *string_digit = numtos(digit);
    	printf("Number is string - ");
    	puts(string_digit);

    	free(string_digit);
    }


    if (choise == 4)
    {	
  		//4. Написать функцию char *bintodec ( char *bin ), преобразующую двоичную запись
		// целого положительного числа (строка bin) в строку, изображающую десятичную
		// запись этого же числа.
    	
    	char *bin = (char *)calloc(50, sizeof(char));
    	printf("Enter bin code - ");
    	fflush(stdin);
    	gets(bin);
		fflush(stdin);

		char *string_bin = bintoced(bin);
		printf("Bin code type of string - ");
		puts(string_bin);

		free(bin);
		free(string_bin);    	
    }

    return 0;
}
