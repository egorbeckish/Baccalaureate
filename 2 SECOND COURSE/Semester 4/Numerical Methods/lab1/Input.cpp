#include "Input.h"

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

double getDouble(double min, double max, std::string notification_message, std::string error_message)
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