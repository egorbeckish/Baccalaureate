#include <stdio.h>


///Даны целые числа K, N, а также K наборов целых чисел по N элементов в каждом
///наборе. Для каждого набора вывести номер его последнего элемента, равного 2,
///или число 0, если в данном наборе нет двоек

int task3()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n, k, digit, counter = 0, collection = 0;
    printf("\n\n\tВведите кол-во элементов N: ");
    scanf("%i", &n);

    while (n <= 0)
    {
        printf("\n\tВведенно некорректное значение");
        scanf("%i", &n);
    }

    printf("\n\tВведите кол-во наборов K: ");
    scanf("%i", &k);

    while (k <= 0)
    {
        printf("\n\tВведенно некорректное значение");
        scanf("%i", &k);
    }

    printf("\n");
    ///проходим по кол-ву наборов
    for (int i = 0; i < k; i++)
    {
        ///проходимся по элементам набора
        for(int j = 0; j < n; j++)
        {
            ///вводим числа с помощью random
            digit = rand()%9;
            printf("digit(%i) = %i\t", j, digit);
            ///если встретили цифру да, то
            ///счетчик увел. на 1
            if (digit == 2)
            {
                counter += 1;
            }

            ///если набор закончился и в этом же наборе
            ///нашли цифру(ы), то увел. набор на 1
            if ((j == (n - 1)) && (counter > 0))
            {
                collection += 1;
                counter = 0;
            }
        }
        printf("\n");
    }

    printf("\n\n\tКол-во наборов: %i", collection);
    getch();
    return 0;
}


int main(int argc, char const *argv[])
{	
	task3();
	return 0;
}
