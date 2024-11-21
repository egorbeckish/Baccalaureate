#include "Socket_functions.h"

using namespace std;

int main()
{
	Socket task_socket; // создаем сокет (ср. "Socket_functions.h")
	string ip;
	int a;
	std::cin >> a;

	task_socket.SendPacketToProxy("123"); // отправляем в прокси-сервер
	return 0;
}