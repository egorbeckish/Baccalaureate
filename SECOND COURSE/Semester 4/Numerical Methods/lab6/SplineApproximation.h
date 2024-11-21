#ifndef SPLINE_APPROZIMATION_H
#define SPLINE_APPROZIMATION_H
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <sstream>
#include <iomanip>
#include "Matrix.h"
#include "Vector.h"
#include "PolStr.h"
#include "Polynomial.h"

#define EPS 1e-7

namespace luMath
{
    std::streambuf* redirectInput(std::ifstream* fin = NULL);
    std::streambuf* redirectOutput(std::ofstream* fout = NULL);
   
    char getSymbol(std::initializer_list<char> list,
        std::string notification_message = "",
        std::string error_message = "Недопустимое значение, попробуйте ещё раз.\n-> ");
    double getDouble(double min = -DBL_MAX,
        double max = DBL_MAX,
        std::string notification_message = "",
        std::string error_message = "Недопустимое значение, попробуйте ещё раз.\n-> ");
    template<class T>  Vector<T>& getGridX(Vector<T>& array, size_t size,
        std::string notification_message = "",
        std::string error_message = "Недопустимое значение, попробуйте ещё раз.");
        
    template<class T>
    class SplineApproximation 
    {
    private:
        std::streambuf* _original_cin;
        std::streambuf* _original_cout;
        unsigned _k;   //  порядок сплайна 
                       // (1 – линейный, 
                       //  2 – параболический,
                       //  3 – кубический)
        unsigned _n;   // количество сплайнов;
        Vector<T> _x0; // узлы сетки;
        Vector<T> _y0; // значения функции в узлах сетки;
        char _s;          // цифра, обозначающая, какого порядка производной будут даны граничащие значения
                          // (1 - производные первого порядка,
                          //  2 - производные второго порядка);
        T _0, _i;      // граничные условия  (для _k=2,3)
        unsigned _m;   // количество интервалов в результирующей сетке
                       // (т.е.количество узлов – m + 1,
                       //  что сделано для унификации с узлами исходной сетки);
        Vector<T> _res_x; // узлы результирующей сетки;
        char _t;          // символ, сообщающий, известно или нет аналитическое выражение для функции f(x)
                          // (y - аналитическое выражение известно,
                          //  n - аналитическое выражение неизвестно);
        char* _f;         // аналитическое выражение для функции (если оно известно).
        Vector<Polynomial<T>> _splines;
    public:
        SplineApproximation()
            : _original_cin{ std::cin.rdbuf() }, _original_cout{ std::cout.rdbuf() },
            _k(1), _n(-1), _0(0), _i(0),
            _x0(), _y0(), _m(0),
            _res_x(), _t('n'), _f(NULL){}
        // Установка потока ввода
        std::ifstream* setInputDevice(char input_method)
        {
            std::ifstream* fin = NULL;
            std::ofstream* fout = NULL;
            switch (input_method)
            {
            case '1': return NULL;
            case '2':
            {
                std::string filename;
                std::cout << "\n\tВведите имя входного файла:\n-> ";
                getline(std::cin, filename);
                fin = new std::ifstream(filename);
                // сохраняем старый поток ввода и перенаправляем его на пользовательский файл
                _original_cin = redirectInput(fin);
                if (!_original_cin)  return NULL;

                std::cout << "\n\tВведите имя выходного файла:\n-> ";
                getline(std::cin, filename);
                fout = new std::ofstream(filename);
                // сохраняем старый поток вывода и перенаправляем его на пользовательский файл
                _original_cout = redirectOutput(fout);
                if (!_original_cout)  return NULL;
                break;
            }
            case '3': case '4': case '5':
                if (input_method == '3')
                    fin = new std::ifstream("input_order_1.txt");
                else if (input_method == '4')
                    fin = new std::ifstream("input_order_2.txt");
                else
                    fin = new std::ifstream("input_order_3.txt");
                // сохраняем старый поток ввода и перенаправляем его на файл input_non-uniform_grid.txt 
                _original_cin = redirectInput(fin);
                if (!_original_cin) return NULL;

                fout = new std::ofstream("output.txt", std::ios::app);
                // сохраняем старый поток вывода и перенаправляем его на файл output.txt
                _original_cout = redirectOutput(fout);
                if (!_original_cout)  return NULL;
                break;
            default:
                throw std::invalid_argument("\n\t\tНет подходящего метода ввода данных...\n");
            }
            return fin;
        }
        // Считывание данных из текущего потока ввода
        void inputData(std::ifstream* in)
        {
            if (!in)
            {
                _k = getSymbol({ '0','1','2' }, "\n\tВведите требуемый порядок сплайна:"
                    "\n\t1 – линейный;"
                    "\n\t2 – параболический;"
                    "\n\t3 – кубический.\n-> ") - '0';
                _n = static_cast<unsigned>(getDouble(0, INT_MAX, "\n\tВведите количество сплайнов:\n-> "));
                _x0 = Vector<T>(_n + 1, false);
                _x0 = getGridX(_x0, _n + 1,
                        "\n\tВведите значения узлов интерполяционной сетки:\n",
                        "\n\tЗначения узлов должны идти строго по возрастанию. Введите другое значение.");
                std::cout << "\n\tВведите значения функции в узлах интерполяционной сетки:\n";
                _y0 = Vector<T>(_n + 1, false);
                for (unsigned i = 0; i <= _n; i++)
                    _y0[i] = getDouble(-DBL_MAX, DBL_MAX, (std::stringstream() << "-> [" << _x0[i] << "]: ").str()); 
                _m = static_cast<unsigned>(getDouble(0, INT_MAX, "\n\tВведите количество интервалов в результирующей сетке:\n-> "));
                _res_x = Vector<T>(_m + 1, false);
                _res_x =  getGridX(_res_x, _m + 1,
                        "\n\tВведите значения узлов результирующей интерполяционной сетки:\n",
                        "\n\t\t\tЗначения узлов должны идти строго по возрастанию. Введите другое значение.\n");
                
                if (_k == 2)
                {
                    _0 = static_cast<unsigned>(getDouble(0, INT_MAX, "\n\tВведите индекс граничного условия:\n-> "));
                    _i = static_cast<unsigned>(getDouble(0, DBL_MAX, "\n\tВведите значение граничного условия:\n-> "));
                }
                else if (_k == 3) 
                {
                    _s = getSymbol({ '1', '2' }, "\n\tКакого порядка производной будут даны граничащие значения:"
                        "\n\t1 - производные первого порядка;"
                        "\n\t2 - производные второго порядка\n-> ");
                    _0 = static_cast<unsigned>(getDouble(0, INT_MAX, "\n\tВведите первое граничное условие:\n-> "));
                    _i = static_cast<unsigned>(getDouble(0, DBL_MAX, "\n\tВведите второе граничное условие:\n-> "));
                }
                _t = getSymbol({ 'y', 'n' }, "\n\tИзвестно ли аналитическое выражение для функции f(x)?"
                    "\n\ty – да;"
                    "\n\tn – нет\n-> ");
                if (_t == 'y')
                {
                    std::string F;
                    char choice = 'y';
                    while (choice == 'y')
                    {
                        std::cout << "\n\tВведите выражение для функции:\n-> ";
                        getline(std::cin, F);
                        if (!F.empty())
                        {
                            _f = CreatePolStr(F.c_str(), 0);
                            if (GetError() != ERR_OK)
                            {
                                std::cerr << "\n\tДанное выражение не поддерживается.";
                                choice = getSymbol({ 'y','n' }, "\n\tПопробовать ещё раз? (y/n)\n-> ");
                            }
                            else choice = 'n';
                        }
                        else
                        {
                            std::cerr << "\n\tНельзя обработать пустую строку.";
                            choice = getSymbol({ 'y','n' }, "\n\tПопробовать ещё раз? (y/n)\n-> ");
                        }
                    }
                }
                if (in)
                {
                    std::cin.rdbuf(_original_cin); // сбрасываем поток до стандартного зарезервированного ввода
                    in->close();
                }
            }
            else
            {
                std::cin  >> _k >> _n;
                _x0 = Vector<T>(_n + 1, false);
                for (unsigned i = 0; i <= _n; i++)
                    std::cin >> _x0[i];
                _y0 = Vector<T>(_n + 1, false);
                for (unsigned i = 0; i <= _n; i++)
                    std::cin >> _y0[i];
                if (_k == 3)
                    std::cin >> _s;
                if (_k == 2 || _k == 3)
                    std::cin >> _0 >> _i;
                std::cin >> _m;
                _res_x = Vector<T>(_m + 1, false);
                for (unsigned i = 0; i <= _m; i++)
                    std::cin >> _res_x[i];
                std::cin >> _t;
                if (_t == 'y')
                {
                    std::cin.seekg(2, std::ios_base::cur);
                    std::string F;
                    getline(std::cin, F);
                    _f = CreatePolStr(F.c_str(), 0);
                    if (GetError() != ERR_OK)
                        std::cout << "\n\tНекорректно задана аналитическая функция (или не подлежит обработке). \n";
                }
            }
        }
        ~SplineApproximation()
        {
            if (_original_cout)
                std::cout.rdbuf(_original_cout); // сбрасываем до стандартного ввода с клавиатуры
            if (_f) { delete[] _f; _f = NULL; }
        }

        // возвратить порядок сплайна
        unsigned getSplOrd() const { return _k; } 
        // возвратить количество сплайнов
        unsigned getCountSpl() const { return _n; }
        // возвратить узлы исходной сетки
        const Vector<T>& getSourceGrid() const { return _x0;}
        // возвратить значения функции в узлах исходной сетки
        const Vector<T>& getValueGrid() const { return _y0; }
        // возвратить количество интервалов в результирующей сетке
        unsigned getCountRes() const { return _m; }
        const Vector<T>& getResultGrid() const { return _res_x; }
        char* getOrigAnalytic() const { return _f; }
        const Vector<Polynomial<T>>& getSplines() const { return _splines; }

        const Vector<Polynomial<T>>& composeSplines(unsigned ord)
        {
            switch (ord)
            {
            case 1: // линейные сплайны
                _splines = SplineFirstOrd(_x0, _y0);
                break;
            case 2: // параболические сплайны
            {  
                _splines = SplineSecondOrd(_x0, _y0, _0, _i);
                break;
            }
            case 3: // кубические сплайны
                _splines = SplineThirdOrd(_x0, _y0, _s, _0, _i);
                break;
            default: throw std::logic_error("Непредвиденный порядок сплайнов");
            }
            return  _splines;
        }
        private:
            // Сплайны первого порядка
            static Vector<Polynomial<T>> SplineFirstOrd(const Vector<T>& x, const Vector<T>& y)
            {
                size_t n = x.getLength() - 1;
                Vector<Polynomial<T>> Splines(n);
                
                for (int i = 0; i < n; i++)
                    Splines[i] = y[i]
                        + ((y[i + 1] - y[i])
                            / (x[i + 1] - x[i])
                            * Polynomial<T>({ -(T)x[i], 1 }));
                return Splines;
            }

            // Сплайны второго порядка 
            static Vector<Polynomial<T>> SplineSecondOrd(const Vector<T>& x, const Vector<T>& y, int index, T border)
            {
                size_t n = static_cast<size_t>(x.getLength()) - 1;
                Vector<Polynomial<T>> Splines(n);
                Vector<T> b(n + 1);
                if (index == 0)
                {
                    b[0] = border;
                    for (int i = 0; i < n; i++)
                        b[i + 1] = 2 * (y[i + 1] - y[i]) / (x[i + 1] - x[i]) - b[i];
                }
                else
                {
                    b[n] = border;
                    for (int i = n - 1; i >= 0; i--)
                        b[i] = 2 * (y[i + 1] - y[i]) / (x[i + 1] - x[i]) - b[i + 1];
                }
                for (int i = 0; i < (int)n; i++)
                    Splines[i] = y[i]
                        + (b[i] * Polynomial<T>({ -(T)x[i], 1 }))
                        + (((b[i + 1] - b[i])
                            / (2 * (x[i + 1] - x[i]))
                            * Polynomial<T>({ -(T)x[i], 1 }) * Polynomial<T>({ -(T)x[i], 1 })));
                return Splines;
            }

            // Сплайны третьего порядка
            static Vector<Polynomial<T>> SplineThirdOrd(const Vector<T>& x, const Vector<T>& y, char s, T left, T right)
            {
                size_t n = x.getLength();
                Vector<Polynomial<T>> Splines(n - 1);
                Matrix<T> A;
                Vector<T> g;
                if (s == '1') 
                {
                    A = Matrix<T>(n);
                    A[0][0] = (x[1] - x[0]) / 3;
                    g = Vector<T>(n);
                    g[0] = (y[1] - y[0]) / (x[1] - x[0]) - left;

                    for (int i = 1; i < n - 1; i++)
                    {
                        A[i][i] = (x[i] - x[i - 1] + x[i + 1] - x[i]) / 3;
                        A[i - 1][i] = A[i][i - 1] = (x[i] - x[i - 1]) / 6;
                        g[i] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]) - (y[i] - y[i - 1]) / (x[i] - x[i - 1]);
                    }
                    A[n - 1][n - 1] = (x[n - 1] - x[n - 2]) / 3;
                    A[n - 2][n - 1] = A[n - 1][n - 2] = (x[n - 1] - x[n - 2]) / 6;
                    g[n - 1] = right - (y[n - 1] - y[n - 2]) / (x[n - 1] - x[n - 2]);
                }
                else 
                {
                    A = Matrix<T>(n - 2);
                    g = Vector<T>(n - 2);
                    g[0] = (y[2] - y[1]) / (x[2] - x[1]) - (y[1] - y[0]) / (x[1] - x[0]) - (x[1] - x[0]) * left / 6;
                    
                    for (int i = 0; i < n - 2; i++)
                    {
                        A[i][i] = (x[i + 1] - x[i] + x[i + 2] - x[i + 1]) / 3;
                        if (i + 1 < n - 2)
                            A[i + 1][i] = A[i][i + 1] = (x[i + 2] - x[i + 1]) / 6;
                    }
                    for (int i = 1; i < n - 3; i++)
                        g[i] = (y[i + 1] - y[i]) / (x[i + 1] - x[i]) - (y[i] - y[i - 1]) / (x[i] - x[i - 1]);

                    g[n - 3] = (y[n - 1] - y[n - 2]) / (x[n - 1] - x[n - 2]) 
                        - (y[n - 2] - y[n - 3]) / (x[n - 2] - x[n - 3]) 
                        - (x[n - 1] - x[n - 2]) * right / 6;
                }
                
                Vector<T> M = SweepMethod(A, g);
                if (s == '2')
                {
                    T* temp_array = new T[n];
                    temp_array[0] = left;
                    for (int i = 1; i < n - 1; i++)
                        temp_array[i] = M[i - 1];
                    temp_array[n - 1] = right;
                    M = Vector<T>(n, false, temp_array);
                }
               
                for (int i = 0; i < n - 1; i++)
                    Splines[i] = y[i]
                        + (((y[i + 1] - y[i]) / (x[i + 1] - x[i])
                            - (x[i + 1] - x[i]) / 6 * (2 * M[i] + M[i + 1])) 
                            * Polynomial<T>({ -(T)x[i], 1 }))
                        + ((M[i] / 2)
                            * Polynomial<T>({ -(T)x[i], 1 }) * Polynomial<T>({ -(T)x[i], 1 }))
                        + (((M[i + 1] - M[i]) / (6 * (x[i + 1] - x[i])) )
                            * Polynomial<T>({ -(T)x[i], 1 }) * Polynomial<T>({ -(T)x[i], 1 }) * Polynomial<T>({ -(T)x[i], 1 }));
                return Splines;
            }

            // Решение Трёхдиагональной СЛАУ
            static Vector<T> SweepMethod(Matrix<T> A, const Vector<T> b)
            {
                size_t n = b.getLength();
                Vector<T> x(n);
                Vector<T> r(n);
                r[0] = -A[0][1] / A[0][0];
                Vector<T> v(n);
                v[0] = b[0] / A[0][0];
                // Прямой ход метода прогонки
                for (int i = 1; i < n - 1; i++)
                {
                    r[i] = -A[i][i + 1] / ( A[i][i] + A[i][i - 1] * r[i - 1]);
                    v[i] = (b[i] - A[i][i - 1] * v[i - 1]) / (A[i][i] + A[i][i - 1] * r[i - 1]);
                }
                v[n - 1] = (b[n - 1] - A[n - 1][n - 2] * v[n - 2]) / (A[n - 1][n - 1] + A[n - 1][n - 2] * r[n - 2]);
                // Обратный ход метода прогонки
                x[n - 1] = v[n - 1];
                for (int i = n - 2; i >= 0; i--)
                    x[i] = r[i] * x[i + 1] + v[i];
                return x;
            }

        void checkSourceGrid()
        {
            bool success = true;
            for (unsigned i = 0; i < _n; i++)
            {
                std::cout << "\tS_" << i << "(" << _x0[(unsigned)i] << ") = " << _splines[i](_x0[(unsigned)i]) << "\n";
                if (abs(_splines[i](_x0[(unsigned)i]) - _y0[i]) > EPS)
                {
                    success = false;
                    std::cout << "\t f(" << _x0[(unsigned)i] << ") = " << _y0[i]
                        << "\n\tЗначение сплайна в узле исходной сетки не совпадает с данным образом этого узла в исходной сетке. Погрешность: " << abs(_splines[i](_x0[(unsigned)i]) - _y0[i]) << "\n";
                }
            }
            std::cout << "\tS_" << _n - 1 << "(" << _x0[(unsigned)_n] << ") = " << _splines[_n - 1](_x0[(unsigned)_n]) << "\n";
            if (abs(_splines[_n - 1](_x0[(unsigned)_n]) - _y0[_n]) > EPS)
            {
                success = false;
                std::cout << "\t f(" << _x0[(unsigned)_n] << ") = " << _y0[_n]
                    << "\n\tЗначение сплайна в узле исходной сетки не совпадает с данным образом этого узла в исходной сетке. Погрешность: " << abs(_splines[_n - 1](_x0[(unsigned)_n]) - _y0[_n]) << "\n";
            }
            if (success) std::cout << "\tОбразы сплайнов в узлах исходной сетки совпадают с образами исходной сетки, данными изначально.";
        }

        void checkResGrid()
        {
            for (unsigned i = 0; i <= _m; i++)
                for (unsigned j = 0; j <= _m; j++)
                    if (_x0[j] <= _res_x[(unsigned)i] && _res_x[(unsigned)i] <= _x0[j + 1])
                    {
                        std::cout << "\tS_" << j << "(" << _res_x[(unsigned)i] << ") = " << _splines[j](_res_x[(unsigned)j]) << "\n";
                        if (_f)
                        {
                            T res_f = EvalPolStr(_f, _res_x[(unsigned)i], 0);
                            std::cout << "\tf(" << _res_x[(unsigned)i] << ") = " << res_f
                                << "\n\tПогрешность: " << abs(_splines[j](_res_x[(unsigned)j]) - res_f) << "\n";
                        }
                    }
        }
        
        friend std::ostream& operator<<(std::ostream& out, SplineApproximation& data)
        {
            std::cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
            std::streamsize precision = std::cout.precision();
            std::streamsize size = std::cout.width();
            std::cout << std::setprecision(precision);
            out << "\n\tЗаданный порядок сплайнов, интерполлирующих функцию: " << data.getSplOrd() << "\n"
                << "Прообразы сетки: " << "\t\t\t\t\t\t" << std::setw(size) << data.getSourceGrid()
                << "Соответствующие заданные образы сетки: " << "\t" << std::setw(size) << data.getValueGrid()
                << "\nСплайны порядка " << data.getSplOrd() << ":";
            for (int i = 0; i < data.getCountSpl(); i++)
                out << "\n\tSpline #"<<i << ": " << data.getSplines()[i];
            out << "\nСверка значений сплайнов с заданными образами сетки в исходных узлах: \n";
            data.checkSourceGrid();
            out << "\nПроверка значений сплайнов требуемого порядка в результирующей сетке:\n";
            data.checkResGrid();
            std::cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
            return out;
        }
    };

    std::streambuf* redirectInput(std::ifstream* in)
    {
        std::streambuf* original_cin = std::cin.rdbuf();
        while (!*in)
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
            in->open(filename);
        }
        //перенаправляем стандартный поток ввода на переданный файл
        std::cin.rdbuf(in->rdbuf());
        return original_cin;
    }

    std::streambuf* redirectOutput(std::ofstream* out)
    {
        std::streambuf* original_cout = std::cout.rdbuf();
        while (!*out)
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
            out->open(filename);
        }
        //перенаправляем стандартный поток вывода на переданный файл
        std::cout.rdbuf(out->rdbuf());
        return original_cout;
    }


    char getSymbol(std::initializer_list<char> list,
        std::string notification_message,
        std::string error_message)
    {
        char choice;
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

    double getDouble(double min, double max,
        std::string notification_message,
        std::string error_message)
    {
        std::string epsstr;
        double eps;
        do {
            std::cout << notification_message;
            std::cin >> epsstr;

            bool point = false, flag = false;
            auto it = epsstr.begin();
            if (it[0] == '-') it++;
            for (; it != epsstr.end(); it++)
                if (!isdigit(it[0]) && (it[0] != ',' || point))
                {
                    std::cout << error_message;
                    flag = true;
                    break;
                }
                else if (it[0] == ',' && !point) point = true;

            if (flag) continue;
            eps = std::stod(epsstr);
            if (eps <= min || eps >= max)
                std::cout << error_message;
            else { std::cin.ignore(32256, '\n'); break; }
        } while (true);
        return eps;
    }

    template<class T> Vector<T>& getGridX(Vector<T>& array, size_t size,
        std::string notification_message,
        std::string error_message)
    {
        std::cout << notification_message;
        int i = 0;
        array[i] = getDouble(-DBL_MAX, DBL_MAX, (std::stringstream() << "-> [" << i << "]: ").str());
        i++;
        do
        {
            array[i] = getDouble(-DBL_MAX, DBL_MAX, (std::stringstream() << "-> [" << i << "]: ").str());
            if (array[i] < array[i - 1]) std::cout << error_message;
            else i++;
        } while (i < size);
        return array;
    }
}
#endif