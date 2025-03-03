from utils import *


docx: Document = open_docx('doc.docx')
tables = get_tables(docx)
table = get_table(tables, 3)
title, data = layers(table)
show_table(title, data)