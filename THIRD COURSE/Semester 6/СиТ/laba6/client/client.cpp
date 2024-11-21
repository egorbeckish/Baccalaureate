#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>

#pragma warning(disable: 4996)

int* _split(std::string a, std::string delimiter, int n)
{
	size_t position;
	int* arr = new int[n];
	int i = 0;

	while ((position = a.find(delimiter)) != std::string::npos)
	{
		int el = std::stoi(a.substr(0, position));
		arr[i] = el;
		i++;
		a.erase(0, position + delimiter.length());
	}

	return arr;
}

int result_sum(std::string a, std::string delimiter, int n)
{
	size_t position;
	int i = 0;
	int counter = 0;

	while ((position = a.find(delimiter)) != std::string::npos)
	{
		int el = std::stoi(a.substr(0, position));
		counter++;
		a.erase(0, position + delimiter.length());
	}

	return (counter == n);
}

int partition(int arr[], int low, int high)
{
	int pivot = arr[high];
	int i = (low - 1);

	for (int j = low; j <= high; j++)
	{
		if (arr[j] < pivot)
		{
			i++;
			std::swap(arr[i], arr[j]);
		}
	}

	std::swap(arr[i + 1], arr[high]);
	return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);

		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

int main()
{
	srand(time(NULL));

	// Загружаем библиотеку сокетов
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2, 2);

	if (WSAStartup(0x0101, &wsaData) == SOCKET_ERROR) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	// Создаем сокет
	SOCKET client = socket(AF_INET, SOCK_DGRAM, 0);

	// Отправить
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(12345);


	char recvBuf[100];
	char sendBuf[100];
	int len = sizeof(SOCKADDR);

	/*int n = 1 + std::rand() % 20;
	std::cout << n << std::endl;*/

	std::string choose;
	std::cout << "Получить задачу [y/n]: ";
	std::cin >> choose;
	std::cout << "\n\n";

	if (choose == "y")
	{

		while (true)
		{
			int n = 1 + std::rand() % 20;
			strcpy(sendBuf, std::to_string(n + 1).c_str());

			std::cout << "Длина массива, которую хотим получить = " << n << std::endl;
			sendto(client, sendBuf, sizeof(sendBuf), 0, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

			memset(&recvBuf, NULL, sizeof(recvBuf));
			recvfrom(client, recvBuf, sizeof(recvBuf), 0, (SOCKADDR*)&addrSrv, &len);

			if ('q' == recvBuf[0])
			{
				break;
			}

			int counter = result_sum(recvBuf, "\t", n);
			while (counter == 0)
			{
				int n = 1 + std::rand() % 20;
				strcpy(sendBuf, std::to_string(n).c_str());

				std::cout << "Длина массива, которую хотим получить = " << n << std::endl;
				sendto(client, sendBuf, sizeof(sendBuf), 0, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

				memset(&recvBuf, NULL, sizeof(recvBuf));
				recvfrom(client, recvBuf, sizeof(recvBuf), 0, (SOCKADDR*)&addrSrv, &len);
			}

			std::cout << counter << std::endl;
			int* arr = _split(recvBuf, "\t", n);

			std::cout << htons(addrSrv.sin_port);
			std::cout << "Полученный массив - [";
			for (int i = 0; i < n; i++)
			{
				if (i == n - 1)
				{
					std::cout << arr[i] << "]\n";
				}

				else
				{
					std::cout << arr[i] << ", ";
				}
			}

			std::cout << "Отсортированный массив - [";
			quickSort(arr, 0, n - 1);
			for (int i = 0; i < n; i++)
			{
				if (i == n - 1)
				{
					std::cout << arr[i] << "]\n";
				}

				else
				{
					std::cout << arr[i] << ", ";
				}
			}

			break;
		}
	}

	system("pause");


	return 0;
}