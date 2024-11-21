//4. Дана квадратная матрица A порядка M. Найти среднее арифметическое элементов ее
//побочной диагонали, т.е. диагонали, содержащей элементы: A1M, A2M−1,
//A3M−2, . . ., AM1.

float middle_arithmetic(int rows, int **matrix)
{
    float sum = 0;
    for (int i = 0; i < rows; i ++)
    {
        sum += matrix[i][rows - i - 1];
    }
    return (sum / rows);
}


void task4()
{
    int rows = 3 + rand() % 6,
        columns = rows;


    int **matrix = (int **)calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i ++)
    {
        matrix[i] = (int *)calloc(rows, sizeof(int));
        for (int j = 0; j < columns; j ++)
        {
            matrix[i][j] = rand() % 10;
        }
    }


    printf("\n");
    for (int i = 0; i < rows; i ++)
    {
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t[ ");
        for (int j = 0; j < columns; j ++)
        {
            printf("%i ", matrix[i][j]);
        }
        printf("]\n");
    }
    printf("\n");


    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tСр-ее ар-ое = %f\n\n", middle_arithmetic(rows, matrix));
}

int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    task4();
    return 0;
}
