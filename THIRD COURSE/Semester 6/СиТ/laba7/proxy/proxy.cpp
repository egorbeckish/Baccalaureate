
#include "socket_functions.h"

int main() {

	
	cout << "Подключение!\n";
	char msg[256];

	Socket client_socket(msg);

	int a;
	std::cin >> a;
	client_socket.SendPacketToClient("123");

	return 0;
}