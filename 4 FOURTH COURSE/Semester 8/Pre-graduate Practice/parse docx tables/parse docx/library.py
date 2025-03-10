try:
    import docx
    from docx import Document
    from tabulate import tabulate
    from PIL import Image

except ImportError:
    import os
    
    
    os.system('python3 -m pip install --upgrade pip; pip install -r requirements.txt; timeout 5; clear; python main.py')