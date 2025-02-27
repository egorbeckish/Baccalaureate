def open_file(path: str) -> list:
	return open(path, encoding="utf-8").read().split("\n")


def get_values(table: list) -> list:
	return list(map(lambda x: x.split(), table))


def count_columns(table: list) -> int:
	return len(table[0])


def count_rows(table: list) -> int:
	return len(table)


def get_maxim_length_columns(table: list, rows: int, columns: int) -> dict:
	maxim_lenght_columns = dict()

	for i in range(columns):
		maxim_lenght = 0
		for j in range(rows):
			maxim_lenght = max(maxim_lenght, len(values[j][i]))
			maxim_lenght_columns[f"столбец_{i + 1}"] = maxim_lenght

	return maxim_lenght_columns


def format_values_table(table: list, rows: int, columns: int, lenght_columns: dict) -> tuple:
	for i in range(columns):
		format_length = lenght_columns[f"столбец_{i + 1}"]
		format_length = format_length + 9 if format_length % 2 else format_length + 8
		for j in range(rows):
			table[j][i] = f"{table[j][i]:^{format_length}}"

	return table[0], table[1:]


def format_title(title: list) -> str:
	return f"|{'|'.join(title)}|"


def format_sep_title(title: list) -> str:
	return f"+{(len(format_title(title)) - 2) * '-'}+"


def format_values(title: list, values: list) -> str:
	return ("\n" + format_sep_title(title).replace('+', '-') + "\n").join(map(lambda x: format_title(x), values))


def format_table(title: list, values: list, format_sep: str) -> str:
	return f"{format_sep}\n{format_title(title)}\n{format_sep}\n{format_values(title, values)}\n{format_sep}"


table = open_file("table.txt")
values = get_values(table)
columns = count_columns(values)
rows = count_rows(values)

maxim_lenght_columns = get_maxim_length_columns(values, rows, columns)

title, values = format_values_table(values, rows, columns, maxim_lenght_columns)
format_string = format_sep_title(title)

print(format_table(title, values, format_string))