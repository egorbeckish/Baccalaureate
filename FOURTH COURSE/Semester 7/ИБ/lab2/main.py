#Инициализация S-блока
def KSA(key: bytes) -> list[bytes]:
	s_block: list[int] = list(range(256))

	j: int = 0
	for i in range(256):
		j = (j + s_block[i] + key[i % len(key)]) % 256
		s_block[i], s_block[j] = s_block[j], s_block[i]

	return s_block

#Генерация псевдослучайного слова K
def PRGA(s_block: list[int]):
	i: int = 0
	j: int = 0
	while True:
		i = (i + 1) % 256
		j = (j + s_block[i]) % 256
		s_block[i], s_block[j] = s_block[j], s_block[i]
		k = s_block[(s_block[i] + s_block[j]) % 256]
		yield k

def RC4(s_block: list[bytes]) -> list[bytes]:
	key = PRGA(s_block) 
	for _ in range(256):
		next(key)

	return key

def xor(text: bytes, key: bytes) -> list[bytes]: 
	result: list[bytes] = []
	for symbol_byte in text: 
		try: 
			symbol_byte = ord(symbol_byte)
		except: 
			pass 

		result += [symbol_byte ^ next(key)]
    
	return result


def get_byte_key() -> bytes:
	return open('key.txt', 'rb').read()

def get_byte_text_from_file() -> bytes:
	return open('file.txt', 'rb').read()


key_byte = get_byte_key()
key = KSA(key_byte)

text_byte = get_byte_text_from_file()

key_cipher = RC4(key[:])
cipher_byte = xor(text_byte, key_cipher)

open('cipher_text.txt', 'wb').write(bytes(cipher_byte))

key_decrypted = RC4(key[:])
decrypted_byte = xor(cipher_byte, key_decrypted)

open('decrypted_text.txt', 'wb').write(bytes(decrypted_byte))