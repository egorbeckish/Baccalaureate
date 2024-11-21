#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <iostream>
#include <string>
#include <unordered_map>

#pragma warning(disable: 4996)

std::string split(std::string str, int delim)
{
	std::string _string{ "\n\nmessage - " };

	if (delim == NULL) return str + "\n\n";
	if (delim != NULL && strlen(str.c_str()) <= delim) return str + " (hash: " + std::to_string(std::hash<std::string>{}(str)) + "\n\n";

	int counter = 0;
	std::string temp{ "" };
	for (auto symbol : str)
	{
		if (counter == delim) 
		{ 
			counter = 0; 
			_string += " (hash: " + std::to_string(std::hash<std::string>{}(temp)) + ")\nmessage - "; 
			temp = ""; 
		}

		_string += symbol;
		temp += symbol;
		counter++;
	}

	return _string + " (hash: " + std::to_string(std::hash<std::string>{}(temp)) + ")\n\n";
}


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
	bind(server, (SOCKADDR*)&addr, sizeof(addr));
	listen(server, SOMAXCONN);

	SOCKET server_connection;
	server_connection = accept(server, (SOCKADDR*)&addr, &addr_lenght);
	if (server_connection == NULL) { return 1; }
	std::cout << "Client is connection." << std::endl;

	char msg[1024], msg_size[10];
	while (true)
	{
		std::cout << "Wait by client send a message..." << std::endl;
		memset(&msg, NULL, sizeof(msg));
		recv(server_connection, (char*)&msg, sizeof(msg), NULL);
		std::cout << "Client send: " << msg << std::endl;

		if (!strcmp("exit", msg)) { std::cout << "Client disconnect of the server\nServer CLOSE!!!" << std::endl; }
		recv(server_connection, (char*)&msg_size, sizeof(msg_size), NULL);
		std::cout << "Client asked to return the offers in size: " << msg_size << std::endl;

		std::string msg_server = split(msg, std::stoi(msg_size));
		strcpy(msg, msg_server.c_str());
		std::cout << "\n\nReturn client his:\n" << msg << std::endl;
		send(server_connection, (char*)&msg, sizeof(msg), NULL);
	}



	system("pause");
	return 0;
}