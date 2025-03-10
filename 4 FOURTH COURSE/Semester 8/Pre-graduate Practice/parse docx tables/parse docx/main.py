from utils import *


_docx: Document = open_docx('files/docx/doc.docx')

_body = _docx.element.body
index_text_table = None
for i, el in enumerate(_body):
    if isinstance(el, docx.oxml.text.paragraph.CT_P):
        text = docx.text.paragraph.Paragraph(el, _docx).text.lower()
        regex_text = regex.findall(r'таблиц[\w]\s[0-9]{1,}', text)
        if regex_text:
            if text == regex_text[0]:
                index_text_table = i

    if isinstance(el, docx.oxml.table.CT_Tbl):
        if index_text_table:

            title = join_text_table(_body[index_text_table:i], _docx)
            table = text_table(el, _docx)
            write_table_to_txt(table_to_tabulate(title, table))