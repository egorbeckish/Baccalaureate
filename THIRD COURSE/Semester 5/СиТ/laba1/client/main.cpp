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
	addr.sin_port = htons(12345);
	addr.sin_family = AF_INET;

	SOCKET server = socket(AF_INET, SOCK_STREAM, NULL);

	if (connect(server, (SOCKADDR*)&addr, addr_lenght) == SOCKET_ERROR) 
	{ std::cout << "Failed Connection to the Server!!!" << std::endl; return 1; }
	std::cout << "Connect to the Server." << std::endl;

	char msg[1024], msg_size[3], split_size[3];
	while (true)
	{
		std::string msg_client, size_split, size_msg;

		std::cout << "Send a message:";
		std::getline(std::cin, msg_client);
		memset(&msg, NULL, sizeof(msg));
		strcpy(msg, msg_client.c_str());


		if (msg_client == "exit")
		{ 
			std::cout << "You disconnect of the server." << std::endl; 
			send(server, (char*)&msg, sizeof(msg), NULL);
			break; 
		}

		std::cout << "Send a size message:";
		std::getline(std::cin, size_split);
		memset(&split_size, NULL, sizeof(split_size));
		strcpy(split_size, size_split.c_str());

		send(server, (char*)&msg, sizeof(msg), NULL);
		send(server, (char*)&split_size, sizeof(split_size), NULL);

		recv(server, (char*)&msg, sizeof(msg), NULL);
		std::cout << "\n\nServer return your:\n" << msg << "\n\n" << std::endl;


	}

	system("pause");
	return 0;
}