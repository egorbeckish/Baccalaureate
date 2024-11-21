#include <iostream>
#include <limits>
#include <iomanip>
#include <math.h>
#include <fstream>
#include <sstream>
#include "mpi.h"

static double f(double a, double c) {
    return 1 / (1 + pow(c * a, 2));
}

static double fi(double a, double c) {
    return (1 / c) * atan(c * a);
}


// запись полученной информации в файл
static void write_file(std::string text, std::ostream& file) {
    file << text;
}


int main(int argc, char* argv[]) {
    int choose = 1;

    int count_process, // кол-во процессов
        process_ID, // номер процесса
        name_length; // длина имени процесса

    char processor_name[MPI_MAX_PROCESSOR_NAME]; // имя процесса

    int intervals = 1000000; // изначальное кол-во интервалов
    double xl = -0.2, // нижняя граница
        xh = 1.0,  // верхняя граница
        c = 0.9,   // параметр С
        sum = 0.0, // сумма для подсчета интеграла
        h = (xh - xl) / static_cast<double>(intervals); // шаг сетки

    double integral, starttime, endtime;

    // открытие файла для записи
    std::ofstream file;
    file.open("tmp.txt", std::ios_base::out);

    // форматирование строки
    std::stringstream text;

    MPI_Init(&argc, &argv); // инициализация

    MPI_Comm_rank(MPI_COMM_WORLD, &process_ID); // получение процесса
    MPI_Comm_size(MPI_COMM_WORLD, &count_process); // получение кол-во процессов
    MPI_Get_processor_name(processor_name, &name_length); // получение имени процесса
    MPI_Status status;

    // подготовка информации для записи ее в файл
    text << "Name process: " << processor_name <<
        "\n\nProcess_ID: " << process_ID <<
        "\tCount process: " << count_process <<
        "\n\nКол-во интервалов: " << intervals <<
        "\nНижняя граница: " << xl <<
        "\nВерхняя граница: " << xh <<
        "\nПараметр с: " << c <<
        std::endl;

    starttime = MPI_Wtime();
    if (choose == 1) {
        if (process_ID == 0) {
            for (int _process_ID = 1; _process_ID < count_process; _process_ID++) {
                MPI_Send(&intervals, 1, MPI_INT, _process_ID, 1, MPI_COMM_WORLD);
            }
        }

        else {
            MPI_Recv(&intervals, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        }

        text << "\n\nРаспараллеливание выполнено с помощью Send & Recv" << std::endl;
    }

    
    else if (choose == 2) {
        if (process_ID == 0) {
            /**
                * @brief Широковещательная рассылка
                * - Коллективная операция
                * - передача данных от одного процесса всем процессам программы
                * - должен быть осуществлен всеми процессами указываемого коммуникатора
                *
                * Метод осуществляет рассылку данных из буфера buffer,
                * содержащего count_data элементов типа type  с процесса,
                * имеющего номер root, всем процессам, входящим в коммуникатор comm
                *
                * Указываемый буфер памяти имеет различное назначение в разных процессах:
                * - Для процесса с рангом root,
                * с которого осуществляется рассылка данных,
                * в этом буфере должно находиться рассылаемое сообщение
                * - Для всех остальных процессов указываемый буфер предназначен
                * для приема передаваемых данных.
                *
                * @param buffer буфер памяти с отправляемым
                    сообщением (для процесса с рангом 0), и для
                    приема сообщений для всех остальных процессов
                * @param type тип данных пересылаемого/принимаемого сообщения
                * @param count_data количество элементов памяти типа type
                * @param root ранг процесса, выполняющего рассылку данных
             */
            MPI_Bcast(&xl, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
            MPI_Bcast(&xh, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
            MPI_Bcast(&intervals, 1, MPI_INT, 0, MPI_COMM_WORLD);
        }

        text << "\n\nРаспараллеливание выполнено с помощью Bcast" << std::endl;
    }

    else if (choose == 3) {
        char pack_buf[100];
        int position = 0;

        if (process_ID == 0) {
            /**
                * @brief  Запаковка сообщения из буфера data, длиной count_data типа данных type
                в буферное пространство, описанное аргументами buf и count_buf (в байтах).

                Параметр position определяет номер ячейки в выходном буфере, с которого будет заполняться buf.
                После заполнения значение position инкрементируется в количестве заполненных байтов.
                *
                * @param data буфер памяти с сообщением для запаковки
                * @param count_data количество значений этого буфера типа type
                * @param buf буфер памяти для запакованных значений
                * @param count_buf общее количество байтов этого буфера
                * @param type MPI_Datatype (тип) данных пакуемого сообщения
                * @param bufpos позиция в выходном буфере, с которого необходимо начать заполнение
            */
            MPI_Pack(&xl, 1, MPI_DOUBLE, &pack_buf, 100, &position, MPI_COMM_WORLD);
            MPI_Pack(&xh, 1, MPI_DOUBLE, &pack_buf, 100, &position, MPI_COMM_WORLD);
            MPI_Pack(&intervals, 1, MPI_INT, &pack_buf, 100, &position, MPI_COMM_WORLD);
        }

        MPI_Bcast(&pack_buf, 100, MPI_PACKED, 0, MPI_COMM_WORLD);

        if (process_ID != 0) {
            /**
                * @brief Распаковка сообщений
                * Метод распаковывает сообщение в приемный буфер, описанный аргументами outbuf, outcount, type
                * из буферного пространства, описанного аргументами inbuf и insize.
                * Выходным буфером может быть любой коммуникационный буфер, разрешенный в MPI_RECV.
                * Входной буфер есть смежная область памяти, содержащая insize байтов, начиная с адреса inbuf.
                * Входное значение position есть первая ячейка во входном буфере, занятом упакованным сообщением.
                * рosition инкрементируется размером упакованного сообщения,
                * так что выходное значение рosition есть первая ячейка во входном буфере после ячеек,
                * занятых сообщением, которое было упаковано.
                * сomm есть коммуникатор для приема упакованного сообщения.
                *
                * @param inbuf буфер, из которого будет распаковываться сообщение
                * @param insize размер этого буфера в байтах
                * @param outbuf буфер, куда будет распаковываться сообщение
                * @param bufpos позиция во входном буфере, указывающая откуда распаковывать сообщение
                * @param type тип данных распаковываемого сообщения
                * @param outcount число единиц распаковываемого сообщения типа type
            */
            MPI_Unpack(pack_buf, 100, &position, &xl, 1, MPI_DOUBLE, MPI_COMM_WORLD);
            MPI_Unpack(pack_buf, 100, &position, &xh, 1, MPI_DOUBLE, MPI_COMM_WORLD);
            MPI_Unpack(pack_buf, 100, &position, &intervals, 1, MPI_INT, MPI_COMM_WORLD);
        }

        text << "\n\nРаспараллеливание выполнено с помощью Pack & Unpack" << std::endl;
    }

    for (int i = process_ID + 1; i <= intervals; i += count_process) {
        double x = xl + h * ((double)i - 0.5); // вычисление равномерной сетки
        sum += f(x, c);
    }

    sum *= h;

    if (choose == 1) {
        if (process_ID != 0) {
            /*MPI_Send(buf, count, datatype, dest, tag, comm)
                 @brief Метод передачи сообщения: в стандартном режиме (блокирующий)
                      Метод выполняет посылку count элементов типа type сообщения buffer
                      с идентификатором tag процессу _process_ID в области связи коммуникатора comm.
                      Переменная buf - это, как правило, массив или скалярная переменная.
                      В последнем случае значение count = 1.

                 @param buf	начальный адрес буфера посылки сообщения(альтернатива)
                 @param count	число элементов в буфере посылки(неотрицательное целое)
                 @param datatype	тип данных каждого элемента в буфере посылки(дескриптор)
                 @param dest	номер процесса - получателя(целое)
                 @param tag	тэг сообщения(целое)
                 @param comm	коммуникатор(дескриптор)*/

            MPI_Send(&sum, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
        }

        if (process_ID == 0) {
            integral = sum;
            for (int _process_ID = 1; _process_ID < count_process; _process_ID++) {
                /*
                    * @brief Метод приёма сообщения: блокирующий
                    *
                    * Метод выполняет прием count_data элементов типа type сообщения  buffer
                    * с идентификатором tag от процесса from_PID в области связи коммуникатора comm.
                    *
                    * @param buffer адрес заполняемого буфера памяти
                    * @param _process_ID ранг процесса, от которого ожидать сообщение
                    * @param type тип данных принимаемого сообщений
                    * @param count_data _максимальное_ количество элементов памяти типа type
                    * @param tag идентификатор принимаемого сообщения: целое число от 0 до 32767
                    * - определяет смысл принятого сообщения.
                    * - Сообщения, пришедшие в неизвестном порядке,
                    * могут извлекаться из общего входного потока в нужном алгоритму порядке.
                    * @return status MPI_Status получения сообщения
                */
                MPI_Recv(&sum, 1, MPI_DOUBLE, _process_ID, 1, MPI_COMM_WORLD, &status);
                integral += sum;
            }

            endtime = MPI_Wtime();

            text <<
                "\nСумма интеграла: " << std::scientific << sum <<
                "\nАпроксимация интеграла: " << std::scientific << integral <<
                "\nОшибка: " << std::scientific << integral - fi(xh, c) + fi(xl, c) <<
                "\nВремя подсчета: " << std::scientific << endtime - starttime <<
                std::endl;
        }
    }

    
    else if (choose == 2) {
        integral = sum;
        MPI_Reduce(&sum, &integral, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        endtime = MPI_Wtime();

        text <<
            "\nСумма интеграла: " << std::scientific << sum <<
            "\nАпроксимация интеграла: " << std::scientific << integral <<
            "\nОшибка: " << std::scientific << integral - fi(xh, c) + fi(xl, c) <<
            "\nВремя подсчета: " << std::scientific << endtime - starttime <<
            std::endl;
    }

    write_file(text.str(), file);

    
    MPI_Finalize();

    return 0;
}

 //mpiexex -n ... file


