#pragma comment(lib, "Ws2_32.lib")

#include <winsock.h>
#include <iostream>
#include <string>

using namespace std;

class Socket
{
	SOCKET sock;
public:
	Socket()
	{
		WSAData wsaData;
		WORD DLLVersion = MAKEWORD(2, 1);
		if (WSAStartup(DLLVersion, &wsaData) != 0) {
			std::cout << "Error" << std::endl;
			exit(1);
		}

		SOCKADDR_IN addr;
		int sizeofaddr = sizeof(addr);
		addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
		addr.sin_port = htons(1112); 
		addr.sin_family = AF_INET;

		SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
		bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
		listen(sListen, SOMAXCONN);

		sock = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);
	}

	void SendPacketToProxy(const string& to_send)
	{
		if (sock == 0) {
			std::cout << "Error #2\n";
		}
		else {
			cout << to_send << std::endl;
			cout << to_send.c_str() << std::endl;
			cout << to_send.size() << std::endl;
			send(sock, to_send.c_str(), to_send.size() + 1, NULL);
		}
	}

	~Socket()
	{
		closesocket(sock);
	}
};