from utils import *


class ParseWordTable:

    def __init__(self, title: str, obj_table: docx.table.Table | list[docx.table.Table]) -> None:
        self.__obj_table: docx.table.Table = obj_table
        self.__title: str = title
        self.__subtitles: list[list[str]] = self.__slice_obj_table[0]
        self.__table: list[list[str]] = self.__slice_obj_table[1]
        self.__fulltable: list[list[str]] = self.__subtitles + self.__table
        self.__rows: int = self.__table_rows
        self.__columns: int = self.__table_columns


    @property
    def title(self) -> str:
        return self.__title


    @property
    def subtitles(self) -> list[list[str]]:
        return self.__subtitles


    @property
    def table(self) -> list[list[str]]:
        return self.__table


    @property
    def fulltable(self) -> list[list[str]]:
        return self.__fulltable


    @property
    def rows(self) -> int:
        return self.__rows


    @property
    def columns(self) -> int:
        return self.__columns


    def __gauss(self, table: list[list[str]]) -> int:
        for i, row in enumerate(table):
            row_isdigit: list[bool] = map(lambda x: x.isdigit(), row)
            if all(row_isdigit):
                length_row: int = len(row)
                if sum(map(int, row)) == (length_row * (length_row + 1)) / 2 and length_row == len(set(row)):
                    return i
                    table.pop(i)
                    return


    def __delete_space(self, data: list[str]) -> None:
        while '' in data:
            data.pop(data.index(''))


    def __correct_data(self, table: list[list[str]]) -> None:
        table.pop(-1)

        for i, row in enumerate(table):
            row = list(map(lambda x: x.split(' '), row))
            for j in range(len(row)):
                self.__delete_space(row[j])
                row[j] = ' '.join(row[j])
            
            table[i] = row

    
    def __join_previously_row(self, table: list[list[str]], join_row: list[list[str]]) -> None:
        if join_row[0][0] == '':
            for i, el in enumerate(join_row[0]):
                if el:
                    table[-1][i] += join_row[0][i]

            join_row.pop(0)



    @property
    def __slice_obj_table(self) -> tuple[list[list[str]], list[list[str]]]:
        if isinstance(self.__obj_table, list):
            layers_table: list[list[list[str]]] = []
            
            for i, table in enumerate(self.__obj_table):
                data: list[list[str]] = ParseWordTable(self.__title, table).fulltable
                self.__correct_data(data)

                if not i:
                    layers_table += data

                else:
                    index: int = self.__gauss(data)
                    data: list[list[str]] = data[index + 1:]
                    self.__join_previously_row(layers_table, data)
                    layers_table += data
            
            index: int = self.__gauss(layers_table)
            return layers_table[:index], layers_table[index + 1:] if index else layers_table[:1], layers_table[1:]

        table: list[list[str]] = [[cell.text for cell in row.cells] for row in self.__obj_table.rows]
        index: int = self.__gauss(table)
        return table[:index], table[index + 1:] if index else table[:1], table[1:]


    @property
    def __table_rows(self) -> int:
        return len(self.__fulltable) + 1


    @property
    def __table_columns(self) -> int:
        return max(map(lambda x: len(x), self.__table))


    @property
    def to_string(self) -> str:
        tmp_table: str = tabulate(
            self.__fulltable,
            [self.__title],
            tablefmt="simple_grid",
            stralign='center',
            showindex=False,
        )

        right_edge: int = tmp_table.index('┐')
        tmp_title: str = ''.join(['╭', '─' * (right_edge - 1), '╮'])
        title: str = f"{tmp_title}\n{f'│{self.__title:^{right_edge - 1}}│'}"

        left_edge: int = tmp_table.index('├')
        table: str = tmp_table[left_edge:].replace('┼', '┬', self.__columns - 1)

        return f'{title}\n{table}'


    def __getitem__(self, index: int) -> str | list[str]:
        return self.__fulltable[index - 1] if index >= 1 \
                else self.__title if self.__rows == abs(index) or not index \
                else self.__fulltable[index]