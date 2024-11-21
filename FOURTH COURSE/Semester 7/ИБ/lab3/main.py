# Взять два простых числа
p: int = 3823
q: int = 2269

# Выбрать экспоненту
e: int = 11

# Тестовое сообщение из Wikipedia
m: int = 111111

# Вычисление произведения
def n(p: int, q: int) -> int:
	return p * q

# Вычисление произведения функции Эйлера
def eiler(p: int, q: int) -> int:
	return (p - 1) * (q - 1)

#Вычисление секретной экспоненты
def secret_e(e: int, eiler: int) -> float:
	return (2 * eiler + 1) / e

#Публикация открытого ключа
def open_key(eiler: int, n: int) -> tuple[int, int]:
	return eiler, n

#Сохранение закрытого ключа
def close_key(secret_e: int, n: int) -> tuple[int, int]:
	return secret_e, n

def fast_pow(m, e, n):
	tmp, _m, _e, _n = 1, m, e, n
	while (_e != 0):
		if (_e % 2 == 1):
			tmp *= _m
		_e >>= 1  
		_m *= _m
		tmp %= _n
	return tmp

#def __open_key(a, b):
#	if not b:
#		return (1, 0, a)
#	y, x, g = __open_key(b, a % b)
#	return (x, y - (a // b) * x, g)

#Шифрование сообщения
def encrypted(m: int | bytes, e: int, n: int) -> int | list[int]:
	#if e <= 32:
	#	return (m ** e) % n
	
	if isinstance(m, bytes):
		_bytearray: list[bytes] = []
		for byte in m:
			_bytearray += [encrypted(byte, e, n)]
		
		return _bytearray

	#tmp: int = 1
	#for _ in range(e):
	#	tmp *= m
	#	tmp %= n
	
	return fast_pow(m, e, n)

#Расшифрование сообщения
def decrypted(m: int, secret_e: int, n: int) -> int | list[bytes]:
	#if secret_e <= 32:
	#	return (m ** secret_e) % n
	
	if isinstance(m, list) or isinstance(m, bytes):
		_bytearray: list[bytes] = []
		for byte in m:
			_bytearray += [decrypted(byte, secret_e, n)]
		
		return _bytearray
	
	#tmp: int = 1
	#for _ in range(secret_e):
	#	tmp *= m
	#	tmp %= n
	
	return fast_pow(m, secret_e, n)


def get_key(eiler: int, n: int) -> tuple[tuple[int, int], int]:
	e: int = 2
	while True:
		_secret_e: int = secret_e(e, eiler)
		_close_key: tuple[int, int] = close_key(_secret_e, n)
		if _close_key[0] == int(_close_key[0]):
			return (int(_close_key[0]), _close_key[1]), e

		e += 1
		
#def get_text() -> str:
#	return open('file.txt').read()

def get_text_byte() -> str:
	return open('file.txt', 'rb').read() 

#text: str = get_text()
text_byte: bytes = get_text_byte()

_n: int = n(p, q)
_eiler: int = eiler(p, q)
_secret_e: int = secret_e(e, _eiler)
_open_key: tuple[int, int] = open_key(e, _n)
_close_key, __open_key = get_key(_eiler, _n)
cipher_message: list[int | bytes] = encrypted(text_byte, *open_key(__open_key, _n))
open('cipher_text.txt', 'wb').write(bytes([_int % 256 for _int in cipher_message]))
originall_message: list[bytes] = decrypted(cipher_message, *_close_key)
open('originall_text.txt', 'wb').write(bytes(originall_message))


#print(
#	f"""
#	{text_byte=}

#	{p=}
#	{q=}
#	{e=}

#	{_n=}
#	{_eiler=}
#	{_secret_e=}

#	{_open_key=}
#	{_close_key=}
#	{__open_key}

#	{m=}
#	{cipher_message=}
#	{originall_message=}
#	"""
#)