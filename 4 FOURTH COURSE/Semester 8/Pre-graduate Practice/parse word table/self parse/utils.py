from library import *


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


def open_docx(path: str) -> Document:
    return Document(path)


def get_tables(docx: Document) -> list:
    return docx.tables


def get_table_parse(tables: list) -> None:
    parse_table = []
    length_before = len(tables)
    for i in range(len(tables) - 1):
        current = layers(tables[i])
        _next = layers(tables[i + 1])
        index = find_gauss(current[1])

        if _next[0] in current[1]:
            current = list(current)
            current[1] += _next[1:][0]
            tables.pop(i + 1)

        # В итоговом варианте данную проверку убрать!!! (оставить только current[1].pop(index))
        if index:
            current[1].pop(index)
        parse_table += [current]
    
    length_after = len(tables)
    if length_after == length_before:
        parse_table += [layers(tables[-1])]

    return parse_table


def get_table(tables: list, index: int | slice=None) -> list:
    if index:
        return tables[index]

    return tables 


def find_gauss(data: list[list[str]]) -> None:
    for i, row in enumerate(data):
        row_isdigit: list[bool] = list(map(lambda x: x.isdigit(), row))
        if all(row_isdigit):
            length_row: int = len(row)
            if sum(map(int, row)) == (length_row * (length_row + 1)) / 2 and length_row == len(set(row)):
                return i
            
    

def layers(table: docx.table) -> tuple[list[str], list[list[str]]]:
    title: list[str] = [cell.text for cell in table.rows[0].cells]
    data: list[list[str]] = [[cell.text for cell in row.cells] for row in table.rows[1:]]

    return title, data


def show_table(title: list[str]=None, data: list[list[str]]=None, tables=None) -> None:
    if tables:
        for table in tables:
            show_table(table[0], table[1])
        
        return

    print(
        tabulate(
            data,
            headers=title,
            tablefmt="simple_grid", 
            showindex=False
        )
    )


def write_table_to_txt(table: tabulate) -> None:
    open('table.txt', 'a+', encoding='utf-8').write(table + '\n\n\n')