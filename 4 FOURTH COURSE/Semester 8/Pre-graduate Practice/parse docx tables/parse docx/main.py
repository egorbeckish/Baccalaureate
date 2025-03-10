import docx.oxml
import docx.table
from utils import *


_docx: Document = open_docx('files/docx/doc.docx')

_body = _docx.element.body
text_table = None
for i, el in enumerate(_body):
    if isinstance(el, docx.oxml.text.paragraph.CT_P):
        text = docx.text.paragraph.Paragraph(el, _docx).text.lower()
        regex_text = regex.findall(r'таблиц[\w]\s[0-9]{1,}', text)
        if regex_text:
            if text == regex_text[0]:
                text_table = i

    if isinstance(el, docx.oxml.table.CT_Tbl):
        if text_table:
            text = _body[text_table:i]
            for j, _text in enumerate(text):
                text[j] = docx.text.paragraph.Paragraph(_text, _docx).text.lower()
            
            text = '. '.join(text)
            table = layers(docx.table.Table(el, _docx))
            write_table_to_txt(table_to_tabulate([text], table))



# tables = get_tables(docx)
# tables = layers(tables)
# for table in tables:
#     write_table_to_txt(table_to_tabulate(*table))