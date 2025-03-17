class WordTable2String:

    def __init__(self, path: str) -> None:
        self.__flag_pdf: bool = False
        if regex.search('.pdf', path):
            self.__flag_pdf: bool = True
            parse(path, 'doc.docx')

        self.__document: Document = self.__open_docx(path if not self.__flag_pdf else 'doc.docx')
        self.__body = self.__document.element.body if not self.__flag_pdf else self.__new_body(self.__document.element.body)
        self.__tables: dict[str: ParseWordTable] = dict()
        # self.__table_to_string

    
    @property
    def tables(self) -> list[str]:
        return self.__tables


    def __open_docx(self, path: str) -> Document:
        return Document(path)
    

    def __convert_oxml_text_to_string(self, oxml_text: docx.oxml.text.paragraph.CT_P) -> str:
        return docx.text.paragraph.Paragraph(oxml_text, self.__document).text.lower()


    def __convert_oxml_text_to_string_title(self, oxml_list: list[docx.oxml.text.paragraph.CT_P]) -> str:
        return '. '.join(map(lambda x: docx.text.paragraph.Paragraph(x, self.__document).text.lower(), oxml_list))

    
    def __convert_oxml_table_to_table(self, oxml_table: docx.oxml.table.CT_Tbl) -> docx.table.Table:
        return docx.table.Table(oxml_table, self.__document)


    def __gauss(self, table: list[list[str]]) -> bool:
        for i, row in enumerate(table):
            row_isdigit: list[bool] = map(lambda x: x.isdigit(), row)
            if all(row_isdigit):
                length_row: int = len(row)
                if sum(map(int, row)) == (length_row * (length_row + 1)) / 2 and length_row == len(set(row)):
                    return True
        return False
    

    def __new_body(self, _body) -> list:
        new_body: list = []
        for element in _body:
            if isinstance(element, docx.oxml.text.paragraph.CT_P):
                text: str = self.__convert_oxml_text_to_string(element)
                regex_text: list[str] = regex.findall(r'таблица\s[0-9]{1,}', text)
                if regex_text:
                    new_body += [element]
                    print(regex_text)

            if isinstance(element, docx.oxml.table.CT_Tbl):
                table = self.__convert_oxml_table_to_table(element)
                table: list[list[str]] = [[cell.text[::-1].replace(' ', '', 1)[::-1] for cell in row.cells] for row in table.rows]
                if len(table) <= 4:
                    continue
                
                print(table)
                if self.__gauss(table):
                    new_body += [element]
                    # print(table)
        
        return new_body


    @property
    def __table_to_string(self) -> None:
        index_title_table: int | None = None
        for index, element in enumerate(self.__body):
            if isinstance(element, docx.oxml.text.paragraph.CT_P):
                text: str = self.__convert_oxml_text_to_string(element)
                regex_text: list[str] = regex.findall(r'таблица\s[0-9]{1,}', text)
                if regex_text:
                    index_title_table: int = index
            
            if isinstance(element, docx.oxml.table.CT_Tbl):
                if index_title_table:
                    title: str = self.__convert_oxml_text_to_string_title(self.__body[index_title_table:index])
                    element: docx.table.Table = self.__convert_oxml_table_to_table(element)
                    self.__tables[title] = ParseWordTable(title, element)


    def __getitem__(self, index: int) -> str:
        return list(self.__tables.values())[index]


from pdf2docx import Converter

pdf_file = 'pdf.pdf'

cv = Converter(pdf_file)
tables = cv.extract_tables()
cv.close()

for table in tables:
    print(table)