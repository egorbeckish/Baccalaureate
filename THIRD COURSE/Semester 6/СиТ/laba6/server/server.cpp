#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include <unordered_map>

#pragma warning(disable: 4996)



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
	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);
	
	// привязать
	SOCKADDR_IN addr;
	int addr_lenght = sizeof(addr);
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(12345);
	bind(sockSrv, (SOCKADDR*)&addr, sizeof(SOCKADDR));

	char recvBuf[100];
	char msg[100];

	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);

	std::cout << "UDP сокет создан\n" << std::endl;
	while (true)
	{
		memset(&recvBuf, NULL, sizeof(recvBuf));
		recvfrom(sockSrv, recvBuf, 100, 0, (SOCKADDR*)&addrClient, &len);
		std::cout << inet_ntoa(addrClient.sin_addr) << htons(addrClient.sin_port) << " Клиент отправил длину массива = " << recvBuf << std::endl;

		int n = std::stoi(recvBuf);
		std::string tmp = "";
		
		int* a = new int[n];
		for (int i = 0; i < n; i++)
		{
			tmp += std::to_string(std::rand() % 100 - 50) + "\t";
		}
		tmp += std::to_string(htons(addrClient.sin_port)) + "\t";

		strcpy(msg, tmp.c_str());
		sendto(sockSrv, msg, strlen(msg) + 1, 0, (SOCKADDR*)&addrClient, len);
	}


	

	return 0;
}