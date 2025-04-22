from library import *


def open_docx(path):
	return Document(path)


def get_tables(document):
	return document.tables


def convert_Table_to_list(table):
	return [[' '.join(cell.text.split()) for cell in row.cells] for row in table.rows]


def get_rows(table):
	return len(table)


def get_columns(table):
	return len(table[0])


def show_table(table):
	for row in table:
		print(row)


def lenght_every_column(table, rows, columns):
	dict_lenght_columns = {}

	for i in range(columns):
		maxim_lenght = 0
		for j in range(rows):
			maxim_lenght = max(maxim_lenght, len(table[j][i]))

		dict_lenght_columns[f'столбец_{i}'] = maxim_lenght + 9 if maxim_lenght % 2 else maxim_lenght + 8

	return dict_lenght_columns


def add_space(dict_lenght_columns, title, columns):
	lenght_title = len(title)

	if sum(list(dict_lenght_columns.values())) + columns <= lenght_title:
		return lenght_title // columns

	return 0


def format_columns(title, table, rows, columns):
	dict_lenght_columns = lenght_every_column(table, rows, columns)
	space = add_space(dict_lenght_columns, title, columns)

	for i in range(columns):
		format_space = dict_lenght_columns[f'столбец_{i}'] + space
		for j in range(rows):
			table[j][i] = f'{table[j][i]:^{format_space}}'


def sep_values_rows(row):
	return f"│{'│'.join(row)}│"


def index_sep_rows(row, columns):
	index_sep = []
	count = 0

	while count != columns:
		index = row[1:].index('│')
		index_sep += [index + 1]
		row = row[index + 1:]
		count += 1

	return index_sep


def sep_rows(index_sep):
	return f"\n├{'┼'.join(list(map(lambda x: '─' * (x - 1), index_sep)))}┤\n"


def sep_begin_row(index_sep: list[int]) -> str:
	return f"├{'┬'.join(list(map(lambda x: '─' * (x - 1), index_sep)))}┤"


def sep_last_row(index_sep: list[int]) -> str:
	return f"└{'┴'.join(list(map(lambda x: '─' * (x - 1), index_sep)))}┘"


def sep_title(title, lenght):
	return f"╭{lenght * '─'}╮\n│{title:^{lenght}}│"


def format_rows(title, table, columns):
	for i, row in enumerate(table):
		table[i] = sep_values_rows(row)

	index_sep = index_sep_rows(table[0], columns)
	return f"{sep_title(title, len(table[0]) - 2)}\n{sep_begin_row(index_sep)}\n{f'{sep_rows(index_sep)}'.join(table)}\n{sep_last_row(index_sep)}"


def to_string(title, element):
	table = convert_Table_to_list(element)

	rows = get_rows(table)
	columns = get_columns(table)

	format_columns(title, table, rows, columns)
	return format_rows(title, table, columns)


def get_body(document):
	return [element for element in document.element.body if isinstance(element, omxl_paragraph) or isinstance(element, omxl_table)]


def correct_body(body, document):
	_body = []
	for i, element in enumerate(body):
		if isinstance(element, omxl_paragraph):
			text = convert_omxl_paragraph_to_text(element, document)
			if text != '':
				_body += [element]
				if regex_title(text):
					index_title = i
					
		else:
			try:
				if index_title:
					_body += [element]

			except:
				continue

	return _body


def convert_omxl_paragraph_to_text(paragraph: omxl_paragraph, document: Document) -> str:
	return ' '.join(Paragraph(paragraph, document).text.lower().split())


def convert_list_omxl_paragraph_to_text(list_paragraph, document):
	return ' '.join(list(map(lambda x: convert_omxl_paragraph_to_text(x, document), list_paragraph)))


def convert_omxl_table_to_table(element: omxl_table, document: Document) -> Table:
	return Table(element, document)


def regex_title(text):
	return regex.findall(r'таблица\s[0-9]{1,}', text) != []


def convert_text_to_oxml_paragraph(text: str) -> omxl_paragraph:
	return Document().add_paragraph(text)._element
	tmp_document: Document = Document()
	paragraph = tmp_document.add_paragraph(text)
	return paragraph._element


def merge(body, document):
	merge_text = ''
	index_title = None
	
	for i, element in enumerate(body):
		if isinstance(element, omxl_paragraph):
			text = convert_omxl_paragraph_to_text(element, document)
			if regex_title(text):
				index_title = i

			if not index_title:
				merge_text += f"{text}\n\n"

		else:
			title = convert_list_omxl_paragraph_to_text(body[index_title:i], document)
			table = convert_omxl_table_to_table(element, document)
			merge_text += f"{to_string(title, table)}\n"
			index_title = None
	
	return merge_text


def main():
	document = open_docx('test1_tables.docx')
	# document = open_docx('pdf.docx')
	body = get_body(document)
	body = correct_body(body, document)

	print(merge(body, document))
