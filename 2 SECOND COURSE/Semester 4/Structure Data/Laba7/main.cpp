#include <iostream>
#include <vector>
#include <fstream>
#include <cstdarg>
#include <string>
#include <vector>
#include <time.h>
#include <ctime>
#include <chrono>
#define BITS_WORD 32
#define BITS_BYTE 8

//constexpr int MAX_BITS = 8;
//void binar(unsigned char* ptr, int bites)
//{
//
//	for (int i = bites - 1; i >= 0; --i)
//	{
//		for (int j = MAX_BITS - 1; j >= 0; --j)
//			std::cout << (ptr[i] >> j) % 2;
//		std::cout << " ";
//	}
//	std::cout << std::endl;
//}


namespace SaDPA
{
	template<typename T>
	void fillingFilesWithRandomElements(int fmt, ...)
	{
		va_list args;
		va_start(args, fmt);
		unsigned amountOfElements = 100;
		srand(static_cast<unsigned>(time(nullptr)));

		while (fmt > 0)
		{
			std::string str = va_arg(args, char*);
			std::ofstream file(str, std::ios::trunc);

			for (unsigned i = amountOfElements; i > 0; --i)
				file << rand() * rand() << ' ';
			file.close();

			amountOfElements *= 10;
			--fmt;
		}
		va_end(args);
	}

	template<typename T>
	std::vector<T> inputDataIntoVector(std::string strFile, int numberOfData = 0)
	{
		std::ifstream fin(strFile);
		if (fin.is_open())
		{
			T number;
			std::vector<T> arr;
			if (numberOfData == 0) numberOfData = arr.size();
			for (int i = 0; i < numberOfData; i++)
			{
				fin >> number;
				arr.push_back(number);
			}

			fin.close();
			return arr;
		}
		else std::cout << "Unable to open file";
		return std::vector<T>();
	}

	template<typename T>
	void outputDataIntoFile(std::vector<T>& vec, std::string strFile)
	{
		std::ofstream fout(strFile, std::ios::trunc);
		for (int i = 0; i < vec.size(); i++)
			fout << vec[i] << ' ';
	}

	template<typename T>
	bool digit(T key, int B)
	{
		return (key >> B) & 1;
	}

	unsigned swaps = 0;
	template<typename T>
	void binaryQuickSort(std::vector<T>& A, int first, int last, int d)
	{
		//std::cout << "d = " << d << '\n';
		if (first < last && d >= 0)
		{
			int k = sizeof(A[0]);
			int i = first, j = last - 1;
			/*for(int i = 0; i < A.size(); i++)
				binary((unsigned char*)&A[i], sizeof(A[i]));*/

			while (i < j)
			{
				while (digit(A[i], d) == false && j > i)
					i++;

				//std::cout << "Index i =" << i << '\n';
				while (digit(A[j], d) == true && j > i)
					j--;

				//std::cout << "Index j =" << j << '\n';
				if (i < j)
				{
					std::swap(A[i], A[j]);
					swaps++;
					/*std::cout << '\n';
					for (int i = 0; i < A.size(); i++)
						binary((unsigned char*)&A[i], sizeof(A[i]));*/
				}
			}
			if (digit(A[j], d) == 0) j++;
			//std::cout << "\nfrom " << first << " to " << j << '\n';
			binaryQuickSort(A, first, j, d - 1);
			//std::cout << "\nfrom " << j << " to " << last << '\n';
			binaryQuickSort(A, j, last, d - 1);
		}
	}

	template<typename T>
	int partition(std::vector<T>& arr, int start, int end)
	{

		T pivot = arr[start];

		int count = 0;
		for (int i = start + 1; i <= end; i++) {
			if (arr[i] <= pivot)
				count++;
		}

		// Giving pivot element its correct position
		int pivotIndex = start + count;
		std::swap(arr[pivotIndex], arr[start]);

		// Sorting left and right parts of the pivot element
		int i = start, j = end;

		while (i < pivotIndex && j > pivotIndex)
		{

			while (arr[i] <= pivot)
				i++;


			while (arr[j] > pivot)
				j--;


			if (i < pivotIndex && j > pivotIndex)
				std::swap(arr[i++], arr[j--]);

		}

		return pivotIndex;
	}

	template<typename T>
	void quickSort(std::vector<T>& arr, int start, int end)
	{

		// base case
		if (start >= end)
			return;

		// partitioning the array
		int p = partition(arr, start, end);

		// Sorting the left part
		quickSort(arr, start, p - 1);

		// Sorting the right part
		quickSort(arr, p + 1, end);
	}

	template <typename T>
	void unitTest(std::vector<T>& vec)
	{
		auto start = std::chrono::system_clock::now();
		swaps = 0;
		binaryQuickSort(vec, 0, vec.size(), BITS_WORD - 1);
		//quickSort(vec, 0, static_cast<int>(vec.size() - 1));
		auto end = std::chrono::system_clock::now();

		std::chrono::duration<double> elapsed_seconds = end - start;

		std::cout << "Sorting by " << vec.size() << " elements took elapsed time: " << elapsed_seconds.count() << "s\n"
			<< "Number of swaps: " << swaps << "\n"
			<< "Computational complexity of the algorithm: O(n)=" << vec.size() * BITS_WORD << "\n\n";
	}

}

using namespace SaDPA;


int main()
{
	fillingFilesWithRandomElements<int>(3, "input1.txt", "input2.txt", "input3.txt");
	std::vector<int> data100 = inputDataIntoVector<int>("input1.txt", 100);
	std::vector<int> data1000 = inputDataIntoVector<int>("input2.txt", 1000);
	std::vector<int> data10000 = inputDataIntoVector<int>("input3.txt", 10000);

	unitTest<int>(data100);
	unitTest<int>(data1000);
	unitTest<int>(data10000);

	outputDataIntoFile<int>(data100, "input1.txt");
	outputDataIntoFile<int>(data1000, "input2.txt");
	outputDataIntoFile<int>(data10000, "input3.txt");

	getchar();
	return 0;
}
