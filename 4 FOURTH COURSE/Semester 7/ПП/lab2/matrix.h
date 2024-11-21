#pragma once

#include <math.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>
#include "process.h"


class Matrix : public Process {
	private:
		int _rows, _columns;
		double startwtime, endwtime;
		float* _matrix;

		std::ofstream fout;

	public:
		Matrix(int argc, char* argv[], std::string filename = "output.txt", int rows = 5, int columns = 5, MPI_Comm comm = MPI_COMM_WORLD) : Process(argc, argv, comm) {
			fout.open(filename, std::ios::out);
			
			_rows = rows;
			_columns = columns;
			_matrix = new float[_rows * _columns];

			if (process_ID == Process::INIT)
			{
				Init_Process::printInfo("", fout);
				random_value();
				Process::printInfo("INITIAL RANDOM MATRIX", fout);
				fout << *this; fflush(NULL);
				Process::printInfo("\t--------------------------------", fout);
			}

			startwtime = MPI_Wtime();
		}

		~Matrix() {
			fout.close();
			delete _matrix;
		}

		float* get_matrix() const {
			return _matrix;
		}

		int get_rows() const {
			return _rows;
		}

		int get_columns() const {
			return _columns;
		}

		void random_value() {
			std::random_device rnd_device;
			std::mt19937 mersenne_engine{ rnd_device() };
			std::uniform_real_distribution<float> distribution(-100.0f, 100.0f);

			for (int i = 0; i < _rows; i++) {
				for (int j = 0; j < _columns; j++) {
					_matrix[i * _columns + j] = distribution(mersenne_engine);
				}
			}
		}

		static float* _reverse(float* a, int rows, int columns) {
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns / 2; j++) {
					std::swap(a[i * columns + j], a[i * columns + (columns - j - 1)]);
				}
			}

			return a;
		}

		void printInfo(std::string accompanying_message = "", std::ostream& out = std::cout, float* buf = NULL, int length = 0) {
			Process::printInfo("\n", out);
			if (buf)
				for (int i = 0; i < length / _columns; i++)
				{
					for (int j = 0; j < _columns; j++)
						out << std::setw(10) << buf[i * _columns + j] << " ";
					out << "\n"; fflush(NULL);
				}
			fflush(NULL);
		}

		void scatterv() {
			int count = _rows / numprocs;
			int ost = _rows % numprocs;

			int* adispls = new int[numprocs];
			int* acounts = new int[numprocs];

			for (int i = 0; i < numprocs; i++)
			{
				int scol = i < ost ? _columns * (count + 1) : _columns * count;
				acounts[i] = i < ost ? _columns * (count + 1) : _columns * count;

				int nach = (i * scol + (i >= ost ? ost : 0)) * _columns;
				adispls[i] = (i * scol + (i >= ost ? ost : 0)) * _columns;
			}

			int scol = process_ID < ost ? _columns * (count + 1) : _columns * count;
			int nach = process_ID * scol + (process_ID >= ost ? ost : 0);


			float* map = new float[scol * _columns];
			MPI_Scatterv(_matrix, acounts, adispls, MPI_FLOAT, map, scol * _columns, MPI_FLOAT, 0, MPI_COMM_WORLD);

			_reverse(map, scol, _columns);
			//printInfo("", std::cout, map, scol);

			MPI_Gatherv(map, scol, MPI_FLOAT, _matrix, acounts, adispls, MPI_FLOAT, 0, MPI_COMM_WORLD);

			fout << *this;
			std::stringstream str;
			str << std::scientific << "Time of calculation: " << endwtime - startwtime;
			Process::printInfo(str.str(), fout);
			Process::printInfo("\t--------------------------------", fout);
			fflush(NULL);
			str.clear();
			str.str("");
		}

		friend std::ostream& operator<<(std::ostream& out, Matrix& matrix) {
			out << "\nRows: " << matrix._rows <<
				"\nColumns: " << matrix._columns << "\n" << std::endl;

			for (int i = 0; i < matrix._rows; i++) {
				for (int j = 0; j < matrix._columns; j++) {
					out << std::setw(10) << std::fixed << std::setprecision(2) << matrix._matrix[i * matrix._columns + j] << " ";
					fflush(NULL);
				}

				out << std::endl;
			}
			out << "\n" << std::endl;
			fflush(NULL);

			return out;
		}
};


