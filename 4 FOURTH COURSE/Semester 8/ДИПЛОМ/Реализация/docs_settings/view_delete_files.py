from docs_settings import *

st.set_page_config(
	layout='centered'
)

st.title(
	'Список документов'
)


if not st.session_state.files and not st.session_state.knowledge_files:
	st.warning(
		'БЗ пуста! Необходимо загрузить документы. Перейдите в раздел "Документы/база знаний" -> "Загрузка документов"',
		icon='⚠️'
	)


else:
	recieved_files = st.data_editor(
		df_files(),
		hide_index=True,
		num_rows='dynamic',
	)

	delete_cols = st.columns(3)
	with delete_cols[0]:
		choose_delete = st.button('Удалить выбранные файлы')


	with delete_cols[1]:
		all_delete = st.button('Удалить все файлы')
	

	if choose_delete:
		print('Удаление выбраных файлов')
		
	elif all_delete:
		delete_all_files(recieved_files['ID'], st.session_state.token)