#pragma once
#include <string>
#include <iostream>
#include <map>
#include <fstream>

class Ciphers {
	protected:
		std::string _alphabet;
		int length_alphabet;

		int _shift;

		std::string message;
		std::string cipher_message;
		std::string originall_message;
		int length_message;

		virtual std::string encryption() = 0;
		virtual std::string decryption() = 0;

	public:
		virtual std::string get_alphabet() const = 0;
		virtual int get_length_alphabet() const = 0;

		virtual std::string get_text_from_file(const std::string &name_file) const = 0;

		virtual std::string get_message() const = 0;
		virtual std::string get_cipher_message() const = 0;
		virtual std::string get_originall_message() const = 0;
		virtual int get_length_message() const = 0;

		virtual void print_hash_table() = 0;

		friend std::ostream& operator<<(std::ostream& output, const Ciphers& cipher) {
			return output << "Испольуемый алфавит: " << cipher._alphabet << \
			"\n\nНачальное сообщение: " << cipher.message << \
			"\nЗашифрованное сообщение: " << cipher.cipher_message << \
			"\nРасшифрованное сообщение: " << cipher.originall_message << '\n';
    	}
};