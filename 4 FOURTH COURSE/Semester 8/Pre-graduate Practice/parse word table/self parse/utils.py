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


def write_table(table):
    open('table.txt', 'a+', encoding='utf-8').write(table + '\n\n')