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
	st.markdown("# :rainbow[Test Chat]")

	if 'access_token' not in st.session_state:
		try:
			st.session_state.access_token = get_gigachat_token()
			st.toast('GIGACHAT token получен', icon='😊')
	
		except Exception as error:
			st.toast(f'Возникла проблема с получением GIGACHAT token\n\nОшибка: {error}', icon='❌')


	if 'messages' not in st.session_state:
		st.session_state.messages = [
			{
				'role': 'ai',
				'prompt': 'Здравствуйте! Чем могу помочь?'
			}
		]


	for message in st.session_state.messages:
		st.chat_message(
			message['role']
		).write(message['prompt'])
	

	prompt = st.chat_input(
		'Задайте свой вопрос...'
	)


	select_search = st.radio('Способ нахождения', ['БЗ', 'Название документа', 'Поиск в интернете'], horizontal=True)
	if select_search == 'Название документа':
		files = get_files(st.session_state.access_token)
		select_file = st.multiselect(
			'Список документов', 
			get_files_name(files), 
			placeholder='Введите название документа(ов)'
		)


	if prompt:
		st.chat_message('user').write(prompt)
		st.session_state.messages.append(
			{
				'role': 'user',
				'prompt': prompt
			}
		)


		match select_search:
			case 'БЗ':
				files = get_files(st.session_state.access_token)
				file_prompt = f"""Запрос: {prompt}\n\nВыбери из данного списка более релевантный файл к заданому запросу:\n{'\t'+'\n\t'.join(get_files_name(files))}\n\nВ ответе вывиди только название файла"""
				responce = send_prompt(file_prompt, st.session_state.access_token)
				file_id = name_file_to_id(st.session_state.access_token, responce)
				responce = send_prompt(prompt, st.session_state.access_token, file_id)
				st.chat_message('ai').write(responce)
				st.session_state.messages.append(
					{
						'role': 'ai',
						'prompt': responce
					}
				)

			case 'Название документа':
				file_id = name_file_to_id(st.session_state.access_token, *select_file)
				responce = send_prompt(prompt, st.session_state.access_token, file_id)
				st.chat_message('ai').write(responce)
				st.session_state.messages.append(
					{
						'role': 'ai',
						'prompt': responce
					}
				)
				

			case 'Поиск в интернете':
				responce: str = send_prompt(prompt, st.session_state.access_token)
				st.chat_message('ai').write(responce)
				st.session_state.messages.append(
					{
						'role': 'ai',
						'prompt': responce
					}
				)

		st.rerun()