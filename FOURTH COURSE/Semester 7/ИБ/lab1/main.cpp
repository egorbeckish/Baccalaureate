#include <iostream>
#include <string>
#include "Chipers/abash_cipher.cpp"
//g++ -o main.cpp


int main() {
	Abash_Cipher Abash("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "file.txt");
	std::cout << Abash << std::endl;

	return 0;
}