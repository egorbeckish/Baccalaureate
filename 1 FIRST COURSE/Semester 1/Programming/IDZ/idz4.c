#include <stdio.h>


/// Дан целочисленный массив размера N, содержащий ровно два одинаковых эле-
/// мента. Найти номера одинаковых элементов и вывести эти номера в порядке воз-
/// растания.

int task4()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    int n, i, j;
    printf("\n\n\tВведите кол-во элементов списка N: ");
    scanf("%d", &n); ///вводим размер массива

    int array[n];

    ///заполняем числами список
    printf("\n\n\tВведите элементы списка\n\n");
    for (i = 0; i < n; i++)
    {
        printf("\tarray[%i] = ", i);
        scanf("%d", &array[i]);
    }


    ///выводим полученный список
    printf("\n\t[ ");
    for (i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("]");


    for (i = 0; i < n; i++)
    {
        for (j = 0; j < i; j++)
        {
            /// находим одинаковые элементы
            if (array[i] == array[j])
            {
                ///при их нахождение, сразу печатеам
                printf("\n\n\tindex = %d;%d\n", j, i);
            }
        }
    }
    getch();
    return 0;
}


int main(int argc, char const *argv[])
{	
	task4();
	return 0;
}
