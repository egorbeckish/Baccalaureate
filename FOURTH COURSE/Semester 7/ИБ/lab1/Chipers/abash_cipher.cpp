#include "ciphers.h"


class Abash_Cipher : virtual public Ciphers {
	private:
		std::map<char, char> hash_table_alphabet;
		
	public:
		Abash_Cipher(const std::string & alphabet, std::string name_file) {
			_alphabet = alphabet;
			length_alphabet = _alphabet.length();
			hash_table_alphabet = get_hash_table_alphabet();

			message = get_text_from_file(name_file);
			length_message = message.length();
			cipher_message = encryption();
			originall_message = decryption();

			std::cout << "\t\t\t\tШифр Абаша\n" << std::endl;
		}

		std::string get_alphabet() const override {
			return _alphabet;
		}

		int get_length_alphabet() const override {
			return length_alphabet;
		}

		std::map<char, char> get_hash_table_alphabet() {
			for (int i = 0; i < length_alphabet; i ++) {
				hash_table_alphabet.emplace(_alphabet[i], _alphabet[length_alphabet - i - 1]);
			}

			return hash_table_alphabet;
		}

		void print_hash_table() override {
			if (hash_table_alphabet.empty()) {
				std::cout << "Hash table is empty." << std::endl;
				return;
			}

			std::cout << "\t Словарь зашифрованных символов\n" << std::endl;

			for (const auto &[key, value] : hash_table_alphabet) {
				std::cout << "Первоначальная буква: " << key << "  ->  Зашифрованная буква: " << value << std::endl;
			}

		}

		std::string encryption() override {
			for (int i = 0; i < length_message; i ++) {
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
			for (int i = 0; i < length_message; i ++) {
				if (isalpha(cipher_message[i])) {
					if (isupper(cipher_message[i])) {
						originall_message += hash_table_alphabet[cipher_message[i]];
					}

					else {
						originall_message += std::tolower(hash_table_alphabet[std::toupper(cipher_message[i])]);
					}
				}

				else {
					originall_message += cipher_message[i];
				}
			}

			return originall_message;
		}

		std::string get_text_from_file(const std::string &name_file) const override {
			std::ifstream in(name_file);

			std::string text = "", tmp;
			if (in.is_open()) {
				while (std::getline(in,tmp)) {
					text += tmp;
				}

				return text;
			}

			in.close();
			return "Файл закрыт!!!";
		}

		std::string get_message() const override {
			return message;
		}

		std::string get_cipher_message() const override {
			return cipher_message;
		}

		std::string get_originall_message() const override {
			return originall_message;
		}

		int get_length_message() const  override {
			return length_message;
		}
};



