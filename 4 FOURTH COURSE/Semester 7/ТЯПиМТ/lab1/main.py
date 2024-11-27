import pandas as pd
import re

buffer = ''
container = set()

def func_transition(file_excel):
	__func_transition = pd.read_excel(
		io=file_excel, 
		index_col=0,
		dtype=str
	)

	return __func_transition

def header(func_transition):
	return re.compile(f'({')|('.join([str(column) for column in func_transition.columns])})')

def analyze_syntax(text, header, func_transition):
	q = 0 # состояние
	row = 1
	column = 0
	index = 0
	text += '\0'

	while True:
		symbol = text[index]
		print(f'Текущий символ: {symbol}')

		if symbol == '\n':
			column = 0
			row += 1
		
		print(f'Текущая строка: {text[index:]}')
		match = header.match(text, pos=index) # совпадение
		print(f'{match=}')

		if match:
			print(f'{match.groups()=}')
			symbol = match.group()
			print(f'Просмотр символа для перехода: {symbol}')
			shift = len(symbol)
			match = [i for i, val in enumerate(match.groups()) if val is not None][0]
			print(f'column: {func_transition.columns[match]}\tcolumns index: {match}')
			next_q = func_transition.iloc[int(q), int(match)] 
			print(f'Следующие состояние перехода: {next_q}\tТекущие состояние: {q}')
			if next_q == 'HALT':
				return True
			
			elif type(next_q) is str:
				if len(next_q.split()) == 2:
					q, check = map(int, next_q.split())
					repeat = check_var(check, symbol, row, column, text)
					if repeat:
						return repeat
				else:
					q = int(next_q)

				#q = int(next_q)
				index += shift
				column += shift
			
			else:
				return f'Ошибка компиляции\nrow={row}\tcolumn={column}\n{text[:-1].split('\n')[row - 1]}'
		
		else:
			return f'Ошибка компиляции\nrow={row}\tcolumn={column}\n{text[:-1].split('\n')[row - 1]}'
		
def check_var(check, symbol, row, column, text):
	global buffer, container

	if check == 1: # добавление символа к временному буферу
		buffer += symbol
	
	# конец считывания идентификатора и его проверка на совпадение 
	# с контейнером идентификаторов, буфер очищается
	elif check == 2:
		if buffer in container:
			return f'Ошибка компиляции\nrow={row}\tcolumn={column}\n{text[:-1].split('\n')[row - 1]}\n{buffer=}\n{container=}'

		container.add(buffer)
		buffer = ''

	print(f'{buffer=}\n{container=}')

#table_func_transition = func_transition('func_transition.xlsx')

#print(table_func_transition)

#__header = header(table_func_transition)

#print(__header)

#file = open('с++.txt').read()
#print(analyze_syntax(file, __header, table_func_transition))