from docx import Document

document = open('Poyasnitelnaya_zapiska_Pleschev_Danil_021-1.docx', 'rb')
document = Document(document)

import docx.document
import docx.oxml.table
import docx.oxml.text.paragraph
import docx.table
import docx.text.paragraph

def iter_items(paragraphs):
    for paragraph in document.paragraphs:
        if paragraph.style.name.startswith('Agt'):
            yield paragraph
        if paragraph.style.name.startswith('TOC'):
            yield paragraph
        if paragraph.style.name.startswith('Heading'):
            yield paragraph
        if paragraph.style.name.startswith('Title'):
            yield paragraph
        if paragraph.style.name.startswith('Heading'):
            yield paragraph
        if paragraph.style.name.startswith('Table Normal'):
            yield paragraph
        if paragraph.style.name.startswith('List'):
            yield paragraph
for item in iter_items(document.paragraphs):
    print(item.text)


def iter_paragraphs(parent, recursive=True):
    """
    Yield each paragraph and table child within *parent*, in document order.
    Each returned value is an instance of Paragraph. *parent*
    would most commonly be a reference to a main Document object, but
    also works for a _Cell object, which itself can contain paragraphs and tables.
    """
    if isinstance(parent, docx.document.Document):
        parent_elm = parent.element.body
    elif isinstance(parent, docx.table._Cell):
        parent_elm = parent._tc
    else:
        raise TypeError(repr(type(parent)))
    for child in parent_elm.iterchildren():
        if isinstance(child, docx.oxml.text.paragraph.CT_P):
            yield docx.text.paragraph.Paragraph(child, parent)
        elif isinstance(child, docx.oxml.table.CT_Tbl):
            if recursive:
                table = docx.table.Table(child, parent)
                for row in table.rows:
                    for cell in row.cells:
                        for child_paragraph in iter_paragraphs(cell):
                            yield child_paragraph

for paragraph in iter_paragraphs(document):
    print(paragraph.text)


# for i in range(len(document.paragraphs)):
# 	# print(i)
	
# 	if len(document.paragraphs[i].runs) > 0:
		
# 		for j in range(len(document.paragraphs[i].runs)):
			
# 			# print(i.runs[j].text == 'Таблица 1.1 – Функции меломана ')
			
# 			if document.paragraphs[i].runs[j].text == 'Таблица 1.1 – Функции меломана ':
# 				print(document.paragraphs[i].runs[j].text)

# 	# print('\n\n')

# table_text = ''
# for k in range(len(document.tables[0].rows)):
# 	for l in range(len(document.tables[0].rows[k].cells)):
# 		table_text += f'{document.tables[0].rows[k].cells[l].text:^60}'
# 	table_text += '\n'

# print(table_text)


from docx2python import docx2python




import docx.package
import docx.parts.document
import docx.parts.numbering
package = docx.package.Package.open("Poyasnitelnaya_zapiska_Pleschev_Danil_021-1.docx")
main_document_part = package.main_document_part
assert isinstance(main_document_part, docx.parts.document.DocumentPart)
numbering_part = main_document_part.numbering_part
assert isinstance(numbering_part, docx.parts.numbering.NumberingPart)
ct_numbering = numbering_part._element
print(ct_numbering)  # CT_Numbering
for num in ct_numbering.num_lst:
    print(num)  # CT_Num
    print(num.abstractNumId)  # CT_DecimalNumber



import sys
import docx
from docx2python import docx2python as dx2py
def ns_tag_name(node, name):
    if node.nsmap and node.prefix:
        return "{{{:s}}}{:s}".format(node.nsmap[node.prefix], name)
    return name
def descendants(node, desc_strs):
    if node is None:
        return []
    if not desc_strs:
        return [node]
    ret = {}
    for child_str in desc_strs[0]:
        for child in node.iterchildren(ns_tag_name(node, child_str)):
            descs = descendants(child, desc_strs[1:])
            if not descs:
                continue
            cd = ret.setdefault(child_str, [])
            if isinstance(descs, list):
                cd.extend(descs)
            else:
                cd.append(descs)
    return ret
def simplified_descendants(desc_dict):
    ret = []
    for vs in desc_dict.values():
        for v in vs:
            if isinstance(v, dict):
                ret.extend(simplified_descendants(v))
            else:
                ret.append(v)
    return ret
def process_list_data(attrs, dx2py_elem):
    #print(simplified_descendants(attrs))
    desc = simplified_descendants(attrs)[0]
    level = int(desc.attrib[ns_tag_name(desc, "val")])
    elem = [i for i in dx2py_elem[0].split("\t") if i][0]#.rstrip(")")
    return "    " * level + elem + " "
def main(*argv):
    fname = r"./Poyasnitelnaya_zapiska_Pleschev_Danil_021-1.docx"
    docd = docx.Document(fname)
    docdpy = dx2py(fname)
    dr = docdpy.docx_reader
    #print(dr.files)  # !!! Check word/numbering.xml !!!
    docdpy_runs = docdpy.document_runs[0][0][0]
    if len(docd.paragraphs) != len(docdpy_runs):
        print("Lengths don't match. Abort")
        return -1
    subnode_tags = (("pPr",), ("numPr",), ("ilvl",))  # (("pPr",), ("numPr",), ("ilvl", "numId"))  # numId is for matching elements from word/numbering.xml
    for idx, (par, l) in enumerate(zip(docd.paragraphs, docdpy_runs)):
        #print(par.text, l)
        numbered_attrs = descendants(par._element, subnode_tags)
        #print(numbered_attrs)
        if numbered_attrs:
            print(process_list_data(numbered_attrs, l) + par.text)
        else:
            print(par.text)
if __name__ == "__main__":
    print("Python {:s} {:03d}bit on {:s}\n".format(" ".join(elem.strip() for elem in sys.version.split("\n")),
                                                   64 if sys.maxsize > 0x100000000 else 32, sys.platform))
    rc = main(*sys.argv[1:])
    print("\nDone.")
    sys.exit(rc)



from docx.api import Document
# Load the first table from your document. In your example file,
# there is only one table, so I just grab the first one.
document = Document('Poyasnitelnaya_zapiska_Pleschev_Danil_021-1.docx')
table = document.tables[0]
# Data will be a list of rows represented as dictionaries
# containing each row's data.
data = []
keys = None
for i, row in enumerate(table.rows):
    text = (cell.text for cell in row.cells)
    # Establish the mapping based on the first row
    # headers; these will become the keys of our dictionary
    if i == 0:
        keys = tuple(text)
        continue
    # Construct a dictionary for this row, mapping
    # keys to values for this row
    row_data = dict(zip(keys, text))
    data.append(row_data)

print(data)


from docx import Document
doc = Document("Poyasnitelnaya_zapiska_Pleschev_Danil_021-1.docx")
#Reading the tables in the particular docx
i = 0
for t in doc.tables:
    for ro in t.rows:
        if ro.cells[0].text=="ID" :
            i=i+1
print("Total Number of Tables: ", i)
#Counting the values of Automation
 # This will count how many yes automation
j=0
for table in doc.tables:
    for ro in table.rows:
        if ro.cells[0].text=="Automated Test Case" and (ro.cells[2].text=="yes" or ro.cells[2].text=="Yes"):
            j=j+1
print("Total Number of YES Automations: ", j)
#This part is used to count the No automation values
k = 0
for t in doc.tables:
    for ro in t.rows:
        if ro.cells[0].text=="Automated Test Case" and (ro.cells[2].text=="no" or ro.cells[2].text=="No"):
            k=k+1
print("Total Number of NO Automations: ", k)




from docx import Document
from docx.document import Document as _Document
from docx.oxml.text.paragraph import CT_P
from docx.oxml.table import CT_Tbl
from docx.table import _Cell, Table
from docx.text.paragraph import Paragraph
def iter_block_items(parent):
    """
    Generate a reference to each paragraph and table child within *parent*,
    in document order. Each returned value is an instance of either Table or
    Paragraph. *parent* would most commonly be a reference to a main
    Document object, but also works for a _Cell object, which itself can
    contain paragraphs and tables.
    """
    if isinstance(parent, _Document):
        parent_elm = parent.element.body
        # print(parent_elm.xml)
    elif isinstance(parent, _Cell):
        parent_elm = parent._tc
    else:
        raise ValueError("something's not right")
    for child in parent_elm.iterchildren():
        if isinstance(child, CT_P):
            yield Paragraph(child, parent)
        elif isinstance(child, CT_Tbl):
            yield Table(child, parent)
"""
Reading the document.
"""
document = Document('Poyasnitelnaya_zapiska_Pleschev_Danil_021-1.docx')
for block in iter_block_items(document):
    print('found one instance')
    if isinstance(block, Paragraph):
        print("paragraph")
        #write the code here
    else:
        print("table")
        #write the code here



start_copy = False
for block in iter_block_items(document):
    if isinstance(block, Paragraph):
        if block.text == "TEXT FROM WHERE WE STOP COPYING":
            break
    if start_copy:
        if isinstance(block, Paragraph):
            last_paragraph = insert_paragraph_after(last_paragraph,block.text)
        elif isinstance(block, Table):
            paragraphs_with_table.append(last_paragraph)
            tables_to_apppend.append(block._tbl)
    if isinstance(block, Paragraph):
        if block.text == "TEXT FROM WHERE WE START COPYING":
            start_copy = True


from docx import Document
from docx.document import Document as _Document
from docx.oxml.text.paragraph import CT_P
from docx.oxml.table import CT_Tbl
from docx.table import _Cell, Table
from docx.text.paragraph import Paragraph
def iter_block_items(parent):
    """
    Generate a reference to each paragraph and table child within *parent*,
    in document order. Each returned value is an instance of either Table or
    Paragraph. *parent* would most commonly be a reference to a main
    Document object, but also works for a _Cell object, which itself can
    contain paragraphs and tables.
    """
    if isinstance(parent, _Document):
        parent_elm = parent.element.body
    elif isinstance(parent, _Cell):
        parent_elm = parent._tc
    elif isinstance(parent, _Row):
        parent_elm = parent._tr
    else:
        raise ValueError("something's not right")
    for child in parent_elm.iterchildren():
        if isinstance(child, CT_P):
            yield Paragraph(child, parent)
        elif isinstance(child, CT_Tbl):
            yield Table(child, parent)
document = Document('Poyasnitelnaya_zapiska_Pleschev_Danil_021-1.docx')
for block in iter_block_items(document):
    #print(block.text if isinstance(block, Paragraph) else '')
    if isinstance(block, Paragraph):
        print(block.text)
    elif isinstance(block, Table):
        for row in block.rows:
            row_data = []
            for cell in row.cells:
                for paragraph in cell.paragraphs:
                    row_data.append(paragraph.text)
            print("\t".join(row_data))


def printTables(doc):
    for table in doc.tables:
        for row in table.rows:
            for cell in row.cells:
                for paragraph in cell.paragraphs:
                    print(paragraph.text)
                printTables(cell)




def iter_block_items(parent):
    # https://github.com/python-openxml/python-docx/issues/40
    from docx.document import Document
    from docx.oxml.table import CT_Tbl
    from docx.oxml.text.paragraph import CT_P
    from docx.table import _Cell, Table
    from docx.text.paragraph import Paragraph
    """
    Yield each paragraph and table child within *parent*, in document order.
    Each returned value is an instance of either Table or Paragraph. *parent*
    would most commonly be a reference to a main Document object, but
    also works for a _Cell object, which itself can contain paragraphs and tables.
    """
    if isinstance(parent, Document):
        parent_elm = parent.element.body
    elif isinstance(parent, _Cell):
        parent_elm = parent._tc
    else:
        raise ValueError("something's not right")
    # print('parent_elm: '+str(type(parent_elm)))
    for child in parent_elm.iterchildren():
        if isinstance(child, CT_P):
            yield Paragraph(child, parent)
        elif isinstance(child, CT_Tbl):
            yield Table(child, parent)  # No recursion, return tables as tables
        # table = Table(child, parent)  # Use recursion to return tables as paragraphs       
        # for row in table.rows:
        #     for cell in row.cells:
        #         yield from iter_block_items(cell)    


document = Document("Poyasnitelnaya_zapiska_Pleschev_Danil_021-1.docx")
for iter_block_item in iter_block_items(document): # Iterate over paragraphs and tables
# print('iter_block_item type: '+str(type(iter_block_item)))
	if isinstance(iter_block_item, Paragraph):
		paragraph = iter_block_item  # Do some logic here
	else:
		table = iter_block_item      # Do some logic here







from docx import Document
from docx.shared import Inches
document = Document("Poyasnitelnaya_zapiska_Pleschev_Danil_021-1.docx")
headings = []
texts = []
for paragraph in document.paragraphs:
    if paragraph.style.name == "Heading 2":
        headings.append(paragraph.text)
    elif paragraph.style.name == "Normal":
        texts.append(paragraph.text)
for h, t in zip(headings, texts):
    print(h, t)



from docx import Document
from docx.shared import Inches
document = Document("Poyasnitelnaya_zapiska_Pleschev_Danil_021-1.docx")
headings = []
texts = []
para = []
for paragraph in document.paragraphs:
    if paragraph.style.name.startswith("Heading"):
        if headings:
            texts.append(para)
        headings.append(paragraph.text)
        para = []
    elif paragraph.style.name == "Normal":
        para.append(paragraph.text)
if para or len(headings)>len(texts):
    texts.append(texts.append(para))
for h, t in zip(headings, texts):
    print(h, t)


from docx.opc.constants import RELATIONSHIP_TYPE as RT
from docx import *
from docx.text.paragraph import Paragraph
from docx.text.paragraph import Run
import xml.etree.ElementTree as ET
from docx.document import Document as doctwo
from docx.oxml.table import CT_Tbl
from docx.oxml.text.paragraph import CT_P
from docx.table import _Cell, Table
from docx.text.paragraph import Paragraph
from docx.shared import Pt
# from docxcompose.composer import Composer
from docx import Document as Document_compose
import pandas as pd
from xml.etree import ElementTree
from io import StringIO
import io
import csv
import base64
#Load the docx file into document object. You can input your own docx file in this step by changing the input path below:
document = Document("Poyasnitelnaya_zapiska_Pleschev_Danil_021-1.docx")
##This function extracts the tables and paragraphs from the document object
def iter_block_items(parent):
    """
    Yield each paragraph and table child within *parent*, in document order.
    Each returned value is an instance of either Table or Paragraph. *parent*
    would most commonly be a reference to a main Document object, but
    also works for a _Cell object, which itself can contain paragraphs and tables.
    """
    if isinstance(parent, doctwo):
        parent_elm = parent.element.body
    elif isinstance(parent, _Cell):
        parent_elm = parent._tc
    else:
        raise ValueError("something's not right")
    for child in parent_elm.iterchildren():
        if isinstance(child, CT_P):
            yield Paragraph(child, parent)
        elif isinstance(child, CT_Tbl):
            yield Table(child, parent)
#This function extracts the table from the document object as a dataframe
def read_docx_tables(tab_id=None, **kwargs):
    """
    parse table(s) from a Word Document (.docx) into Pandas DataFrame(s)
    Parameters:
        filename:   file name of a Word Document
        tab_id:     parse a single table with the index: [tab_id] (counting from 0).
                    When [None] - return a list of DataFrames (parse all tables)
        kwargs:     arguments to pass to `pd.read_csv()` function
    Return: a single DataFrame if tab_id != None or a list of DataFrames otherwise
    """
    def read_docx_tab(tab, **kwargs):
        vf = io.StringIO()
        writer = csv.writer(vf)
        for row in tab.rows:
            writer.writerow(cell.text for cell in row.cells)
        vf.seek(0)
        return pd.read_csv(vf, **kwargs)
#    doc = Document(filename)
    if tab_id is None:
        return [read_docx_tab(tab, **kwargs) for tab in document.tables]
    else:
        try:
            return read_docx_tab(document.tables[tab_id], **kwargs)
        except IndexError:
            print('Error: specified [tab_id]: {}  does not exist.'.format(tab_id))
            raise
#The combined_df dataframe will store all the content in document order including images, tables and paragraphs.
#If the content is an image or a table, it has to be referenced from image_df for images and table_list for tables using the corresponding image or table id that is stored in combined_df
#And if the content is paragraph, the paragraph text will be stored in combined_df
combined_df = pd.DataFrame(columns=['para_text','table_id','style'])
table_mod = pd.DataFrame(columns=['string_value','table_id'])
#The image_df will consist of base64 encoded image data of all the images in the document
image_df = pd.DataFrame(columns=['image_index','image_rID','image_filename','image_base64_string'])
#The table_list is a list consisting of all the tables in the document
table_list=[]
xml_list=[]
i=0
imagecounter = 0
blockxmlstring = ''
for block in iter_block_items(document):
    if 'text' in str(block):
        isappend = False
        runboldtext = ''
        for run in block.runs:                        
            if run.bold:
                runboldtext = runboldtext + run.text
        style = str(block.style.name)
        appendtxt = str(block.text)
        appendtxt = appendtxt.replace("\n","")
        appendtxt = appendtxt.replace("\r","")
        tabid = 'Novalue'
        paragraph_split = appendtxt.lower().split()                
        isappend = True
        for run in block.runs:
            xmlstr = str(run.element.xml)
            my_namespaces = dict([node for _, node in ElementTree.iterparse(StringIO(xmlstr), events=['start-ns'])])
            root = ET.fromstring(xmlstr) 
            #Check if pic is there in the xml of the element. If yes, then extract the image data
            if 'pic:pic' in xmlstr:
                xml_list.append(xmlstr)
                for pic in root.findall('.//pic:pic', my_namespaces):
                    cNvPr_elem = pic.find("pic:nvPicPr/pic:cNvPr", my_namespaces)
                    name_attr = cNvPr_elem.get("name")
                    blip_elem = pic.find("pic:blipFill/a:blip", my_namespaces)
                    embed_attr = blip_elem.get("{http://schemas.openxmlformats.org/officeDocument/2006/relationships}embed")
                    isappend = True
                    appendtxt = str('Document_Imagefile/' + name_attr + '/' + embed_attr + '/' + str(imagecounter))
                    document_part = document.part
                    image_part = document_part.related_parts[embed_attr]
                    image_base64 = base64.b64encode(image_part._blob)
                    image_base64 = image_base64.decode()                            
                    dftemp = pd.DataFrame({'image_index':[imagecounter],'image_rID':[embed_attr],'image_filename':[name_attr],'image_base64_string':[image_base64]})
                    # image_df = image_df.append(dftemp,sort=False)
                    style = 'Novalue'
                imagecounter = imagecounter + 1
    elif 'table' in str(block):
        isappend = True
        style = 'Novalue'
        appendtxt = str(block)
        tabid = i
        dfs = read_docx_tables(tab_id=i)
        dftemp = pd.DataFrame({'para_text':[appendtxt],'table_id':[i],'style':[style]})
        # table_mod = table_mod.append(dftemp,sort=False)
        table_list.append(dfs)
        i=i+1
    if isappend:
            dftemp = pd.DataFrame({'para_text':[appendtxt],'table_id':[tabid],'style':[style]})
            # combined_df=combined_df.append(dftemp,sort=False)
combined_df = combined_df.reset_index(drop=True)
image_df = image_df.reset_index(drop=True)


from __future__ import (
    absolute_import, division, print_function, unicode_literals
)
from docx import Document
from docx.document import Document as _Document
from docx.oxml.text.paragraph import CT_P
from docx.oxml.table import CT_Tbl
from docx.table import _Cell, Table
from docx.text.paragraph import Paragraph
def iter_block_items(parent):
    """
    Generate a reference to each paragraph and table child within *parent*,
    in document order. Each returned value is an instance of either Table or
    Paragraph. *parent* would most commonly be a reference to a main
    Document object, but also works for a _Cell object, which itself can
    contain paragraphs and tables.
    """
    if isinstance(parent, _Document):
        parent_elm = parent.element.body
        # print(parent_elm.xml)
    elif isinstance(parent, _Cell):
        parent_elm = parent._tc
    else:
        raise ValueError("something's not right")
    for child in parent_elm.iterchildren():
        if isinstance(child, CT_P):
            yield Paragraph(child, parent)
        elif isinstance(child, CT_Tbl):
            yield Table(child, parent)
document = Document("Poyasnitelnaya_zapiska_Pleschev_Danil_021-1.docx")
for block in iter_block_items(document):
    print('found one')
    print(block.text if isinstance(block, Paragraph) else '')




from docx import Document
from docx.document import Document as _Document
from docx.oxml.text.paragraph import CT_P
from docx.oxml.table import CT_Tbl
from docx.table import _Cell, Table
from docx.text.paragraph import Paragraph
def iter_block_items(parent):
    """
    Generate a reference to each paragraph and table child within *parent*,
    in document order. Each returned value is an instance of either Table or
    Paragraph. *parent* would most commonly be a reference to a main
    Document object, but also works for a _Cell object, which itself can
    contain paragraphs and tables.
    """
    if isinstance(parent, _Document):
        parent_elm = parent.element.body
    elif isinstance(parent, _Cell):
        parent_elm = parent._tc
    elif isinstance(parent, _Row):
        parent_elm = parent._tr
    else:
        raise ValueError("something's not right")
    for child in parent_elm.iterchildren():
        if isinstance(child, CT_P):
            yield Paragraph(child, parent)
        elif isinstance(child, CT_Tbl):
            yield Table(child, parent)
document = Document("Poyasnitelnaya_zapiska_Pleschev_Danil_021-1.docx")
for block in iter_block_items(document):
    #print(block.text if isinstance(block, Paragraph) else '')
    if isinstance(block, Paragraph):
        print(block.text)
    elif isinstance(block, Table):
        for row in block.rows:
            row_data = []
            for cell in row.cells:
                for paragraph in cell.paragraphs:
                    row_data.append(paragraph.text)
            print("\t".join(row_data))





from __future__ import (
    absolute_import, division, print_function, unicode_literals
)
import json
from docx import Document
from docx.document import Document as _Document
from docx.oxml.text.paragraph import CT_P
from docx.oxml.text.run import CT_R
from docx.oxml.table import CT_Tbl
from docx.table import _Cell, Table
from docx.text.paragraph import Paragraph
from docx.text.run import Run
#import datetime
import sys, traceback
# import win_unicode_console
from colorama import init
from colorama import Fore, Back, Style
#outputFile = open('Document-ToJSON.csv', 'w', newline='\n')
#outputWriter = csv.writer(outputFile)
gblDocTree = []
gblDocListNumber = []
gblRowCols = {}
def init_myGlobals():
    #Reinitialize Global Variables
    #init()
    win_unicode_console.enable()
    init()
    global gblDocTree
    gblDocTree = []
    global gblDocListNumber
    gblDocListNumber = []
    global gblRowCols
    gblRowCols = {}
    return
class tblparam():
    def __init__(self,param):
        self.param = param
def get_num(x):
    return int(''.join(ele for ele in x if ele.isdigit()))
def add_RowCol(rowNumber, rowList):
    global gblRowCols
    gblRowCols[rowNumber] = rowList
    return
def add_to_sectionnumber(myLocation):
    global gblDocListNumber
    myInt = myLocation - 1
    if myLocation > len(gblDocListNumber) or len(gblDocListNumber) == 0:
        #initializing
        gblDocListNumber.append(1)
    elif len(gblDocListNumber) == myLocation:
        #if total array len is equal to current heading depth
        #do this
        gblDocListNumber[myInt] = gblDocListNumber[myInt] + 1
    #elif myLocation == 1:
    #   del gblDocListNumber[0:]
    #   gblDocListNumber[0] = gblDocListNumber[0] + 1
    elif len(gblDocListNumber) > myLocation:
        #x = len(gblDocListNumber) - myLocation
        #print("myLocation:{0}, myListCount:{1}".format(myLocation, len(gblDocListNumber)))
        #Eliminate everything from
        del gblDocListNumber[myLocation:]
        gblDocListNumber[myLocation - 1] = gblDocListNumber[myLocation - 1] + 1
    return
def add_to_hierarchy(myHeading, myLocation):
    #Create a String Array holding the Paragraph
    #Names, and appending them to previous levels
    #Heading1 > SubHeading2 > SubHeading3
    global gblDocTree
    myInt = myLocation - 1
    if myLocation > len(gblDocTree) or len(gblDocTree) == 0:
        gblDocTree.append(myHeading)
    elif len(gblDocTree) == myLocation:
        gblDocTree[myInt] = myHeading
    elif myLocation == 1:
        del gblDocTree[:]
        gblDocTree.append(myHeading)
    elif len(gblDocTree) > myLocation:
        x = len(gblDocTree) - myLocation
        #print("i'm going to remove -{0}".format(x))
        del gblDocTree[myLocation - 1:]
        gblDocTree.append(myHeading)
    return
def iter_block_items(parent):
    #"""
    #Generate a reference to each paragraph and table child within *parent*,
    #in document order. Each returned value is an instance of either Table or
    #Paragraph. *parent* would most commonly be a reference to a main
    #Document object, but also works for a _Cell object, which itself can
    #contain paragraphs and tables.
    #"""
    if isinstance(parent, _Document):
        parent_elm = parent.element.body
        #print(parent_elm.xml)
    elif isinstance(parent, _Cell):
        parent_elm = parent._tc
    else:
        raise ValueError("something's not right")
    for child in parent_elm.iterchildren():
        if isinstance(child, CT_P):
            yield Paragraph(child, parent)
        elif isinstance(child, CT_Tbl):
            yield Table(child, parent)
        #elif isinstance(child, CT_R):
        #   yield Run(child, parent)
def parseDocX(mydocumentfullpath, startSection):
    init_myGlobals()    #Initialize 
    #Setup variables#
    myDoc = mydocumentfullpath
#   f = open(outputCSVPath, 'w', newline='')    #Python 3, newline='' eliminates extra newlines' in output
    startSectSet = True
    try:
        document = Document(myDoc)
        prvHeader = ''
        headerLst = ['Heading 1',
                        'Heading 2', 'Heading 3', 'Heading 4',
                        'Heading 5', 'Heading 6', 'Heading 7',
                        'Heading 8', 'Heading 9',
                        'Egemin1', 'Egemin2', 'Egemin3', 'Egemin4',
                        'Egemin5', 'Egemin6', 'Egemin7', 'Egemin8',
                        'Egemin9', 'Egemin10', 'Egemin11', 'Egemin12']
        valNext = False
        prvIntHeadLv = 0
        curHeadIntLv = 0
        curHeadNm = ''
        curListNm = ''
        myIntValName = ''
        myPropCnt = 0
        sectionJSON = {}
        paraText = ''
        for block in iter_block_items(document):
            #print(block.text if isinstance(block, Paragraph) else '')
            #print('************************')
            #print('NEW LOOP')
            if isinstance(block, Paragraph):
                #print('In Paragraph')
                #for myRun in block.runs:
                #   print('Got Runs ?')
                #   print('Run Text :: {0}'.format(myRun.text))
                    #print('Style :: {0}'.format(myRun.style.name))
                #print(block.runs.text)
                #print(block.text)
                #print(block.style.name)
                if block.style.name in headerLst:
                    #New Document Header, so new Section
                    sectionJSON = {}    #Reset
                    paraText = ''
                    #Paragraphs contain all doc information.
                    #Using the above array, we're checking for the most commonly used
                    #Section/Paragrah Headers
                    #So we can differentiate what data we are actually processing
                    curHeadIntLv = get_num(block.style.name)    
                    add_to_hierarchy(block.text.strip().lower(), curHeadIntLv)
#BOUTIFY CODE
                    if len(block.text.strip().lower())>0:
                        add_to_sectionnumber(curHeadIntLv)
                    curListNm = '.'.join(map(str, gblDocListNumber))
                    curHeadNm = "%s %s" % (curListNm, block.text.strip())
                    #Check if Current Section is greater than required Start
                    if(startSectSet and curListNm!=''):
                        sectionHeading = curHeadNm.lstrip().split(" ")[0]   #Use Full Paragraph Header String, to ID true section number
                        curListTuple = tuple([int(x) for x in sectionHeading.split('.')])
                        reqStartTuple = tuple([int(x) for x in startSection.split('.')])
                        if (curListTuple < reqStartTuple):
                            continue    #Skip iteration
                        elif (curListTuple > reqStartTuple):
                            break   #Exit
                    if curHeadIntLv == 1 or prvIntHeadLv == 0:
                        #curHeadNm = block.text.strip().lower()
                        prvIntHeadLv = curHeadIntLv
                    elif curHeadIntLv == prvIntHeadLv:
                        prvIntHeadLv = curHeadIntLv
                        continue
                    elif curHeadIntLv > prvIntHeadLv:
                        prvIntHeadLv = curHeadIntLv
                        continue
                    else:
                        #curHeadNm = block.text.strip().lower()
                        prvIntHeadLv = curHeadIntLv
                        continue
                else:
                    curParaText = block.text.strip().lower()
                    paraText += block.text.strip().lower().replace("'", "''")
            elif isinstance(block, Table):  #process table rows, for interesting data
            #Check if Current Section is greater than required Start
                if(startSectSet and curListNm!=''):
                    sectionHeading = curHeadNm.lstrip().split(" ")[0]   #Use Full Paragraph Header String, to ID true section number
                    curListTuple = tuple([int(x) for x in sectionHeading.split('.')])
                    reqStartTuple = tuple([int(x) for x in startSection.split('.')])
                    if (curListTuple < reqStartTuple):
                        continue    #Skip iteration
                    elif (curListTuple > reqStartTuple):
                        break   #exit
                else:
                    continue        
                #Assuming if @ table, then paragraph Text is all captured
                #sectionJSON.update({"ParagraphText":paraText})
                i = 0
                if curHeadNm!='':
                    #print("Good Heading")
                    #Try and get the Heading Number
                    sectionHeading = curHeadNm.lstrip().split(" ")[0]
                    #print("Section Check ; {0}".format(sectionHeading))
                else:
                    #print("Empty Heading")
                    continue
                rowsArray = []
                headerArray = []
                #Process Table, row by row
                for row in block.rows:
                    #print('Processing section {0}'.format(sectionHeading))
                    i += 1
                    myCell = 0
                    JSONrow = {}
                    rstList = []
                    rowStringify = []
                    if i==1:
                        for row_cell in row.cells:
                            headerArray.append(row_cell.text.strip().lower().replace("'", "''"))
                            continue #Start proper table loop
                    else:
#                   for row_cell in row.cells:
#                       rstList.append(row_cell.text.strip().lower().replace("'", "''"))
                        for x in range(len(headerArray)):
                            #print('Iteration {0}'.format(x))
                            #print(row.cells[x].text.strip().lower())
                            rowStringify.append("\"" + headerArray[x] + "\"" + ":" + "\"" + row.cells[x].text.strip().lower().replace("'", "''") + "\"")
                        #Create JSON object, with Array of Columns as Value
                        myStr = ("{" + (','.join(map(str, rowStringify))) + "}")
                        print(u"{}".format(myStr))
                        #JSONrow = json.loads(myStr.replace('\r', '\\r').replace('\n', '\\n'))
                        JSONrow = json.loads(u"{}".format(myStr))
                        rowsArray.append(JSONrow)   #Now, add JSONrow back to array object
                sectionJSON.update({"Rows":rowsArray})
                break   #end now, after fully processing table
                #print(json.dumps(sectionJSON, indent=4, sort_keys=True))
                #writer = csv.writer(f, delimiter=',')
                #writer.writerow([sectionHeading, json.dumps(sectionJSON)])
                #now, back to start
    except IOError as e:
        print ('I/O error({0}): {1}'.format(e.errno, e.strerror))
#       traceback.print_exc()
        #return 1
    except ValueError:
        print ('Could not convert data to an integer. {0} :: {1}'.format(sys.exc_info()[0], sys.exc_info()[1]))
#       traceback.print_exc()
        #return 1
    except :
        print ('Unexpected error: {0} :: {1}'.format(sys.exc_info()[0], sys.exc_info()[1]))
        traceback.print_exc()
        #return 1
    finally:
        #f.close()
        win_unicode_console.disable()
        return json.dumps(sectionJSON,sort_keys=True)
#       globals().clear()
        #return 0
#if __name__=='__main__':
#   sys.exit(main(sys.argv[1], sys.argv[2]))
