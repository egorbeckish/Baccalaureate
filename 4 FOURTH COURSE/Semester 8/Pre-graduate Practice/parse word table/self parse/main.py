from utils import *


# file = open_file('table.txt')
# table = get_table(file)

# columns = count_columns(table=table)
# rows = count_rows(table)

# # show_table(table)

# title, subtitles, values = layers(table)

# subtitles = correct_subtitles(subtitles)     
# show_layers_table(title, subtitles, values)

# join_subtitles(columns, subtitles)
# show_layers_table(title, subtitles, values)

# # _join_index = join_index(subtitles)
# # join_values(columns, _join_index, values)


docx = open_docx('table.docx')
tables = all_tables(docx)
table = get_table_docx(tables)

columns = count_columns(table)
rows = count_rows(table)

title, subtitles, values = layers_docx(table)

columns = count_columns(title=title)
rows = count_rows(table)

subtitles = correct_subtitles(subtitles)
# show_layers_table(title, subtitles, values)

join_subtitles2(columns, subtitles)

# join_subtitles(columns, subtitles)
# show_layers_table(title, subtitles, values)

# _join_index = join_index(subtitles)
# print(_join_index)