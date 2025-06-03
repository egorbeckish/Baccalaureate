from docs_settings import *


st.set_page_config(
	layout='centered'
)

st.title('Подключение базы знаний')


files = st.file_uploader(
	"Выберите документы для загрузки...",
	type=['docx', 'pdf', 'epub', 'ppt', 'pptx', 'txt', 'jpg', 'png', 'tiff', 'bmp'],
	accept_multiple_files=True
)
	
if files:
	load_files_knowledge(files)