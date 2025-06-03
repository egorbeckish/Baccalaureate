from docs_settings import *


st.set_page_config(
	layout='centered'
)

st.title('Загрузка документов')


files = st.file_uploader(
	"Выберите документы для загрузки...",
	type=['docx', 'pdf', 'epub', 'ppt', 'pptx', 'txt', 'jpg', 'png', 'tiff', 'bmp'],
	accept_multiple_files=True
)
	
if files:
	load_files(files, st.session_state.token)
	st.session_state.files = get_files(st.session_state.token)
	st.session_state.files_name = get_files_name()
	st.session_state.files_id = get_name_files_to_id()
