#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>

#pragma warning(disable: 4996)

int main(int argc, char* argv[])
{
	WSAData wsaData;
	if (WSAStartup(0x0101, &wsaData) == SOCKET_ERROR) {
		std::cout << "Error" << std::endl;
		exit(1);
	}

	SOCKADDR_IN addr;
	int addr_lenght = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1112);
	addr.sin_family = AF_INET;

	SOCKET server = socket(AF_INET, SOCK_STREAM, NULL);

	if (connect(server, (SOCKADDR*)&addr, addr_lenght) == SOCKET_ERROR)
	{
		std::cout << "Failed Connection to the Server!!!" << std::endl; return 1;
	}
	std::cout << "Присоединие к серверу через PROXY." << std::endl;

	char msg[256];
	memset(&msg, NULL, sizeof(msg));
	recv(server, msg, sizeof(msg), NULL);
	std::cout << msg << std::endl;

	return 0;
}