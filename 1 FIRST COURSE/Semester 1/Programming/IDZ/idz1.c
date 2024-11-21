#include <stdio.h>

/// Написать функцию int left_shift(int n, int s), выполняющую цик-
/// лический сдвиг разрядов числа n на s разрядов влево.

int mypow(int n)
{
    int x, j;
    x = 1;
    for (j = 1; j <= n; j++)
    {
        x *= 10;
    }
    return x;
}


int left_shift(int digit, int shift)
{
    /// digit - число
    /// shift - сдвиг на определенное число разрядов

    int counter, lenght, temp, new_digit, i;

    counter = 0;
    new_digit = digit;
    while (digit != 0)  /// ищем длину числа
    {
        counter += 1;
        digit /= 10;
    }
    lenght = counter;


    for (i = 0; i <= lenght; i++)   ///начинаем сдвигать введеное число на определенное кол-во разрядов
    {
        temp = new_digit % mypow(lenght - shift);   /// убираем те цифры, которые сдвигаем на введенные разрядов
        temp *= mypow(lenght - (lenght - shift));   /// добавляем нули, чтобы добавить сдвинутые разряды
        temp += new_digit / mypow(lenght - shift);  /// добавляем в конец к нулям сдвинутые разряды
    }
    new_digit = temp;
    return new_digit;
    //printf("%i",new_digit);
}



int main(int argc, char const *argv[])
{	
	int digit, shift;
  digit = rand() % 100000000;
  shift = rand() % 10;
  
  int number = left_shift(digit, shift);
  printf("%i", number);
  
	return 0;
}
