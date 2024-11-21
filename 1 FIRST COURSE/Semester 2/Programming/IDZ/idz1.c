//1. Дана матрица размера M x N. Для каждого столбца матрицы с четным номером
//найти сумму его элементов. Условный оператор не использовать.

int *sum_columns(int rows, int columns, int **matrix)
{
    int *sum_columns = (int *)calloc(columns, sizeof(int));
    for (int i = 0; i < columns; i += 2)
    {
        for (int j = 0; j < rows; j ++)
        {
            sum_columns[i] += matrix[j][i];
        }
    }

    // for (int i = 0; i < columns; i += 2)                                                                              
    // {                                                                                                          
    //     if (i % 2 == 0) printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%i)\t %i\n", i, sum_columns[i]);       
    // }

    return sum_columns;
}




int task1()
{
    int rows = 3 + rand() % 6,
        columns = 2 + rand() % 6;


    int **matrix = (int **)calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i ++)
    {
        matrix[i] = (int *)calloc(columns, sizeof(int));
        for (int j = 0; j < columns; j ++)
        {
            matrix[i][j] = rand() % 10;
        }
    }


    printf("\n\n");
    for (int i = 0; i < rows; i ++)
    {
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t[ ");
        for (int j = 0; j < columns; j ++)
        {
            printf("%i ", matrix[i][j]);
        }
        printf("]\n");
    }
    printf("\n");

    int *sum = sum_columns(rows, columns, matrix);

    for (int i = 0; i < columns; i += 2)                                                                              
    {                                                                                                          
        if (i % 2 == 0) printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t%i)\t %i\n", i, sum[i]);       
    }
}


int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    task1();
    return 0;
}
