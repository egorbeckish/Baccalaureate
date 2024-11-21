from utils import *
from big_text import *

st.markdown("# :rainbow[Test Chat]")

if 'access_token' not in st.session_state:
	try:
		st.session_state.access_token = get_gigachat_token()
		st.toast('GIGACHAT token получен', icon='😊')
	
	except Exception as error:
		st.toast(f'Возникла проблема с получением GIGACHAT token\n\nОшибка: {error}', icon='❌')

if 'access_messages' not in st.session_state:
	st.session_state.access_messages = [
		{
			'role': 'ai',
			'prompt': 'Ждем вашего запроса 😊'
		}
	]

for message in st.session_state.access_messages:
	st.chat_message(
		message['role']
	).write(message['prompt'])

if prompt := st.chat_input():
	st.chat_message('user').write(prompt)
	st.session_state.access_messages.append(
		{
			'role': 'user',
			'prompt': prompt
		}
	)
	
	responce: str = send_prompt(prompt, st.session_state.access_token)
	st.chat_message('ai').write(responce)
	st.session_state.access_messages.append(
		{
			'role': 'ai',
			'prompt': responce
		}
	)

#token = get_gigachat_token()
#a = foo(token, 'Какой нужно использовать размер шрифта?')
#print(a)

###_get_files = get_files(token)
###print(_get_files, sep='\n\n')

##_embeddings = embeddings(token)
##print(_embeddings)