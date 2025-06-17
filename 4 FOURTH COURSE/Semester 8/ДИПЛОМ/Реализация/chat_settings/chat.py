from chat_settings import *


st.set_page_config(
	layout='wide'
)


st.markdown(
	'# Чат'
)


setting = st.columns(2)

with setting[0]:
	select_models = st.radio(
		'Языковые модели',
		st.session_state.models,
		horizontal=True,
	)

	select_search = st.radio(
		'Способ нахождения', 
		[
			'БД', 
			'Название документа', 
			'Поиск в интернете'
		], 
		horizontal=True,
		help='БД - База документов; Название документа - определенный документ, имеющийся в хранилище'
	)

with setting[1]:
	clear = st.button('Очистить чат')
	if clear:
		st.session_state.messages = [
			{
				'role': 'ai',
				'prompt': 'Здравствуйте! Чем могу помочь?'
			}
		]

		st.rerun()
	

if select_search == 'Название документа':
	select_files = st.multiselect(
		'Список документов',
		st.session_state.files_name,
		placeholder='Введите название документа(ов)'
	)


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


if prompt:
	send_message(prompt, 'user')

	match select_search:
		case 'БД':
			knowledges = '\n'.join(st.session_state.files_name)
			response = search_file(
				knowledges,
				prompt,
				select_models,
			)
			
			file = response
			attachments = st.session_state.files_id[file]

			response = send_prompt(
				prompt,
				select_models,
				attachments
			)
			send_message(f'Данная информация выбрана из файла - {file}', 'ai')
			send_message(response, 'ai')

		case 'Название документа':
			attachments = get_files_id(select_files)
			response = send_prompt(
				prompt,
				select_models,
				attachments[0]
			)
			send_message(response, 'ai')
			

		case 'Поиск в интернете':
			response = send_prompt(
				prompt, 
				select_models,
			)
			send_message(response, 'ai')