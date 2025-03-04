from utils import *


docx: Document = open_docx('doc.docx')
tables = get_tables(docx)
tables_parse = get_table_parse(tables)
show_table(tables=tables_parse)


# table = get_table(tables, 3)
# title, data = layers(table)
# show_table(title, data)