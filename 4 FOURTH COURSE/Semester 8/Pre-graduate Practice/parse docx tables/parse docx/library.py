try:
    import docx
    from docx import Document
    from tabulate import tabulate
    import os
    import regex

    os.system('clear; python main.py')

except ImportError:
    import os
    
    
    os.system('python3 -m pip install --upgrade pip; pip install -r requirements.txt; clear; python library.py; clear; python main.py')