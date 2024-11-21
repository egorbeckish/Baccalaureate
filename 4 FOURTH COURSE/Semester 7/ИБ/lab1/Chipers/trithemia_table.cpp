#include "ciphers.h"

class Trithemia_Table : public Ciphers {
	private:
		std::map<int, std::string> hash_table_alphabet;

	public:
		Trithemia_Table(std::string alphabet, std::string name_file) {
			_alphabet = alphabet;
			length_alphabet = _alphabet.length();

			hash_table_alphabet = get_hash_table_alphabet();
		
			message = get_text_from_file(name_file);
			length_message = message.length();
			cipher_message = encryption();
			originall_message = decryption();

			std::cout << "\t\t\t\tТаблица Тритемия\n" << std::endl;	
		}

		std::string get_alphabet() override {
			return _alphabet;
		}

		int get_length_alphabet() override {
			return length_alphabet;
		}

		std::map<int, std::string> get_hash_table_alphabet() {
			for (int i = 0; i < length_alphabet; i ++) {
				if (i == 0) {
					hash_table_alphabet.emplace(i, _alphabet);
				}

				else {
					char symbol = _alphabet.substr(0, i + 1)[i];
					std::string cipher_string = _alphabet.substr(_alphabet.find(symbol), length_alphabet) + _alphabet.substr(0, i);
					hash_table_alphabet.emplace(i, cipher_string); 
				}		
			}

			return hash_table_alphabet;
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

		std::string encryption() override {
			for (int i = 0; i < length_message; i ++) {
				if (isalpha(message[i])) {
					char symbol = message[i];
					int index = hash_table_alphabet[i].find(message[i]);
					int c = (index + i) % length_alphabet;
					std::cout << i << "  " << message[i] << "  " << hash_table_alphabet[i] << "  " << index << "  " << c << "  " << hash_table_alphabet[i][c] << std::endl;
				}

				else {
					std::cout << message[i] << std::endl;
				}
			}
			//return cipher_message;
			return "encryption message";
		}

		std::string decryption() override {
			return "decryption message";
		}

		int get_length_message() override {
			return length_message;
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