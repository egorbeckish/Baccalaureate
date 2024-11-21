//3. Дана матрица размера M x N. Зеркально отразить её элементы относительно 
//вер-тикальной оси симметрии матрицы 
//(при этом поменяются местами столбцы с номерами 1 и N, 2 и N − 1 и т. д.).


int **symmetry_matrix(int rows, int columns, int **matrix)
{
    int stop;
    if (rows > columns)
    {
        stop = (columns / 2) - 1;
    }

    else stop = (rows / 2) - 1;
    // printf("%i", stop);
    for (int i = 0; i < rows; i ++)
    {
        for (int j = 0; j < columns; j ++)
        {
            if (j <= stop)
            {
                int temp = matrix[i][j];
                matrix[i][j] = matrix[i][columns - j - 1];
                matrix[i][columns - j - 1] = temp;
            }
        }
    }

    return matrix;
}

int task3()
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

	printf("\n");
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

	// int stop;
	// if (rows > columns)
	// {
	// 	stop = (columns / 2) - 1;
	// }

	// else stop = (rows / 2) - 1;
	// printf("%i", stop);
	// for (int i = 0; i < rows; i ++)
	// {
	// 	for (int j = 0; j < columns; j ++)
	// 	{
	// 		if (j <= stop)
	// 		{
	// 			int temp = matrix[i][j];
	// 			matrix[i][j] = matrix[i][columns - j - 1];
	// 			matrix[i][columns - j - 1] = temp;
	// 		}
	// 	}
	// }
	// int **new_matrix = symmetry_matrix(rows, columns, matrix);

	int **new_matrix = symmetry_matrix(rows, columns, matrix);
	printf("\n");
	for (int i = 0; i < rows; i ++)
	{
		printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t[ ");
		for (int j = 0; j < columns; j ++)
		{
			printf("%i ", new_matrix[i][j]);
		}
		printf("]\n");
	}
	printf("\n");

}


int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));
    task3();
    return 0;
}
