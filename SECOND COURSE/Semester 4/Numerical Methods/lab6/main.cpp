#include <iostream>
#include "SplineApproximation.h"

using namespace luMath;

int main()
{
    system("chcp 1251 > null");
    char choice;
    do {
        system("pause");
        system("cls");
        choice = getSymbol({ '1','2','3','4','5','6'},
            "Введите способ ввода данных:"
            "\n1) с клавиатуры"
            "\n2) из файла, заданного пользователем"
            "\n3) стандартный c линейным сплайном       (из файла input_order_1.txt)"
            "\n4) стандартный с параболическим сплайном (из файла input_order_2.txt)"
            "\n5) стандартный с кубическим сплайном     (из файла input_order_3.txt)"
            "\n6) завершить программу\n-> ");
        if (choice == '6') break;
        SplineApproximation<double> data;
        std::ifstream* fin = data.setInputDevice(choice);
        data.inputData(fin);
        data.composeSplines(data.getSplOrd());
        std::cout << std::setprecision(5) << std::setw(10) << data;
    } while (choice);
    system("pause");
}