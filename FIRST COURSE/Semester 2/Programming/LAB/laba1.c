#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>


//                                                               Дана целочисленная матрица A размера M x N,
//                                                           элементы которой могут принимать значения от 0 до 100.
//                                                               Найти количество строк матрицы, похожих на первую.




int** create_and_print_matrix(int rows, int columns)
{
    int **matrix = (int **)calloc(rows, sizeof(int *)); // memory allocation for the matrix
    for (int i = 0; i < rows; ++ i)    // create matrix
    {
        matrix[i] = (int *)calloc(columns, sizeof(int));
        for (int j = 0; j < columns; ++ j)
        {
            // matrix[i][j] = rand() % 100;
            printf("\t\t\t\t\t\t\t\t\t\t\t\tmatrix[%i][%i] = ", i, j);
            scanf("%i", &matrix[i][j]);
        }
    }
    printf("\n");


    for (int i = 0; i < rows; ++ i)    // print matrix
    {
        printf("\t\t\t\t\t\t\t\t\t\t\t\t[ ");
        for (int j = 0; j < columns; ++ j)
        {
            printf("%i ", matrix[i][j]);
        }
        printf("]\n");
    }
    printf("\n\n");

    return matrix;
}

// void quick_sort(int *array, int start, int finish)
// {
//     int left = start,
//         right = finish,
//         middle = array[(start + finish) / 2];

//     do
//     {
//         if (array[left] < middle) left ++;
//         if (array[right] > middle) right --;

//         if (left <= right)
//         {
//             int temp = array[left];
//             array[left] = array[right];
//             array[right] = temp;

//             left ++;
//             right --;
//         }

//     } while (left <= finish);

//     if (left < finish) quick_sort(array, left, finish);
//     if (right > finish) quick_sort(array, start, right);
// }

void bubble_sort(int *array, int size_array)
{
    for (int i = 0; i < size_array - 1; ++ i)
    {
        for (int j = 0; j < size_array - i - 1; ++ j)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}




int* create_and_print_set(int columns, int *elements, int *size_set)
{
    // check repeat elements
    int counter = 0;
    for (int i = 0; i < columns; i ++)
    {
        int flag = 1;
        for (int j = 0; j < i; j ++)
        {
            if (elements[i] == elements[j])
            {
                flag = 0;
            }
        }

        if (flag)
        {
            counter ++;
        }
    }


    // create set
    int *set = (int *)calloc(counter, sizeof(int)); // memory allocation for the set
    int k = 0;

    for (int i = 0; i < columns; i ++)
    {
        int flag = 1;
        for (int j = 0; j < i; j ++)
        {
            if (elements[i] == elements[j])
            {
                flag = 0;
            }
        }

        if (flag) set[k ++] = elements[i];
    }

    bubble_sort(set, counter);
    // quick_sort(set, 0, counter);


    printf("\t\t\t\t\t\t\t\t\t\t\t\t[ ");
    for (int i = 0; i < counter;  i ++)
    {
        printf("%i ", set[i]);
    }
    printf("]\n");


    *size_set = counter;
    return set;
}


void check_match_rows(int *set, int size_of_set, int rows, int columns, int **matrix)
{
    int counter_rows = 0;
    for (int i = 1; i < rows; i ++)
    {
        int size_set;
        int *temp_set = create_and_print_set(columns, matrix[i], &size_set);

        if (size_set != size_of_set)
        {
            continue;
        }

        int flag = 1;
        for (int j = 0; j < size_of_set; j ++)
        {
            if (temp_set[j] != set[j])
            {
                flag = 0;
                break;
            }
        }

        if (flag)
        {
            counter_rows ++;
        }
    }

    printf("Кол-во совпад. строк = %i", counter_rows);
    printf("\n");
}





int main(void)
{
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));

    int n = 5, m = 5;

    printf("\n\t\t\t\t\t\t\t\tДана целочисленная матрица A размера M x N,"
            "\n\t\t\t\t\t\t\t\tэлементы которой могут принимать значения от 0 до 100."
            "\n\t\t\t\t\t\t\t\tНайти количество строк матрицы, похожих на первую.\n\n");



    // define size of matrix
    // printf("\tВведите n: ");
    // scanf("%i", &n);
    // printf("\tВведите m: ");
    // scanf("%i", &m);

    int **matrix = create_and_print_matrix(n, m); 

    int lenght_set;
    int *set = create_and_print_set(m, matrix[0], &lenght_set);

    check_match_rows(set, lenght_set, n, m, matrix);

    for (int i = 0; i < m; i ++)
    {
        free(matrix);
    }

    return 0;
}
