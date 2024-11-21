#include <stdio.h>
#include <stdlib.h>

/// Дано целое число N и набор из N целых чисел, содержащий по крайней мере два
///нуля. Вывести сумму чисел из данного набора, расположенных между последними
///двумя нулями (если последние нули идут подряд, то вывести 0).

int task2()
{

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n, sum = 0, temp_sum = 0, digit;

    printf("\n\tВведите кол-во элементов N: ");
    scanf("%i", &n);

    printf("\n\tВведите элементы набора\n\n");
    for (int i = 0; i < n; i++)
    {
        printf("\t%i-ый элемент: ", i);
        scanf("%i", &digit);///вводим число

        temp_sum += digit;///добавляем его во временую сумму

        if (digit == 0)///если встретился введенный ноль, то фиксируем накопленную сумму
        {
            sum = temp_sum;
            temp_sum = 0;
        }
    }
    printf("\n\tСумма = %i", sum);
    getch();
    return 0;
}



int main(int argc, char const *argv[])
{	
	task2();
	return 0;
}
