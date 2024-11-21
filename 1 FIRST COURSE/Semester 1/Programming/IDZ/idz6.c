#include <stdio.h>
#include <stdlib.h>


///Дан массив размера N. После каждого отрицательного элемента массива вставить
///элемент с нулевым значением.


int task6()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int n, counter;
    printf("\n\n\tВведите кол-во элементов списка N: ");
    scanf("%i", &n);///ввод кол-во элементов списка

    int *list;

    list = (int *)calloc(n, sizeof(int));

    ///заполняем список элементами
    printf("\n\tВведите элементы списка\n");
    for (int i = 0; i < n; i++)
    {
        printf("\tarray[%i] = ", i);
        scanf("%i", &list[i]);
    }

    ///вывод изначального списка
    printf("\n\tИзначальный список\t[ ");
    for (int i = 0; i < n; i++)
    {
        printf("%i ", list[i]);
    }
    printf("]\n");


    counter = 0;
    for (int i = 0; i < n + counter; i++)
    {
        if (list[i] < 0)
        {
            counter += 1;
            list = (int *)realloc(list, (n+counter)*sizeof(int));
            for (int j = n + counter - 1; j > i; j--)
            {
                list[j] = list[j - 1];
            }
            list[i + 1] = 0;
        }
    }

    printf("\n\tСписок после преобразования\t[ ");
    for (int i = 0; i < n + counter; i++)
    {
        printf("%i ", list[i]);
    }
    printf("]");

    getch();
    return 0;
}

int main(int argc, char const *argv[])
{	
	task6();
	return 0;
}
