#include <iostream>
#include <omp.h>
#include <chrono>
#include <thread>
#include <fstream>

int Nrdr = 0;
int data = 0;
int t = 1000;
std::ofstream file;

void READER(int n)
{
    Nrdr++;
#pragma omp critical
    {
        //std::cout << "READER " << omp_get_thread_num() << ": Nrdr=" << Nrdr << '\n';
        file << "READER " << omp_get_thread_num() << ": Nrdr=" << Nrdr << '\n';
    }

#pragma omp critical
    {
        //std::cout << "READER " << omp_get_thread_num() << ": Nrdr=" << Nrdr << ": data=" << data << " inter=" << n << std::endl;
        file << "READER " << omp_get_thread_num() << ": Nrdr=" << Nrdr << ": data=" << data
            << " inter=" << n << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % t + 1));

    Nrdr--;
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % t + 1));
#pragma omp critical
    {
        //std::cout << "READER " << omp_get_thread_num() << ": Nrdr=" << Nrdr << std::endl;
        file << "READER " << omp_get_thread_num() << ": Nrdr=" << Nrdr << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(rand() % 1 + 1));
}

void WRITER(int n)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % t + 1));
    data++;
#pragma omp critical
    {
        //std::cout << "\nWRITER " << omp_get_thread_num() << ": data=" << data << " inter=" << n << std::endl;
        file << "\nWRITER " << omp_get_thread_num() << ": data=" << data << " inter=" << n << std::endl;
    }
}

int main(int argc, char* argv[])
{
    file.open("nonsync_output.txt");
    int n = 7;

#pragma omp parallel
    {
#pragma omp sections nowait
        {
#pragma omp section
            {
                for (int i = 0; i < n; i++)
                {
                    WRITER(i);
                }
            }
#pragma omp section
            {
                for (int i = 0; i < n; i++)
                {
                    READER(i);
                }
            }
#pragma omp section
            {
                for (int i = 0; i < n; i++)
                {
                    READER(i);
                }
            }
#pragma omp section
            {
                for (int i = 0; i < n; i++)
                {
                    WRITER(i);
                }
            }
#pragma omp section
            {
                for (int i = 0; i < n; i++)
                {
                    READER(i);
                }
            }
        }
    }
    file.close();
    return 0;
}