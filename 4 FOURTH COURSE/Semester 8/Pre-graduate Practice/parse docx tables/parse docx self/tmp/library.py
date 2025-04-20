import docx

from docx import Document
from docx.text.paragraph import Paragraph
from docx.table import Table

from docx.oxml.text.paragraph import CT_P as omxl_paragraph
from docx.oxml.table import CT_Tbl as omxl_table
from docx.oxml.section import CT_SectPr as omxl_section

import regex


from pdf2docx import Converter, parse