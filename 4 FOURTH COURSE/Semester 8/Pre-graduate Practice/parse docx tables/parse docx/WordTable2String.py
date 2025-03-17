from ParseWordTable import *


class WordTable2String:

    def __init__(self, path: str) -> None:
        self.__document: Document = self.__open_docx(path)
        self.__body = self.__document.element.body
        self.__tables: dict[str: ParseWordTable] = dict()
        self.__table_to_string

    
    @property
    def tables(self) -> list[str]:
        self.__table_to_string
        return self.__tables


    def __open_docx(self, path: str) -> Document:
        return Document(path)
    

    def __convert_oxml_text_to_string(self, oxml_text: docx.oxml.text.paragraph.CT_P) -> str:
        return docx.text.paragraph.Paragraph(oxml_text, self.__document).text.lower()


    def __convert_oxml_text_to_string_title(self, oxml_list: list[docx.oxml.text.paragraph.CT_P]) -> str:
        return '. '.join(map(lambda x: docx.text.paragraph.Paragraph(x, self.__document).text.lower(), oxml_list))

    
    def __convert_oxml_table_to_table(self, oxml_table: docx.oxml.table.CT_Tbl) -> docx.table.Table:
        return docx.table.Table(oxml_table, self.__document)


    @property
    def __table_to_string(self) -> None:
        index_title_table: int | None = None
        for index, element in enumerate(self.__body):
            if isinstance(element, docx.oxml.text.paragraph.CT_P):
                text: str = self.__convert_oxml_text_to_string(element)
                regex_text: list[str] = regex.findall(r'таблица\s[0-9]{1,}', text)
                if regex_text:
                    if text == regex_text[0]:
                        index_title_table: int = index
            
            if isinstance(element, docx.oxml.table.CT_Tbl):
                if index_title_table:
                    title: str = self.__convert_oxml_text_to_string_title(self.__body[index_title_table:index])
                    element: docx.table.Table = self.__convert_oxml_table_to_table(element)
                    self.__tables[title] = ParseWordTable(title, element)


    def __getitem__(self, index: int) -> str:
        return list(self.__tables.values())[index]