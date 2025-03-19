import docx
from docx import Document
from docx.oxml.text.paragraph import CT_P
from docx.oxml.table import CT_Tbl

from tabulate import tabulate

import os

import regex

from pdf2docx import Converter, parse