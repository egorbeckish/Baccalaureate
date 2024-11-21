#include <iostream>
#include "Timer.h"
#include "Interpolation.h"

using namespace Math;

int main()
{
    system("chcp 1251 > null");
    char choice;
    do {
        system("pause");
        system("cls");
        choice = getSymbol({ '1','2','3','4','5' },
            "Введите способ ввода данных:"
            "\n1) с клавиатуры"
            "\n2) из файла, заданного пользователем"
            "\n3) стандартный с равномерной сеткой (из файла input_uniform_grid.txt)"
            "\n4) стандартный с неравномерной сеткой (из файла input_non-uniform_grid.txt)"
            "\n5) завершить программу\n-> ");
        if (choice == '5') break;
        Interpolation<double> data;
        std::ifstream* fin = data.setInputDevice(choice);
        data.inputData(fin);
        std::cout << std::setprecision(5) << std::setw(10) << data;
    } while (choice);
    system("pause");
}