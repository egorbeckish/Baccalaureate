import os


def clear_terminal() -> None:
	os.system('cls')
	print('\n\n')


def open_file(path: str) -> list:
	return open(path, encoding="utf-8").read().split("\n")


def get_table(table: list) -> list:
	return list(map(lambda x: x.split(), table))


def count_columns(title: list) -> int:
	return len(title[0])


def count_rows(table: list) -> int:
	return len(table)


def show_table(table: list) -> None:
	for row in table:
		print(row)

	print('\n\n')


def show_layers_table(title: list, subtitles: list, values: list) -> None:
	print(title)
	print('\n\n')
	show_table(subtitles)
	show_table(values)


def layers(table: list) -> tuple:
	"""
	Разделение данных таблицы на:
		- заголовок (основной, является первая строка)
		- подзаголовки (начинаются со следущей строки после заголовка)
		- данные (начинаются со следущей строки после подзаголовков)
	"""

	title: list = [value for value in table[0]]
	subtitles: list = []
	values: list = []

	for i, row in enumerate(table[1:]):
		format_subtitle: list = ['' if value in title else value for value in row]
		if '' in format_subtitle:
			subtitles += [format_subtitle]

		else:
			values += [format_subtitle]
		
	return title, subtitles, values


def get_intervals(index: list) -> None:
	interval = [[] for _ in range(len(index))]

	# for i, row in enumerate(index):
	# 	current: int = index[i][0]
	# 	_next: int = index[i][0]
	# 	row_index = []
	# 	for j in range(1, len(row)):
	# 		if index[i][j] == _next + 1:
	# 			_next: int = index[i][j]

	# 		else:
	# 			if current == _next:
	# 				row_index += [current]
	# 			else:
	# 				row_index += [current, _next]

	# 			current: int = index[i][j]
	# 			_next: int = index[i][j]

	# 	if current == _next:
	# 		row_index += [current]
	# 	else:
	# 		row_index += [current, _next]	

	# 	index[i] = row_index

	for i, row in enumerate(index):
		index_row: list = []
		for j in range(len(row) - 1):
			current: int = row[j]
			_next: int = row[j + 1]

			if _next - current == 1:
				if not index_row:
					index_row += [current]

			else:
				index_row += [current]
				interval[i] += index_row
				index_row: list = []

			if j + 1 == len(row) - 1:
				interval[i] += index_row + [row[j + 1]]

		index[i] = interval[i]


def join_indexs(subtitles: list) -> list:
	"""
	
	"""

	index = []
	for row in subtitles:
		row_index = []
		for i in range(len(row)):
			if row[i]:
				row_index += [i]

		index += [row_index]

	get_intervals(index)
	return index



clear_terminal()

file = open_file("table.txt")
table = get_table(file)

print('ТАБЛИЦА ИЗ WORD')
show_table(table)

title, subtitles, values = layers(table)

print('ТАБЛИЦА РАЗДЕЛЕННАЯ НА СЛОИ')
show_layers_table(title, subtitles, values)

join_indexs(subtitles)




"""
Номер Столбец1 Столбец2 Столбец3
Номер Столбец1 Подстолбец1 Подстолбец2 Столбец3
Номер Столбец1 Подстолбецподстолбца1.1 Подстолбецподстолбца1.2 Подстолбецподстолбца2.1 Подстолбецподстолбца2.2 Столбец3
1 1 2 3
2 5 6 7
3 9 10 11
"""