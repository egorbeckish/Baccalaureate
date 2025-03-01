from library import *


def open_file(path: str) -> list[str]:
	return open(path, encoding="utf-8").read().split("\n")


def get_table(table: list) -> list[list[str]]:
	return list(map(lambda x: x.split(), table))


def count_columns(title: list[str]=None, table: list[list[str]]=None) -> int:
	return len(table[0]) if table else len(title)


def count_rows(table: list[list[str]]) -> int:
	return len(table)


def show_table(table: list[list[str]]) -> None:
	for row in table:
		print(row)

	print('\n\n')


def show_layers_table(title: list, subtitles: list[list[str]], values: list[list[str]]) -> None:
	print(title)
	print('\n')
	show_table(subtitles)
	show_table(values)
	

def layers(table: list[list[str]]) -> tuple[list[str] | list[list[str]]]:
	"""
	Разделение данных таблицы на:
		- заголовок (основной, является первая строка)
		- подзаголовки (начинаются со следущей строки после заголовка)
		- данные (начинаются со следущей строки после подзаголовков)

    :params table: Полноценная таблица полученная из docx
    :type table: list[list[str]]
    :return: Разделенная таблица на соот. слои
    :return type: tuple[list[str] | list[list[str]]]
	"""

	title: list[str] = [value for value in table[0]]
	subtitles: list[list[str]] = []
	values: list[list[str]] = []

	for i, row in enumerate(table[1:]):
		format_subtitle: list[str] = ['' if value in title else value for value in row]
		if '' in format_subtitle:
			subtitles += [format_subtitle]

		else:
			values += [format_subtitle]

	return title, subtitles, values
     

def unic_subtitles(subtitles: list[list[str]]) -> list[list[str]]:
    """
    Доопределение подзаголовков с учетом того, что у самого первого
    подзаголовка могут быть собственные подзаголовки.

    :params subtitles: Подзаголовки
    :type subtitles: list[list[str]]
    :return: Подзаголовки без повторов
    :return type: list[list[str]]
    """

    new_subtitles = [subtitles[0]]
    for i, subtitle in enumerate(subtitles[1:]):
        format_subtitle: list[str] = ['' if value in subtitles[i] else value for value in subtitle]
        new_subtitles += [format_subtitle]

    return new_subtitles
     

def get_intervals(interval: list[list[int]]) -> None:
    """
    Возвращает начало и конец интервалов.


    :params interval: Интервалы для каждой строки
    :type table: list[list[int]]
    :return: Корректные интервалы для каждой строки
    :return type: None

    >>> get_intervals(
        [
            [1, 2, 3, 4, 7, 8, 9, 10],
            [10, 11, 12, 13, 1, 2, 3, 4, 7, 9, 10, 11]
        ]
    )

    [
        [[1, 4], [7, 10]],
        [[10, 13], [1, 4], [7], [9, 11]]
    ]
    """

	# for i, row in enumerate(interval):
	# 	current: int = interval[i][0]
	# 	_next: int = interval[i][0]
	# 	row_index = []
	# 	for j in range(1, len(row)):
	# 		if index[i][j] == _next + 1:
	# 			_next: int = interval[i][j]

	# 		else:
	# 			if current == _next:
	# 				row_index += [current]
	# 			else:
	# 				row_index += [current, _next]

	# 			current: int = interval[i][j]
	# 			_next: int = interval[i][j]

	# 	if current == _next:
	# 		row_index += [current]
	# 	else:
	# 		row_index += [current, _next]

	# 	interval[i]: list = row_index


    intervals: list[list[int]] = [[] for _ in range(len(interval))]
    for i, row in enumerate(interval):
        index_row: list[int] = []
        for j in range(len(row) - 1):
            current: int = row[j]
            _next: int = row[j + 1]

            if _next - current == 1:
                if not index_row:
                    index_row += [current]

            else:
                index_row += [current]
                intervals[i] += [index_row]
                index_row: list[int] = []

            if j + 1 == len(row) - 1:
                intervals[i] += [index_row + [row[j + 1]]]

        interval[i] = intervals[i]
     

def join_index(subtitles: list[list[str]]) -> list[list[list[int]]]:
	"""
	Получаем индексы, какие подзаголовки и данные необходимо объединить, чтобы
    соответствовали кол-ву столбцам, т.к. главный заголовок определяет кол-во элементов в строке.
    По последней строке подзаголовка определяется объединение значений.

    :params subtitles: Подзаголовки
    :type subtitles: list[list[str]]
    :return: Индексы каждого подзаголовка и значений
    :return type: list[list[int]]
	"""

	index: list[list[int]] = []
	for row in subtitles:
		row_index: list[int] = []
		for i in range(len(row)):
			if row[i]:
				row_index += [i]

		index += [row_index]

	get_intervals(index)
	return index
     

def join_subtitles2(columns: int, subtitles: list[list[str]]) -> None:
    return "Данная функция не поддерживается"
    """
    Объединение по кол-ву столбцов всех подзаголовков.

    :params columns: Подзаголовки
    :type columns: int
    :params subtitles: Подзаголовки
    :type subtitles: list[list[str]]
    :return: Объединенные столбцы по их кол-ву из заголовка
    :return type: None
    """

    index: list[list[int]] = join_index(subtitles)

    for i, subtitle in enumerate(subtitles):
        new_subtitle: list[str] = [''] * columns
        for row_index in index[i]:
            row_index: list[int] = [row_index[0], row_index[1] + 1]
            _slice: slice = slice(*row_index)
            join_subtitle: str = '|'.join(subtitle[_slice])
            place = row_index[0] if row_index[0] < columns else (row_index[0] - 1 if row_index[0] == columns else columns - 1)
            # print(join_subtitle, place, _slice)
            new_subtitle[place] = join_subtitle
            print(new_subtitle)

        subtitles[i] = new_subtitle
    

def join_subtitles(subtitles: list[list[str]], index: list[list[int]]):
    """
    Объединение подзаголовков.

    :params columns: Подзаголовки
    :type columns: int
    :params subtitles: Подзаголовки
    :type subtitles: list[list[str]]
    :return: Объединенные подзаголовки
    :return type: None
    """

    for i, subtitle in enumerate(subtitles):
        new_subtitle: list[str] = [''] * index[i][0][0]
        for j, row_index in enumerate(index[i]):
            if j != len(index[i]) - 1:
                row_index: list[int] = [row_index[0], row_index[1] + 1]
                _slice: slice = slice(*row_index)
                join_subtitle: str = '|'.join(subtitle[_slice])
                diff: int = index[i][j + 1][0] - row_index[1] - 1
                new_subtitle += [join_subtitle, '' * diff]

        row_index: list[int] = [row_index[0], row_index[1] + 1]
        _slice: slice = slice(*row_index)
        join_subtitle: str = '|'.join(subtitle[_slice])
        new_subtitle += [join_subtitle]

        subtitles[i] = new_subtitle


def correct_subtitles2(subtitles):
    return "Данная функция не поддерживается"
    title_subtitle = [subtitles[0]]
    subtitles = subtitles[1:]

    for row in subtitles:
        for i, subtitle in enumerate(row):
            if subtitle:
                index = i
                break
        
        tmp = row[:index]
        row = row[index:]
        for i in range(len(title_subtitle[0])):
            if tmp[i] != title_subtitle[0][i]:
                index = i
                break
        
        row = title_subtitle[0][:index] + row
        title_subtitle += [row]
    
    return title_subtitle


def delete_space(row: list[str]) -> None:
    while '' in row:
        row.pop(row.index(''))


def correct_subtitles(subtitles: list[list[str]]) -> None:
    for row in subtitles[1:]:
        delete_space(row)
        for i in range(len(subtitles[0])):
            if not subtitles[0][i]:
                row.insert(i, '')
            

def join_values(index: list[list[int]], values: list[list[str]]) -> None:
    index: list[list[int]] = [index[0][0]] + index[-1]
    insert_index = []
    for _index in index:
        _index[1] += 1
        insert_index += list(range(*_index))

    for i, value in enumerate(values):
        new_value = [value[i] for i in range(len(value)) if i not in insert_index]
        for row_index in index:
            _slice: slice = slice(*row_index)
            _join_value = "|".join(value[_slice])
            new_value.insert(row_index[0], _join_value)

        values[i] = new_value
        

def open_docx(docx: str) -> Document:
    return Document(docx)
     

def all_tables(docx: Document) -> list:
    return docx.tables
     

def get_table_docx(tables: list) -> list[list[str]]:
    return [[cell.text for cell in row.cells] for row in tables[7].rows]


def unic_values(row):
    unic = []
    for value in row:
        if value not in unic:
            unic += [value]

    return unic
     

def layers_docx(table):
    title = unic_values(table[0])

    subtitles: list[list[str]] = []
    values: list[list[str]] = []
    for row in table[1:]:
        format_subtitle = unic_values(row)

        format_subtitle = ['' if value in title else value for value in format_subtitle]
        if '' in format_subtitle:
            subtitles += [format_subtitle]

        else:
            values += [format_subtitle]

    return title, subtitles, values