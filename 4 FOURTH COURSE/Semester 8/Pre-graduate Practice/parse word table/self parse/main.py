from utils import *


docx: Document = open_docx('doc.docx')
tables = get_tables(docx)
show_parse_table(tables=tables)


for table in tables:
    title, data = table
    show_table(title, data)

# # table = get_table(tables, 3)
# # title, data = layers(table)
# # show_table(title, data)