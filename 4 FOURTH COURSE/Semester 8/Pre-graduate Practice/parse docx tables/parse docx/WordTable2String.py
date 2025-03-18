from ParseWordTable import *


class WordTable2String:

    def __init__(self, path: str) -> None:
        self.__flag_pdf: bool = False
        if regex.search('.pdf', path):
            self.__flag_pdf: bool = True
            parse(path, 'pdf.docx')

        self.__document: Document = self.__open_docx(path if not self.__flag_pdf else 'pdf.docx')
        self.__body = self.__new_body(self.__document.element.body)
        self.__tables: dict[str: ParseWordTable] = dict()
        self.__table_to_string


    @property
    def tables(self) -> list[str]:
        return self.__tables


    def __open_docx(self, path: str) -> Document:
        return Document(path)


    def __convert_oxml_text_to_string(self, oxml_text: CT_P) -> str:
        return docx.text.paragraph.Paragraph(oxml_text, self.__document).text.lower()


    def __convert_oxml_text_to_string_title(self, oxml_list: list[CT_P]) -> str:
        return '. '.join(map(lambda x: docx.text.paragraph.Paragraph(x, self.__document).text.lower(), oxml_list))


    def __convert_string_to_oxml(self, title: str) -> CT_P:
        tmp_doc: Document = Document()
        paragraph = tmp_doc.add_paragraph(title)
        return paragraph._element


    def __convert_oxml_table_to_table(self, oxml_table: CT_Tbl) -> docx.table.Table:
        return docx.table.Table(oxml_table, self.__document)


    def __delete_space(self, data: list[str]) -> None:
        while '' in data:
            data.pop(data.index(''))


    def __format_title(self, title: str) -> str:
        format_title: list[str] = regex.findall(r'таблица\s[0-9]{1,}\.', title)
        if format_title:
            return title

        tmp_title: str = regex.findall(r'таблица\s[0-9]{1,}', title)[0]
        tmp_text: str = regex.split(r'\s', regex.split(tmp_title, title)[-1])
        self.__delete_space(tmp_text)
        tmp_text: str = ' '.join(tmp_text)

        return tmp_title + '. ' + tmp_text


    def __gauss(self, table: list[list[str]]) -> bool:
        for i, row in enumerate(table):
            row_isdigit: list[bool] = map(lambda x: x.isdigit(), row)
            if all(row_isdigit):
                length_row: int = len(row)
                if sum(map(int, row)) == (length_row * (length_row + 1)) / 2 and length_row == len(set(row)):
                    return True
        return False


    def __new_body(self, body) -> list[docx.oxml]:

        new_body: list[docx.oxml] = []
        index_title_table: int | None = None
        unic_index_title: list[str] = []

        for index, element in enumerate(body):
            if isinstance(element, CT_P):
                text: str = self.__convert_oxml_text_to_string(element)
                regex_text: list[str] = regex.findall(r'таблица\s[0-9]{1,}', text)
                if regex_text:
                    index_title_table: int = index

            if isinstance(element, CT_Tbl):
                table = self.__convert_oxml_table_to_table(element)
                table: list[list[str]] = [[cell.text[::-1].replace(' ', '', 1)[::-1] for cell in row.cells] for row in table.rows]

                if 'ТИПОВЫЕ ТРЕБОВАНИЯ' in table[0][0] or len(table) <= 3:
                    continue

                if index_title_table:
                    if index_title_table not in unic_index_title:
                        title: str = self.__convert_oxml_text_to_string_title(body[index_title_table:index])
                        title: CT_P = self.__convert_string_to_oxml(title)
                        new_body += [title]

                    unic_index_title += [index_title_table]

                new_body += [element]

        new_body: list[CT_P | CT_Tbl | list[CT_Tbl]] = self.__layers_table(new_body)
        return new_body


    def __layers_table(self, body) -> list[CT_P | CT_Tbl | list[CT_Tbl]]:
        index_paragraphs = [i for i in range(len(body)) if isinstance(body[i], CT_P)]
        new_body: list[CT_P | CT_Tbl | list[CT_Tbl]] = []
        for i in range(len(index_paragraphs) - 1):
            element: list[CT_Tbl] = body[index_paragraphs[i] + 1:index_paragraphs[i + 1]]

            new_body += [body[index_paragraphs[i]]]
            if len(element) == 1:
                new_body += element

            else:
                new_body += [element]

        new_body += [body[index_paragraphs[-1]]]
        element: list[CT_Tbl] = body[index_paragraphs[-1] + 1:]
        if len(element) == 1:
            new_body += element

        else:
            new_body += [element]

        return new_body

    @property
    def __table_to_string(self) -> None:
        index_title_table: int | None = None
        for index, element in enumerate(self.__body):
            if isinstance(element, CT_P):
                text: str = self.__convert_oxml_text_to_string(element)
                # regex_text: list[str] = regex.findall(r'таблица\s[0-9]{1,}', text)
                # if regex_text:
                #     index_title_table: int = index

            if isinstance(element, CT_Tbl) or isinstance(element, list):
                title: str = self.__format_title(text)

                if isinstance(element, list):
                    for i, el in enumerate(element):
                        element[i]: docx.table.Table = self.__convert_oxml_table_to_table(el)
                else:
                    element: docx.table.Table = self.__convert_oxml_table_to_table(element)

                self.__tables[title] = ParseWordTable(title, element)

                # if index_title_table:
                #     title: str = self.__convert_oxml_text_to_string_title(self.__body[index_title_table:index])
                #     element: docx.table.Table = self.__convert_oxml_table_to_table(element)
                #     self.__tables[title] = ParseWordTable(title, element)


    def __getitem__(self, index: int) -> str:
        return list(self.__tables.values())[index]