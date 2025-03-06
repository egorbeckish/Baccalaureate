from utils import *


docx: Document = open_docx('files/docx/doc.docx')
tables = get_tables(docx)
tables = layers(tables)
for table in tables:
    write_table_to_txt(table_to_tabulate(*table))