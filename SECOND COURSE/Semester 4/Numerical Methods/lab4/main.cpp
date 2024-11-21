#include <iostream>
#include "NonlinearEquations.h"

using namespace Math;

void m()
{
    NonlinearEquations<double> data;
    switch (data.getMethod())
    {
    case NonlinearEquations<double>::METHOD::NEWTON:  // Метод Ньютона (+ Метод Итераций)
        data.Newton();
        break;
    case NonlinearEquations<double>::METHOD::STEEPESTDESCENT: // Метод наискорейшего спуска
        data.SteepestDescent();
        break;
    }

}