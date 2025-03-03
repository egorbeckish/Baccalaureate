from utils import *


docx: Document = Document('doc.docx')
tables: list = docx.tables
# print(tables)
table = tables[3]

headers: list[str] = [cell.text for cell in table.rows[0].cells]
data: list[str] = [[cell.text for cell in row.cells] for row in table.rows[1:]]
data: list[str] = data[1:] if data.count(data[0]) > 1 else data

# print(
#     tabulate(
#         data, 
#         headers=headers, 
#         tablefmt="simple_grid", 
#         showindex=False
#     )
# )

# write_table(
#     tabulate(
#         data, 
#         headers=headers, 
#         tablefmt="simple_grid", 
#         showindex=False
#     ) + '\n\n'
# )