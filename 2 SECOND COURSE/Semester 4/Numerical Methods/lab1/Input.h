#ifndef IINPUTDEVICE_H
#define IINPUTDEVICE_H
#include <iostream>
#include <exception>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>
#include <sstream>
#include <cfloat>
#include <cmath>
//#include <iomanip>

char getSymbol(std::initializer_list<char> list,
    std::string notification_message = "",
    std::string error_message = "Были ввидены некоректные данные.\n->");

double getDouble(double min = -DBL_MAX,
    double max = DBL_MAX,
    std::string = "",
    std::string error_message = "Были ввидены некоректные данные.\n->");



class IInputDevice
{
private:
    std::streambuf* _original_cin;
    std::ifstream* _fin;
    std::vector<std::string> _expr;
    char _method;
    int _NAfterComma;
    double _eps;
    double _a, _b;
public:

    IInputDevice(char choice = '1')
        : _original_cin{ NULL },
        _fin{ NULL }
    {
        switch (choice)
        {
        case '1':
            _a = getDouble(-DBL_MAX, DBL_MAX, "левая граница\n-> ");
            _b = getDouble(-DBL_MAX, DBL_MAX, "правая граница\n-> ");
            _NAfterComma = setNAfterComma();
            break;
        case '2':
        {
            std::string filename;
            std::cout << "Данные через файл:\n->";
            getline(std::cin, filename);
            _fin = new std::ifstream(filename);
            _original_cin = redirectInput(_fin);
            if (!_original_cin)  choice = '4';
            break;
        }
        case '3':
            _fin = new std::ifstream("input.txt");
            _original_cin = redirectInput(_fin);
            if (!_original_cin) choice = '4';
            break;
        case '4': break;
        default:
            throw std::invalid_argument("Работа завершена...\n");
        }
        InputData(choice);
    }

    void InputData(char choice)
    {
        std::string string;
        switch (choice)
        {
        case '1':
            while (true)
            {
                std::cout << "Задайте уравнение.:\n-> ";

                getline(std::cin, string);
                if (string.empty())
                    std::cerr << "Задайте уравнение.\n";
                else _expr.push_back(string);
                choice = getSymbol({ '1','2' }, "1) Перезаписать;\n2) Выбрать метод\n-> ");
                if (choice == '1') continue;
                else break;
            }
            break;
        case '2': case '3':
            while (true)
            {
                string.clear();
                getline(std::cin, string);
                if (!string.empty()) { _expr.push_back(string); continue; }
                if (_expr.empty())
                    std::cerr << "1.\n";
                break;
            }
            _method = _expr[0][0];
            std::stringstream stream(_expr[2]);
            getline(stream, string, ' ');
            _a = std::stod(string);
            getline(stream, string, ' ');
            _b = std::stod(string);
            _eps = std::stod(_expr[3]);
            _NAfterComma = setNAfterComma(_eps);
            _expr[0] = _expr[1];
            _expr.resize(1);

            break;
        }
    }

    std::streambuf* redirectInput(std::ifstream* fin = NULL)
    {
        std::streambuf* original_cin = std::cin.rdbuf();
        while (!*fin)
        {
            std::string filename;
            char choice;
            choice = getSymbol({ '1', '2' },
                "Äàííûé ôàéë íå ìîæåò áûòü îòêðûò, ëèáî íå ñóùåñòâóåò. Ïîïðîáîâàòü åù¸ ðàç?\n1) äà\n2) âûéòè\n->");
            if (choice == '1')
            {
                std::cout << "Ââåäèòå èìÿ ôàéëà:\n->";
                getline(std::cin, filename);
            }
            else return NULL;
            fin->open(filename);
        }
        
        std::cin.rdbuf(fin->rdbuf());
        return original_cin;
    }



    ~IInputDevice()
    {
        if (_original_cin)
            std::cin.rdbuf(_original_cin);
        if (_fin)
            _fin->close();
    }

    bool isEmptyVectorString()
    {
        return _expr.empty();
    }
    std::vector<std::string> getVectorString()
    {
        return _expr;
    }

    double getLeft() { return _a; }
    double getRight() { return _b; }
    double getEps() { return _eps; }
    int getNAfterComma() { return _NAfterComma; }
    char getMethod() { return _method; }

    void setMethod(char method)
    {
        if (method < '1' || method > '6') throw std::invalid_argument("Метод не найден");
        _method = method;
    }

    int setNAfterComma(double eps = 0.0)
    {

        if (!eps)
            _eps = getDouble(0, 1,
                "Введите погрежность (0 < eps < 1) (используйте ',')\n->");

        std::string s = std::to_string(_eps);
        for (int i = 0; i < sizeof(s); ++i)
        {
            if (s[i] == '1') { return (i - 1); break; }
        }
        
        return 1;

        //if (choice == '1')
        //return 1 - log(1 * _eps)
        //return -std::ceil(log(_eps)); // выводить опреденное кол-во знаков для корня и функции
                                        // научный формат - достигнутой точности
        //else
        //	return  1 - log(1 * _eps);
    }
};
#endif