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
			'БЗ', 
			'Название документа', 
			'Поиск в интернете'
		], 
		horizontal=True,
		help='БЗ - База знаний; Название документа - определенный документ, имеющихся в хранилище и базе знаний'
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
		case 'БЗ':
			pass

		case 'Название документа':
			attachments = get_files_id(select_files)
			responce = send_prompt(
				prompt,
				st.session_state.token,
				select_models,
				attachments
			)
			send_message(responce, 'ai')
			

		case 'Поиск в интернете':
			responce = send_prompt(
				prompt, 
				st.session_state.token,
				select_models,
			)
			send_message(responce, 'ai')