from utils import *


docx: Document = open_docx('files/docx/doc.docx')
tables = get_tables(docx)
get_correct_tables(tables)


# table = get_table(tables, 3)
# title, data = layers(table)
# show_table(title, data)