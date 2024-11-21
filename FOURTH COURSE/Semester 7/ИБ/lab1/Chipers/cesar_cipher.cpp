#include "ciphers.h"

class Cesar_Cipher : public Ciphers {
	private:
		std::map<char, char> hash_table_alphabet;

	public:
		Cesar_Cipher(std::string alphabet, std::string name_file, int shift) {
			_alphabet = alphabet;
			length_alphabet = _alphabet.length();

			_shift = shift;
			hash_table_alphabet = get_hash_table_alphabet();
		
			message = get_text_from_file(name_file);
			length_message = message.length();
			cipher_message = encryption();
			originall_message = decryption();

			std::cout << "\t\t\t\tШифр Цезаря(сдвига)\n" << std::endl;
		}

		std::string get_alphabet() {
			return _alphabet;
		}

		int get_length_alphabet() {
			return length_alphabet;
		}

		std::string get_text_from_file(std::string name_file) override {
			std::ifstream in(name_file);

			std::string text = "", tmp;
			if (in.is_open()) {
				while (std::getline(in, tmp)) {
					text += tmp;
				}

				return text;
			}

			in.close();
			return "Файл закрыт!!!";
		}

		std::string get_message() override {
			return message;
		}

		std::string get_cipher_message() override {
			return cipher_message;
		}

		std::string get_originall_message() override {
			return originall_message;
		}

		int get_length_message() override {
			return length_message;
		}

		std::string encryption() override {
			if (length_message < _shift || _shift < 0) {
				return "Сдвиг больше или меньше длины алфавита. Введите другое значение";
			}

			if (length_message == _shift || _shift == 0) {
				cipher_message = message;
				return cipher_message;
			}


			for (int i = 0; i < length_message; i++) {
				if (isalpha(message[i])) {
					if (isupper(message[i])) {
						cipher_message += hash_table_alphabet[message[i]];
					}

					else {
						cipher_message += std::tolower(hash_table_alphabet[std::toupper(message[i])]);
					}
				}

				else {
					cipher_message += message[i];
				}
			}

			return cipher_message;
		}

		std::string decryption() override {
			if (length_message < _shift || _shift < 0) {
				return "Сдвиг больше или меньше длины алфавита. Введите другое значение";
			}

			if (length_message == _shift || _shift == 0) {
				originall_message = message;
				return originall_message;
			}

			_shift = length_alphabet - _shift;
			std::map<char, char> tmp;
			for (int i = 0; i < length_alphabet; i ++) {
				if (i + _shift >= length_alphabet) {
					tmp.emplace(_alphabet[i], _alphabet[(_shift + i) - length_alphabet]);
				}

				else {
					tmp.emplace(_alphabet[i], _alphabet[_shift + i]);
				}
			}

			for (int i = 0; i < length_message; i ++) {
				if (isalpha(cipher_message[i])) {
					if (isupper(cipher_message[i])) {
						originall_message += tmp[cipher_message[i]];
					}

					else {
						originall_message += std::tolower(tmp[std::toupper(cipher_message[i])]);
					}
				}

				else {
					originall_message += cipher_message[i];
				}
			}

			return originall_message;
		}

		std::map<char, char> get_hash_table_alphabet() {
			for (int i = 0; i < length_alphabet; i++) {
				if (i + _shift >= length_alphabet) {
					hash_table_alphabet.emplace(_alphabet[i], _alphabet[(i + _shift) - length_alphabet]);
				}

				else {
					//std::cout << "shift no" << '\t' << _alphabet[i] << '\t' << _alphabet[i + _shift] << std::endl;
					hash_table_alphabet.emplace(_alphabet[i], _alphabet[i + _shift]);
				}
			}

			return hash_table_alphabet;
		}

		void print_hash_table() override {
			if (hash_table_alphabet.empty()) {
				std::cout << "Hash table is empty." << std::endl;
				return;
			}

			for (const auto& [key, value] : hash_table_alphabet) {
				std::cout << "Первоначальная буква: " << key << "  ->  Зашифрованная буква: " << value << std::endl;
			}
		}
};