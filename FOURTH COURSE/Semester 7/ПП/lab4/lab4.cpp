#include <iostream>
#include <omp.h>
#include <math.h>
#include <fstream>
#include <string>
#define CHUNK 1000

static double f(double a, double c);
static double fi(double a, double c);

void lab4(int argc, char* argv[])
{
	std::ofstream fout("output.txt", std::ios::app);
	fout << "\n\n-------------------------------------------------------------";
	int intervals = 100'000'000;
	fout << "\nNumber of intervals: " << intervals;

	double xl = -0.2, xh = 1.0, c = 0.9;

	//Функция omp_get_max_threads() возвращает максимально допустимое чис -
	//ло нитей для использования в следующей параллельной области.
	int max_threads = omp_get_max_threads();
	fout << "\nMaximum number of threads: " << max_threads;
	if (argv[1])
		omp_set_num_threads(std::stoi(argv[1]));

//Директива parallel
//	Параллельная область задаётся при помощи директивы parallel(parallel ... end parallel).
#pragma omp parallel

//Директива master
//	Директивы master(master ... end master) выделяют участок кода, кото -
//	рый будет выполнен только нитью - мастером.Остальные нити просто про -
//	пускают данный участок и продолжают работу с оператора, расположенного
//	следом за ним.Неявной синхронизации данная директива не предполагает.
#pragma omp master
	fout << "\nEvaluation on " << omp_get_num_threads() << " threads";

	double integral = 0;
	double step = (xh - xl) / (double)intervals;
	fout << "\nStep: " << step << '\n';

	//Функция omp_get_wtime() возвращает в вызвавшей нити астрономическое
	//время в секундах(вещественное число двойной точности), прошедшее с не -
	//которого момента в прошлом.
	double startwtime = omp_get_wtime();
	
	fout << "\nDYNAMIC chunk:" << CHUNK;
	//fout << "\nSTATIC chunk:" << CHUNK;
	// fout << "\nSTATIC auto";
	// fout << "\nDYNAMIC auto";


//shared(список) – задаёт список переменных, общих для всех нитей.

//reduction(оператор:список) – задаёт оператор и список общих пе -
//	ременных; для каждой переменной создаются локальные копии в каж -
//	дой нити; локальные копии инициализируются соответственно типу
//	оператора(для аддитивных операций – 0 или его аналоги, для мульти -
//	пликативных операций – 1 или её аналоги); над локальными копиями
//	переменных после завершения всех итераций цикла выполняется за -
//	данный оператор;

//schedule(type[, chunk]) – опция задаёт, каким образом итерации
//	цикла распределяются между нитями;
#pragma omp parallel for shared(step, xl, c) reduction (+: integral) schedule(static, CHUNK) 
	for (int i = 1; i <= intervals; i++)
	{
		double x = xl + step * ((double)i - 0.5);
		integral += f(x, c) * step;
		// #pragma omp critical
		//     std::cout << omp_get_thread_num()
		//               << ": " << "x=" << x << ";\t f(x)=" << f(x, c) 
		//               << "; \tpart of integral=" << integral << '\n';
	}
	fout << std::scientific << "\nIntegral is approximately: " << integral;
	fout << std::scientific << "\nError: " << integral - fi(xh, c) + fi(xl, c);
	fout << std::scientific << "\nTime of calculation: " << omp_get_wtime() - startwtime;
	fout << std::endl;
}

int main(int argc, char** argv)
{
	lab4(argc, argv);
		
	return 0;
}


static double f(double a, double c)
{
	return 1 / (1 + pow(c * a, 2));
}


static double fi(double a, double c)
{
	return (1 / c) * atan(c * a);
}
