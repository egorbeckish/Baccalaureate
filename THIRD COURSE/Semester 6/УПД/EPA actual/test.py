from library import *

def print_function_name(decorated_function):
	def wrapper_function(*args, **kwargs):
		print('Print from {0}'.format(decorated_function.__name__))
		return decorated_function(*args, **kwargs)

	return wrapper_function

n = 1
def foo():
	global n
	n = 3
	return n + 1

print(foo())
for i in range(8):
	print(str(uuid.uuid4()))