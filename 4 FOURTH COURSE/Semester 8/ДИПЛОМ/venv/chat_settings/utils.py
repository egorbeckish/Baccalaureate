from chat_settings import *


def send_message(prompt, role):
	st.chat_message(role).write(prompt)
	st.session_state.messages.append(
		{
			'role': role,
			'prompt': prompt
		}
	)


def send_prompt(prompt, token, model, attachments=None):
	"""
		curl -L -X POST 'https://gigachat.devices.sberbank.ru/api/v1/chat/completions' \
		-H 'Content-Type: application/json' \
		-H 'Accept: application/json' \
		-H 'Authorization: Bearer <токен_доступа>' \
		--data-raw '{
		"model": "GigaChat",
		"messages": [
			{
			"role": "user",
			"content": "Привет! Как дела?"
			}
		],
		"stream": false,
		"repetition_penalty": 1
		}'
	"""

	if model != 'GigaChat':
		url = 'http://localhost:11434/api/generate'
		
		payload = {
			'model': model,
			'prompt': prompt,
			'stream': False,
		}

		response = requests.post(
			url=url,
			data=json.dumps(payload)
		)

		return response.json()['response']
		

	url = 'https://gigachat.devices.sberbank.ru/api/v1/chat/completions'

	headers = {
		'Content-Type': 'application/json',
		'Accept': 'application/json',
		'Authorization': f'Bearer {token}'
	}

	payload = {
		'model': 'GigaChat',
		'messages': [
			{
				'role': 'user',
				'content': prompt
			},
		],
	}
	

	if attachments:
		if 'memory' in attachments[0]:
			file_name, file_format = attachments[0].split('/')[1:]
			bytes = get_knowledge_bytes(file_name, file_format)
		
		else:
			payload['messages'][0]['attachments'] = attachments
		return

	
	response = requests.post(
		url=url,
		headers=headers,
		data=json.dumps(payload),
		verify=False
	)

	"""
		{
			"choices": [
			{
				"finish_reason": "stop",
				"index": 0,
				"message": {
					"content": "Все отлично, спасибо. А как ваши дела?",
					"role": "assistant"
				}
			}
			],
			"created": 1706096547,
			"model": "GigaChat",
			"object": "chat.completion",
			"usage": {
				"completion_tokens": 12,
				"prompt_tokens": 173,
				"system_tokens": 0,
				"total_tokens": 185
			}
		}
	"""

	return response.json()['choices'][0]['message']['content']


def get_files_id(files):
	attachments = []
	for file in files:
		attachments += [st.session_state.files_id[file]]
	
	return attachments


def get_knowledge_bytes(file_name, file_format):
	st.session_state.cursor.execute(
		f"SELECT convert_from(data, 'utf-8')::text FROM knowledge WHERE filename='{file_name}' AND format='{file_format}';"
	)

	[bytes] = st.session_state.cursor.fetchone()
	return bytes