//2. Дана целочисленная матрица размера M x N. Найти номер первого из её столб-цов, 
//содержащих максимальное количество одинаковых элементов.

void repeat_elements(int* set, int columns, int *repeat)
{
    int counter = 0;
    for (int i = 0; i < columns; i ++)
    {
        int flag = 1;
        for (int j = 0; j < i; j ++)
        {
            if (set[i] == set[j])
            {
                flag = 0;
            }
        }

        if (flag)
        {
            counter ++;
        }
    }

    *repeat = columns - counter;
    // printf("%i ", columns - counter);
}

int *transposition_matrix(int rows, int columns, int **matrix)
{
    int **new_matrix = (int **)calloc(columns, sizeof(int *));
    for (int i = 0; i < columns; i ++)    // Транспонирование матрицы
    {
        new_matrix[i] = (int *)calloc(rows, sizeof(int));
        for (int j = 0; j < rows; j ++)
        {
            new_matrix[i][j] = matrix[j][i];
        }
    }


    printf("\n");
    for (int i = 0; i < columns; i ++)
    {
        printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t[ ");
        for (int j = 0; j < rows; j ++)
        {
            printf("%i ", new_matrix[i][j]);
        }
        printf("]\n");
    }
    printf("\n");


    int maxim = 0, index;
    int *answer = (int *)calloc(2, sizeof(int));
    for (int i = 0; i < columns; i ++)
    {    
        // answer[i] = (int *)calloc(2, sizeof(int));
        int repeat;
        repeat_elements(new_matrix[i], rows, &repeat);

        if (repeat > maxim)
        {
            maxim = repeat;
            index = i;
        }
    }
    answer[0] = index;
    answer[1] = maxim;
    
    return answer;
}

int task2()
{
    int rows = 3 + rand() % 6,
        columns = 2 + rand() % 6;


    int **matrix = (int **)calloc(rows, sizeof(int *));
    for (int i = 0; i < rows; i ++)
    {
        matrix[i] = (int *)calloc(columns, sizeof(int));
        for (int j = 0; j < columns; j ++)
        {
            matrix[i][j] = rand() % 5;
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
    
    int *result = transposition_matrix(rows, columns, matrix);

    printf("\t\t\t\t\t\t\t\t\t\t\t\t\t  Столбец №%i Кол-во повтор. эл-ов = %i\n", result[0], result[1]);
}


int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    task2();
    return 0;
}
