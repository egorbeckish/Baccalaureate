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


def format_rows(table, columns):
    for i, row in enumerate(table):
        table[i] = sep_values_rows(row)
    
    index_sep = index_sep_rows(table[0], columns)
    return f'{sep_begin_row(index_sep)}\n{f'{sep_rows(index_sep)}'.join(table)}\n{sep_last_row(index_sep)}'


def to_string(element):
    table = convert_Table_to_list(element)
    
    rows = get_rows(table)
    columns = get_columns(table)

    format_columns('', table, rows, columns)
    return format_rows(table, columns)


def get_body(document):
    return [element for element in document.element.body if isinstance(element, omxl_paragraph) or isinstance(element, omxl_table)]


def convert_omxl_paragraph_to_text(paragraph: omxl_paragraph, document: Document) -> str:
    return ' '.join(Paragraph(paragraph, document).text.lower().split())


def convert_list_omxl_paragraph_to_text(list_paragraph, document):
    return ' '.join(list(map(lambda x: convert_omxl_paragraph_to_text(x, document), list_paragraph)))


def convert_omxl_table_to_table(element: omxl_table, document: Document) -> Table:
    return Table(element, document)


def regex_title(text):
    return regex.findall(r'таблица\s[0-9]{1,}', text) != []


def match_elements(elements):
    return isinstance(elements[0], omxl_paragraph) and isinstance(elements[1], omxl_table)


def convert_text_to_oxml_paragraph(text: str) -> omxl_paragraph:
    tmp_document: Document = Document()
    paragraph = tmp_document.add_paragraph(text)
    return paragraph._element


def new_body(body, document):
    """
    ...
    """

    new_body = []
    index_title_table = None
    unic_index_title = []

    for index, element in enumerate(body):
        if isinstance(element, omxl_paragraph):
            text = convert_omxl_paragraph_to_text(element, document)
            if regex_title (text):
                index_title_table = index

        if isinstance(element, omxl_table):
            table = convert_omxl_table_to_table(element, document)
            table = convert_Table_to_list(table)


            if 'ТИПОВЫЕ' in table[0][0] or 'РЕГЛАМЕНТ' in table[0][0] or len(table) <= 3:
                continue

            if index_title_table:
                if index_title_table not in unic_index_title:
                    title = convert_list_omxl_paragraph_to_text(body[index_title_table:index], document)
                    title = convert_text_to_oxml_paragraph(title)
                    new_body += [title]

                unic_index_title += [index_title_table]

            new_body += [element]

    new_body = layers_table(new_body)
    return new_body


def layers_table(body):
    """
    ...
    """

    index_paragraphs = [i for i in range(len(body)) if isinstance(body[i], omxl_paragraph)]
    new_body = []
    for i in range(len(index_paragraphs) - 1):
        element = body[index_paragraphs[i] + 1:index_paragraphs[i + 1]]

        new_body += [body[index_paragraphs[i]]]
        if len(element) == 1:
            new_body += element

        else:
            new_body += [element]

    new_body += [body[index_paragraphs[-1]]]
    element = body[index_paragraphs[-1] + 1:]
    if len(element) == 1:
        new_body += element

    else:
        new_body += [element]

    return new_body


def main():
    # document = open_docx('test1_tables.docx')
    document = open_docx('pdf.docx')

    body = get_body(document)
    body = new_body(body, document)
    tables = get_tables(document)
    print(body)
    
    # count_table = -1
    # for i, element in enumerate(body):
    #     if isinstance(element, omxl_paragraph):
    #         if regex_title(convert_omxl_paragraph_to_text(element, document)):
    #             index = i
        
    #     else:
    #         count_table += 1
    #         try:
    #             print(convert_list_omxl_paragraph_to_text(body[index:i], document))
    #             print(to_string(tables[count_table]))
    #         except:
    #             continue


    