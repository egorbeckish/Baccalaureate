#include <stdio.h>
#include <stdlib.h>



void task7()
{
    printf("\t\tЗадание 7\n"
           "\n\tДана матрица размера MxN. Преобразовать матрицу, поменяв местами мини-"
           "\n\tмальный и максимальный элемент в каждой строке.");

    int n, m, i, j;

    printf("\n\n\t\tВведите кол-во строк n: ");
    scanf("%i", &n);
    printf("\t\tВведите кол-во столбцов m: ");
    scanf("%i", &m);

    int matrix[n][m];


    for (i = 0; i < n; i ++)
    {
        for (j = 0; j < m; j ++)
        {
            matrix[i][j] = rand()%1000;
        }
    }

    printf("\n\t\tИзначальная матрица\n\n");
    for (i = 0; i < n; i ++)
    {
        printf("\t\t   [ ");
        for (j = 0; j < m; j ++)
        {
            printf("%i ", matrix[i][j]);
        }
        printf("]\n");
    }

    int maxim = 0, minim = 0, temp;
    for (i = 0; i < n; i ++)
    {
        for (j = 0; j < m; j ++)
        {
            if (matrix[i][minim] > matrix[i][j])
            {
                minim = j;
            }

            if (matrix[i][maxim] < matrix[i][j])
            {
                maxim = j;
            }
        }
        temp = matrix[i][minim];
        matrix[i][minim] = matrix[i][maxim];
        matrix[i][maxim] = temp;
    }

    printf("\n\t\tПреобразованная матрица\n\n");
    for (i = 0; i < n; i ++)
    {
        printf("\t\t   [ ");
        for (j = 0; j < m; j ++)
        {
            printf("%i ", matrix[i][j]);
        }
        printf("]\n");
    }
    getch();
}


int main(int argc, char const *argv[])
{	
	task7();
	return 0;
}
