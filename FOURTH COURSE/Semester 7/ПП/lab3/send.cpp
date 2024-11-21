#include <iostream>
#include <mpi.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <iterator>
#include <vector>


void fillRandom(double* data, int rows, double min = -100.0, double max = 100.0)
{
    std::random_device rnd_device;
    std::mt19937 mersenne_engine{ rnd_device() };
    std::uniform_real_distribution<double> dist{ min, max };
    auto gen = [&dist, &mersenne_engine]()
        {return dist(mersenne_engine); };
    std::generate(data, data + rows * rows, gen);
}


void write_matrix(double* matrix, int rows, std::stringstream& text) {
    text << std::endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            text << std::setw(10) << std::setprecision(5) << matrix[i * rows + j] << " ";
        }
        text << std::endl;
        fflush(NULL);
    }
}

void write_file(std::string text, std::ostream& file) {
    file << text;
}

void triangle_matrix(double* matrix, double* _triangle_matrix, int rows) {
    int _rows = rows / 2 + 1;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            if (i == 0) {
                _triangle_matrix[i * rows + j] = matrix[i * rows + j];
            }

            else if (i < _rows) {
                if (j >= i && (j <= rows - i - 1)) {
                    _triangle_matrix[i * rows + j] = matrix[i * rows + j];
                }

                else {
                    _triangle_matrix[i * rows + j] = 0;
                }
            }

            else {
                _triangle_matrix[i * rows + j] = 0;
            }
        }
    }
}


void print_matrix(double* matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < rows; j++) {
            std::cout << matrix[i * rows + j] << " ";
        }
        std::cout << std::endl;
    }
}

void write_array(double* matrix, int rows, std::stringstream& text) {
    text << "\n";
    for (int i = 0; i < rows; i++) {
        text << std::setw(10) << std::setprecision(5) << matrix[i] << " ";
        if ((i + 1) % 9 == 0 && i != 0) {
            text << "\n";
        }
    }
    text << "\n";
}

int main(int argc, char* argv[]) {
    srand(time(NULL));

    int _process_ID, _count_process;

    int count_process,
        process_ID,
        name_length,
        len_type = 0;

    char processor_name[MPI_MAX_PROCESSOR_NAME];

    const int rows = 9;
    double* matrix = nullptr;
    double* _triangle_matrix = new double[rows * rows];
    

    // открытие файла для записи
    std::ofstream file;
    file.open("tmp.txt", std::ios_base::out);

    // форматирование строки
    std::stringstream text;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &count_process);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_ID);
    MPI_Get_processor_name(processor_name, &name_length);
    MPI_Status status;

    // подготовка информации для записи ее в файл
    text << "Name process: " << processor_name <<
        "\n\nProcess_ID: " << process_ID <<
        "\tCount process: " << count_process <<
        "\n\n Matrix " << rows << "x" << rows <<

        std::endl;

    if (process_ID == 0) {
        matrix = new double[rows * rows];
        fillRandom(matrix, rows, rows);
        write_matrix(matrix, rows, text);
    }

    // Определяем количество строк, которое будет обрабатывать каждый процесс
    int count_rows = rows / count_process;
    int count_rest = rows % count_process;

    // Массив для хранения количества строк у каждого процесса
    int process_rows[rows];
    for (int i = 0; i < rows; i++) {
        process_rows[i] = count_rows;
        if (count_rest > 0) {
            process_rows[i]++;
            count_rest--;
        }
    }

    // Массивы смещений для отправки данных
    int displs[rows];
    displs[0] = 0;
    for (int i = 1; i < rows; i++) {
        displs[i] = displs[i - 1] + process_rows[i - 1] * rows;
    }

    MPI_Datatype MPI_TRIANGLE;
    MPI_Type_indexed(rows, process_rows, displs, MPI_DOUBLE, &MPI_TRIANGLE);
    MPI_Type_commit(&MPI_TRIANGLE);

    if (process_ID == 0) {
        MPI_Send(matrix, 1, MPI_TRIANGLE, 1, 1, MPI_COMM_WORLD);
        MPI_Send(matrix, 1, MPI_TRIANGLE, 1, 2, MPI_COMM_WORLD);
        MPI_Recv(_triangle_matrix, 1, MPI_TRIANGLE, 1, 1, MPI_COMM_WORLD, &status);
        write_matrix(_triangle_matrix, rows, text);
    }

    if (process_ID == 1) {
        MPI_Recv(matrix, 1, MPI_TRIANGLE, process_ID, 1, MPI_COMM_WORLD, &status);
        write_matrix(matrix, rows, text);
        MPI_Recv(_triangle_matrix, rows, MPI_DOUBLE, process_ID, 2, MPI_COMM_WORLD, &status);
        write_matrix(_triangle_matrix, rows, text);
        MPI_Send(_triangle_matrix, rows, MPI_DOUBLE, process_ID, 1, MPI_COMM_WORLD);
    }


    write_file(text.str(), file);
    MPI_Type_free(&MPI_TRIANGLE);
    MPI_Finalize();

    return 0;
}


