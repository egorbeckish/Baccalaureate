from config import *
from docs_settings import *


st.set_page_config(
	layout='wide'
)

st.markdown(
	'# Программный комплекс интеллектуального поиска в корпоративных базах знаний'
)

if 'token' not in st.session_state:
	try:
		st.session_state.token = get_gigachat_token()
		st.toast('GIGACHAT token получен', icon='😊')
	
	except Exception as error:
		st.toast(f'Возникла проблема с получением GIGACHAT token\n\nОшибка: {error}', icon='❌')


if 'cursor' not in st.session_state:
	st.session_state.cursor = sql_cursor()


if 'knowledge_files' not in st.session_state:
	st.session_state.knowledge_files = get_knowledge()


if 'files' not in st.session_state:
	st.session_state.files = get_files(st.session_state.token)
	st.session_state.files_name = get_files_name()
	st.session_state.files_id = get_name_files_to_id()
	st.toast('Документы из хранилища получены', icon='😊')


if 'models' not in st.session_state:
	st.session_state.models = get_models()
	st.session_state.models.pop(1)