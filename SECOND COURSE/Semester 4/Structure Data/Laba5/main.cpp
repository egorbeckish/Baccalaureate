#include <iostream>
#include <fstream>
#include <exception>
#include <conio.h>
#include <string>
#include "HashTable.h"
#include <windows.h>
 //Написать программу, 
 //которая реализует метод закрытого хеширования 
 //с квадратичной последовательностью проб 
 //и хеш - функцией, основанной на методе деления с остатком.
 //
 //Хеш - таблица ориентирована на хранение символьной информации.
 //Данные в хеш - таблицу заносятся из файла.
 //Файл должен содержать не менее 15 слов.
 //
 //Вывести построенную хеш - таблицу на экран
 //(вместе с количеством выполненных проб).
 //
 //Организовать поиск и удаление данных в хеш - таблице.
 //
 //Результаты поиска данных вывести на экран.
 //
 //Также вывести количество проб, которые были затрачены при поиске.


char getSymbol(std::initializer_list<char> list,
    std::string notification_message = "",
    std::string error_message = "Недопустимое значение, попробуйте ещё раз.\n->");
std::streambuf* redirectInput(std::ifstream* fin = NULL);
std::streambuf* redirectOutput(std::ofstream* fout = NULL);

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    char choice;


    do {
        system("cls");
        choice = getSymbol({ '1','2','3','4' },
            "Введите способ ввода и вывода данных:\n1) с клавиатуры;\n2) из файла\n3) стандартный (из файла input.txt в файл output.txt)\n4) завершить программу\n-> ");
        if (choice == '4') break;
        HashTable T;

        std::string filein("input.txt");
        std::string fileout("output.txt");
        int size = 25;
        if (choice == '1')
        {
            std::cout << "Введите размер хеш-таблицы:\n-> ";
            std::cin >> size;
            T.resize(size);
            T.reserve(size);
        }
        if (choice == '2')
        {
            std::cout << "Введите имя входного файла:\n->";
            getline(std::cin, filein);
            std::cout << "Введите имя выходного файла:\n->";
            getline(std::cin, fileout);
        }

        std::ofstream fout;
        fout.open(fileout);
        std::streambuf* original_stream = NULL;
        if (choice == '2' || choice == '3')
        {
            std::ifstream fin(filein);
            original_stream = redirectInput(&fin);
            if (!original_stream) { choice = '4'; break; }
            T.resize(size);
            T.reserve(size);
            while (fin)
                fin >> T;

            std::cin.rdbuf(original_stream);
            fin.close();
        }

        char choice;
        while (true)
        {
            system("cls");
            choice = getSymbol({ '1','2','3','4','5','6' },
                "Выберите действие:\n1) просмотреть хеш-таблицу\n2) вставить слово в хеш-таблицу\n3) удалить слово из хеш-таблицы\n4) найти индекс слова в хеш-таблице\n5) напечатать хеш-таблицу в файле\n6) Завершить таблицу (не сохраняет в файл)\n-> ");

            switch (choice)
            {
            case '1':
                std::cout << T;
                break;
            case '2':
            {
                std::cout << "Введите слово: ";
                std::string newword;
                std::cin >> newword;
                T.insert(std::move(newword));
                break;
            }
            case '3':
            {
                std::cout << "Введите слово: ";
                std::string delword;
                std::cin >> delword;
                T.del(std::move(delword));
                break;
            }
            case '4':
            {
                std::cout << "Введите слово: ";
                std::string indword;
                std::cin >> indword;
                std::cout << T.search(std::move(indword)) << " <- индекс элемента" << std::endl;
                break;
            }
            case '5':
                original_stream = redirectOutput(&fout);
                if (!original_stream) break;
                std::cout << T;
                std::cout.rdbuf(original_stream);
                break;
            case '6':
                std::cout << T;
                break;
            default: std::cerr << "Упс, что-то пошло нет так...";
            }
            if (choice == '6') break;
            system("pause");
        }
        system("pause");
    } while (true);
}

char getSymbol(std::initializer_list<char> list,
    std::string notification_message,
    std::string error_message)
{
    char choice = NULL;
    std::cout << notification_message;

    bool flag = true;
    do {
        choice = _getche();
        std::cout << std::endl;
        for (auto it = list.begin(); it != list.end(); it++)
            if (it[0] == choice) { flag = false; break; }

        if (flag) std::cerr << error_message;
    } while (flag);
    return choice;
}

std::streambuf* redirectInput(std::ifstream* fin)
{
    std::streambuf* original_cin = std::cin.rdbuf();
    while (!*fin)
    {
        std::string filename;
        char choice;
        choice = getSymbol({ '1', '2' },
            "Данный файл не может быть открыт, либо не существует. Попробовать ещё раз?\n1) да\n2) выйти\n->");
        if (choice == '1')
        {
            std::cout << "Введите имя файла:\n->";
            getline(std::cin, filename);
        }
        else return NULL;
        fin->open(filename);
    }
    //перенаправляем стандартный поток ввода на переданный файл
    std::cin.rdbuf(fin->rdbuf());
    return original_cin;
}
std::streambuf* redirectOutput(std::ofstream* fout)
{
    std::streambuf* original_cout = std::cout.rdbuf();
    while (!*fout)
    {
        std::string filename;
        char choice;
        choice = getSymbol({ '1', '2' },
            "Данный файл не может быть открыт, либо не существует. Попробовать ещё раз?\n1) да\n2) выйти\n->");
        if (choice == '1')
        {
            std::cout << "Введите имя файла:\n->";
            getline(std::cin, filename);
        }
        else return NULL;
        fout->open(filename);
    }
    //перенаправляем стандартный поток вывода на переданный файл
    std::cout.rdbuf(fout->rdbuf());
    return original_cout;
}
