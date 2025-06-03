from config import *


pages = st.navigation(
	{
		'Описание': [
			st.Page(r'main.py', title='Главная', default=True)
		],

		'СИПвКБЗ': [
			st.Page(r'chat_settings/chat.py', title='Чат', icon='🗨️'),
			st.Page(r'chat_settings/close_chat.py', title='Закрыть чат', icon='🔒')
		],

		'Документы/база знаний': [
			st.Page(r'docs_settings/upload_files.py', title='Загрузка документов', icon='🔄'),
			st.Page(r'docs_settings/view_delete_files.py', title='🗑️ Просмотр/удаление документов', icon='📄'),
			# st.Page(r'docs_settings/load_knowledge.py', title='Загрузка базы знаний', icon='🗃️'),
		]		
	}
	
	# [
	# 	st.Page(r'main.py', title='Главная', default=True),
	# 	st.Page(r'chat_settings/chat.py', title='Чат', icon='🗨️'),
	# 	st.Page(r'docs_settings/processing_files.py', title='Документы/база знаний', icon='📄'),
	# 	st.Page(r'chat_settings/close_chat.py', title='Закрыть чат', icon='🔒'),
	# ]
)

pages.run()