#include <stdio.h>
#include <stdlib.h>
#include <math.h>


                                                  // Ваш компьютер «не знает» арифметики вещественных чисел. Научите его
                                                  // выполнять операции сложения, вычитания и умножения чисел с плавающей
                                                  // точкой, используя только функции для работы с символами и строками
                                                  // и операции целочисленной арифметики.


                                                  // Для этого определите структурный тип данных DECIMAL для
                                                  // представления конечной десятичной дроби, и напишите функции
                                                  //              DECIMAL summarize(DECIMAL, DECIMAL),
                                                  //              DECIMAL subtract(DECIMAL, DECIMAL),
                                                  //              DECIMAL multiply(DECIMAL, DECIMAL),
                                                  // которые возвращают значения суммы, разности и произведения значений
                                                  // типа DECIMAL.




typedef struct 
{
	int entire;			// целая часть
	int fraction;		// дробная часть
	int fallibility;	// погрешность

} DECIMAL;



int power(int number, int degree)
{
	int result = 1;

	for (int i = 0; i < degree; i ++)
	{
		result *= number;
	}

	return result;
}



DECIMAL take_value(int entire, int fraction, int fallibility)
{
	DECIMAL number;

	number.fallibility = fallibility;
	number.fraction = fraction;
	number.entire = entire;

	return number;
}




DECIMAL summarize(DECIMAL first, DECIMAL second)
{
	DECIMAL sum;

	int difference;

	if (first.fallibility < second.fallibility)
	{
		difference = fabs(first.fallibility - second.fallibility);
		first.fallibility += difference;
		first.fraction *= power(10, difference);


		sum.fallibility = first.fallibility;
		sum.entire = first.entire + second.entire;
		sum.fraction = first.fraction + second.fraction;

		if (sum.fraction > power(10, sum.fallibility))
		{
			sum.entire += 1;
			sum.fraction -= power(10, sum.fallibility);
		}
	}


	else if (first.fallibility > second.fallibility)
	{
		difference = fabs(first.fallibility - second.fallibility);
		second.fallibility += difference;
		second.fraction *= power(10, difference);


		sum.fallibility = first.fallibility;
		sum.entire = first.entire + second.entire;
		sum.fraction = first.fraction + second.fraction;

		if (sum.fraction > power(10, sum.fallibility))
		{
			sum.entire += 1;
			sum.fraction -= power(10, sum.fallibility);
		}
	}


	else if (first.fallibility == second.fallibility)
	{
		sum.fallibility = first.fallibility;
		sum.entire = first.entire + second.entire;
		sum.fraction = first.fraction + second.fraction;

		if (sum.fraction > power(10, sum.fallibility))
		{
			sum.entire += 1;
			sum.fraction -= power(10, sum.fallibility);
		}
	}


	return sum;
}




DECIMAL substract(DECIMAL first, DECIMAL second)
{
	DECIMAL sum;

	int difference;

	if (first.fallibility < second.fallibility)
	{
		difference = fabs(first.fallibility - second.fallibility);
		first.fallibility += difference;
		first.fraction *= power(10, difference);


		sum.fallibility = first.fallibility;
		sum.entire = first.entire - second.entire;
		sum.fraction = first.fraction - second.fraction;

		if (sum.fraction < 0)
		{
			sum.entire -= 1;
			sum.fraction = first.fraction + power(10, sum.fallibility) - second.fraction;
		}
	}


	else if (first.fallibility > second.fallibility)
	{
		difference = fabs(first.fallibility - second.fallibility);
		second.fallibility += difference;
		second.fraction *= power(10, difference);


		sum.fallibility = first.fallibility;
		sum.entire = first.entire - second.entire;
		sum.fraction = first.fraction - second.fraction;

		if (sum.fraction < 0)
		{
			sum.entire -= 1;
			sum.fraction = first.fraction + power(10, sum.fallibility) - second.fraction;
		}
	}


	else if (first.fallibility == second.fallibility)
	{
		sum.fallibility = first.fallibility;
		sum.entire = first.entire - second.entire;
		sum.fraction = first.fraction - second.fraction;

		if (sum.fraction < 0)
		{
			sum.entire -= 1;

			if (sum.entire >= 0)
			{
				sum.fraction = first.fraction + power(10, sum.fallibility) - second.fraction;
			}

			else
			{
				sum.fraction = power(10, sum.fallibility) - second.fraction - first.fraction;
			}
		}
	}


	return sum;
}





DECIMAL multiply(DECIMAL first, DECIMAL second)
{
	DECIMAL product;

	int difference;

	if (first.fallibility > second.fallibility)
	{
		difference = fabs(first.fallibility - second.fallibility);
		second.fallibility += difference;
		second.fraction *= power(10, difference);
	}


	else if (first.fallibility < second.fallibility)
	{
		difference = fabs(first.fallibility - second.fallibility);
		first.fallibility += difference;
		first.fraction *= power(10, difference);
	}


	product.entire = first.entire * second.entire;


	int fract[3],
		fallib[3];

	fallib[0] = first.fallibility;
	fract[0] = first.entire * second.fraction * power(10, first.fallibility);

	while (fract[0] / power(10, fallib[0]) > first.entire) fallib[0] += 1;


	if (fract[0] > power(10, fallib[0]))
	{
		product.entire += 1;
		fract[0] -= power(10, fallib[0]);
	}


	fallib[1] = second.fallibility;
	fract[1] = second.entire * first.fraction * power(10, second.fallibility);

	while (fract[1] / power(10, fallib[1]) > second.entire) fallib[1] += 1;

	if (fract[1] > power(10, fallib[1]))
	{
		product.entire += 1;
		fract[1] -= power(10, fallib[1]);
	}


	fallib[2] = first.fallibility;
	fract[2] = first.fraction * second.fraction;

	while (fract[2] / power(10, fallib[2]) > 1) fallib[2] += 1;

	int maxim = - 100000;
	for (int i = 0; i < 3; i ++)
	{
		if (maxim < fallib[i]) maxim = fallib[i];
	}


	int diff[3];
	for (int i = 0; i < 3; i ++)
	{
		diff[i] = maxim - fallib[i];
	}


	for (int i = 0; i < 3; i ++)
	{
		fallib[i] += diff[i];
		fract[i] *= power(10, diff[i]);
	}


	product.fallibility = fallib[0];
	if (fract[0] + fract[1] > power(10, fallib[0]))
	{
		product.entire += 1;
		product.fraction = fract[0] + fract[1] - power(10, fallib[0]);
	}


	else product.fraction = fract[0] + fract[1];


	if (product.fraction + fract[2] > power(10, fallib[0]))
	{
		product.entire += 1;
		product.fraction = product.fraction + fract[2] - power(10, fallib[0]);
	}


	else product.fraction += fract[2];

	return product;
}




typedef struct
{
	int digit;
	int dec;
	int inaccuracy;
} decimal;


decimal take(int digit, int dec, int inaccuracy)
{
	decimal number;

	number.digit = digit;
	number.dec = dec;
	number.inaccuracy = inaccuracy;

	return number;
}



decimal multi(decimal first, decimal second)
{
	decimal result;
	int difference;

	difference = first.inaccuracy + second.inaccuracy;
	
	result.digit = first.digit * second.digit;

	int temp[3];
	temp[0] = first.digit * second.dec * power(10, first.inaccuracy);
	temp[1] = second.digit * first.dec * power(10, second.inaccuracy);
	temp[2] = first.dec * second.dec;

	result.dec = temp[0] + temp[1] + temp[2];
	result.digit += (result.dec / power(10, difference));
	result.dec = result.dec % power(10, difference);

	return result;
}





int main()
{
	// DECIMAL first_number = take_value(12, 35, 2);
	// DECIMAL second_number = take_value(4, 97, 2);

	// DECIMAL add = summarize(first_number, second_number);
	// printf("Sum = %i.%i , fallibility = %i\n", add.entire, add.fraction, add.fallibility);

	// DECIMAL deduct = substract(first_number, second_number);
	// printf("Deduct = %i.%i , fallibility = %i\n", deduct.entire, deduct.fraction, deduct.fallibility);

	// DECIMAL multi = multiply(first_number, second_number);
	// printf("Multi = %i.%i , fallibility = %i\n", multi.entire, multi.fraction, multi.fallibility);


	decimal a = take(12, 35, 3);
	decimal b = take(4, 1, 3);

	decimal c = multi(a, b);
	printf("%i,%i\n", c.digit, c.dec);

	return 0;
}
