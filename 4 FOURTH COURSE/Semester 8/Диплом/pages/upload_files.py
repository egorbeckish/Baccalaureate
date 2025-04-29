from utils import *


st.set_page_config(
	layout='wide'
)

columns_menu = st.columns([1, 2])

with columns_menu[0]:
	st.page_link('chat.py', label='Чат 📨')
	st.page_link(r'pages/upload_files.py', label='Документы/база знаний 📄')
	st.page_link(r'pages/close_chat.py', label='Закрыть чат 🔒')


with columns_menu[1]:
	st.markdown('# Документы/база знаний')

	tab_load_files, see_files = st.tabs(['Загрузка/подключение', 'Просмотр документов'])

	with tab_load_files:
		files = st.file_uploader(
			"Выберите документы для загрузки...",
			type=['docx', 'pdf', 'epub', 'ppt', 'pptx', 'txt', 'jpg', 'png', 'tiff', 'bmp'],
			accept_multiple_files=True
		)

		if files:
			for file in files:
				file = file.name, file.type, file.getvalue()
				print(load_file(file, st.session_state.access_token))
	
	with see_files:
		if st.button('Получить файлы'):
			print(get_files(st.session_state.access_token))

		if st.button('Удалить все файлы'):
			print(delete_all_files(st.session_state.access_token))