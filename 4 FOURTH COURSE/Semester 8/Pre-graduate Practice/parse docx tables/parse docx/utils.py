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


    # intervals: list[list[int]] = [[] for _ in range(len(interval))]
    # for i, row in enumerate(interval):
    #     index_row: list[int] = []
    #     for j in range(len(row) - 1):
    #         current: int = row[j]
    #         _next: int = row[j + 1]

    #         if _next - current == 1:
    #             if not index_row:
    #                 index_row += [current]

    #         else:
    #             index_row += [current]
    #             intervals[i] += [index_row]
    #             index_row: list[int] = []

    #         if j + 1 == len(row) - 1:
    #             intervals[i] += [index_row + [row[j + 1]]]

    #     interval[i] = intervals[i]

    _interval: list[int] = []
    new_interval: list[list[int]] = []
    for i in range(len(interval) - 1):
        current = interval[i]
        _next = interval[i + 1]
        if _next - current == 1:
            if not _interval:
                _interval += [current]
        
        else:
            _interval += [current]
            new_interval += [_interval]
            _interval: list[int] = []
        
        if i + 1 == len(interval) - 1:
            new_interval += [_interval + [interval[i + 1]]]
    
    return new_interval


def open_docx(path: str) -> Document:
    return Document(path)


def get_tables(docx: Document) -> list:
    return get_correct_tables(docx.tables)


def delete_tables(tables: list[docx.table], index: list[int]) -> list[docx.table]:
    diff: int = None
    for i, del_index in enumerate(index):
        if len(del_index) == 2:
            del_index[1] += 1
            if not i:
                diff: int = del_index[1] - del_index[0]
                tables = tables[:del_index[0]] + tables[del_index[1]:]
            
            else:
                previously_index: list[int] = index[i - 1]
                if len(previously_index) == 1:
                    if not diff:
                        diff: int = del_index[1] - del_index[0]
                    else:
                        diff += 1

                del_index: list[int] = [x - diff for x in del_index]
                diff += del_index[1] - del_index[0]
                tables: list[docx.table] = tables[:del_index[0]] + tables[del_index[1]:]

        else:
            if not diff:
                if not i:
                    tables.pop(del_index[0])
                else:
                    diff: int = 1
                    tables.pop(del_index[0] - i)
            
            else:
                previously_index: list[int] = index[i - 1]
                if len(previously_index) == 2:
                    tables.pop(del_index[0] - diff)
                
                else:
                    tables.pop(del_index[0] - diff - 1)
                    diff += 1

    return tables


def get_correct_tables(tables: list) -> None:
    index_delete_table = []

    for i in range(len(tables)):
        title_current_table, data_current_table = layers(tables[i])
        new_table: list[docx.table] = [tables[i]]
        for j in range(i + 1, len(tables)):
            title_next_table, _ = layers(tables[j])

            if title_next_table not in [data_current_table[0], title_current_table]:
                break

            new_table += [tables[j]]
            index_delete_table += [j]

        if len(new_table) > 1:
            tables[i] = new_table
    
    index_delete_table = sorted(set(index_delete_table))
    return delete_tables(tables, get_intervals(index_delete_table))


def join_tables(tables: list[docx.table]) -> None:
    for i in range(len(tables)):
        if not i:
            title, data = layers(tables[i])
        else:
            data += layers(tables[i])[1]

    return title, data


def get_table(tables: list, index: int | slice=None) -> list:
    if index:
        return tables[index]

    return tables 


def find_gauss(data: list[list[str]]) -> int:
    for i, row in enumerate(data):
        row_isdigit: list[bool] = list(map(lambda x: x.isdigit(), row))
        if all(row_isdigit):
            length_row: int = len(row)
            if sum(map(int, row)) == (length_row * (length_row + 1)) / 2 and length_row == len(set(row)):
                return i
                data.pop(i)


def delete_gauss(data: list[list[str]]) -> None:
    index: int = find_gauss(data)
    if index == None:
        return
    
    match data.count(data[index]):
        case 1:
            data.pop(index)
        
        case _:
            value: list[str] = data[index]
            while value in data:
                index = data.index(value)
                data.pop(index)
                # if data.count(value) == 1:
                #     break


def layers(table: docx.table) -> tuple[list[str], list[list[str]]]:
    return [[cell.text for cell in row.cells] for row in table.rows]
    if isinstance(table, list):
        list_layers = []
        for _table in table:
            if not isinstance(_table, list):
                list_layers += [layers(_table)]
            else:
                list_layers += [join_tables(_table)]
        
        return list_layers

    title: list[str] = [cell.text for cell in table.rows[0].cells]
    data: list[list[str]] = [[cell.text for cell in row.cells] for row in table.rows[1:]]

    return title, data


def show_table(title: list[str]=None, data: list[list[str]]=None, tables=None) -> None:
    # return
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


def table_to_tabulate(title: list[str], data: list[list[str]]) -> tabulate:
    return tabulate(data, headers=title, tablefmt="simple_grid", showindex=False)


def write_table_to_txt(table: tabulate) -> None:
    open('table.txt', 'a+', encoding='utf-8').write(table + '\n\n\n')


def image_table(index: int) -> Image:
    return Image.open(fr'files/image/table{index + 1}.png')