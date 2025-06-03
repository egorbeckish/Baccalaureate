from chat_settings import *


def send_message(prompt, role):
	st.chat_message(role).write(prompt)
	st.session_state.messages.append(
		{
			'role': role,
			'prompt': prompt
		}
	)


def send_prompt(prompt, model, attachments=None):
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

		if attachments:
			if 'memory' in attachments:
				file_name, file_format = attachments.split('/')[1:]
				return summarize_text(prompt, model, file_name, file_format)

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
		'Authorization': f'Bearer {st.session_state.token}'
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
		if 'memory' in attachments:
			file_name, file_format = attachments.split('/')[1:]
			return summarize_text(prompt, model, file_name, file_format)
		
		else:
			payload['messages'][0]['attachments'] = attachments
	
		return attachments

	
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


def summarize_text(prompt, model, file_name, file_format):
	if model != 'GigaChat':
		llm = OllamaLLM(
			base_url='http://localhost:11434',
			model=model,
		)

	else:
		llm = GigaChat(
			credentials=AUTH_KEY,
			model="GigaChat",
			verify_ssl_certs=False,
			profanity_check=False,
		)

	db = SQLDatabase.from_uri(DB_LINK)
	loader = SQLDatabaseLoader(
    	db=db,
    	query=f"SELECT convert_from(data, 'utf-8')::text FROM knowledge WHERE filename='{file_name}' AND format='{file_format}'",
	)

	documents = loader.load()
	

	prompt = PromptTemplate(
		template=f"{prompt}\n\n" + '{text}'
	)


	chain = load_summarize_chain(
		llm,
		chain_type='map_reduce',
		map_prompt=prompt,
		combine_prompt=prompt,
		verbose=False
	)

	results = chain.invoke(
		{
			'input_documents': documents
		}
	)


	return results['output_text']


def search_file(files, prompt, model):
	"""
	curl --location 'https://gigachat.devices.sberbank.ru/api/v1/chat/completions' \
	--header 'Content-Type: application/json' \
	--header 'Authorization: <токен_доступа>' \
	--data '{
	  "model": "GigaChat",
	  "messages": [
	        {
	            "role": "system",
	            "content": "Классифицируй обращения пользователя в подходящую категорию. Категории: Статус заказа, Возврат и обмен товаров, Характеристики продукта, Технические проблемы, Другое. В ответе укажи только категорию."
	        },
	        {
	            "role": "user",
	            "content": "При оформлении заказа возник вопрос о возможностях устройства. Помогите уточнить информацию, пожалуйста?"
	        }
	    ]
	}'
	"""

	if model != 'GigaChat':
		url = 'http://localhost:11434/api/generate'

		payload = {
			'model': model,
			'prompt': f'Список документов: {files}\n\nИз списка выше выбери релевантный документ, который соответствует запросу: {prompt}\n\nВыведи только название файл, который представлен в списке.',
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
		'Authorization': f'Bearer {st.session_state.token}'
	}

	payload = {
		'model': 'GigaChat',
		'messages': [
			{
				'role': 'system',
				'content': 'Ты - тот, кто выбирает из предоставленного списка название релевантного документ, который наиболее соответствует запросу. Отвечать нужно только названием документа.'
			},
			{
				'role': 'user',
				'content': f'Список документов: {files}\n\nЗапрос: {prompt}'
			},
		],
		'stream': False,
	}

	response = requests.post(
		url=url,
		headers=headers,
		data=json.dumps(payload),
		verify=False
	)

	return response.json()['choices'][0]['message']['content']