#include <iostream>
#include "Datah.h"
using namespace Base;

int main()
{
    setlocale(LC_ALL, "Rus");
    InputData<double> data;

    switch (data.getMethod())
    {
    case InputData<double>::METHOD::GAUSS:
        switch (data.getTask())
        {
        case InputData<double>::TASK::ROOT:
            data.getRoot(InputData<double>::GaussMethod);
            break;
        case InputData<double>::TASK::DETERMINANT:
            data.getDeterminant();
            break;
        case InputData<double>::TASK::INVERS:
            data.setInverseMatrixByMethod(InputData<double>::GaussMethod);
            break;
        }
        break;
    case InputData<double>::METHOD::DECOMPOSOTION:
        switch (data.getTask())
        {
        case InputData<double>::TASK::ROOT:
            data.getRoot(InputData<double>::DecompositionMethod);
            break;
        case InputData<double>::TASK::DETERMINANT:
            data.getDeterminant();
            break;
        case InputData<double>::TASK::INVERS:
            data.setInverseMatrixByMethod(InputData<double>::DecompositionMethod);
            break;
        }
        break;
    case InputData<double>::METHOD::SIMPLEITERATION:
        switch (data.getTask())
        {
        case InputData<double>::TASK::ROOT:
            data.getRoot(InputData<double>::SimpleIterationMethod);
            break;
        case InputData<double>::TASK::DETERMINANT:
            data.getDeterminant();
            break;
        case InputData<double>::TASK::INVERS:
            data.setInverseMatrixByMethod(InputData<double>::SimpleIterationMethod);
            break;
        }
        break;
    case InputData<double>::METHOD::SEIDEL:
        switch (data.getTask())
        {
        case InputData<double>::TASK::ROOT:
            data.getRoot(InputData<double>::SeidelMethod);
            break;
        case InputData<double>::TASK::DETERMINANT:
            data.getDeterminant();
            break;
        case InputData<double>::TASK::INVERS:
            data.setInverseMatrixByMethod(InputData<double>::SeidelMethod);
            break;
        }
        break;
    }
    return 0;
}