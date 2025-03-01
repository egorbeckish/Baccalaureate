from utils import *

docx = Document('doc.docx')
tables = docx.tables
table = tables[0]

headers = [cell.text for cell in table.rows[0].cells]
data = [[cell.text for cell in row.cells] for row in table.rows[1:]]

print(
    tabulate(
        data, 
        headers=headers, 
        tablefmt="simple_grid", 
        showindex=False
    )
)