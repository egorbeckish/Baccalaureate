from library import *
# from big_text import *

def get_gigachat_token() -> str:
	"""
		curl -L -X POST 'https://ngw.devices.sberbank.ru:9443/api/v2/oauth' \
		-H 'Content-Type: application/x-www-form-urlencoded' \
		-H 'Accept: application/json'
		--dara 'scope=GIGACHAT_API_PERS'
	"""

	url: str = 'https://ngw.devices.sberbank.ru:9443/api/v2/oauth'

	headers: dict[str: str] = {
		'Content-Type': 'application/x-www-form-urlencoded',
		'Accept': 'application/json',
		'RqUID': str(uuid.uuid4()),
	}

	payload: dict[str: str] = {
		'scope': 'GIGACHAT_API_PERS',
	}

	request: dict = requests.post(
		url=url,
		headers=headers,
		auth=HTTPBasicAuth(CLIENT_ID, SECRET),
		data=payload,
		verify=False
	)

	"""
		{
			"access_token": "<токен_доступа>",
			"expires_at": 1706026848841
		}
	"""
	return request.json()['access_token']


def get_auth_key() -> str:
	return AUTH_KEY


def send_prompt(prompt: str, access_token: str, attachments=None) -> str:
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

	url: str = 'https://gigachat.devices.sberbank.ru/api/v1/chat/completions'

	headers: dict[str: str] = {
		'Content-Type': 'application/json',
		'Accept': 'application/json',
		'Authorization': f'Bearer {access_token}'
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
		payload['messages'][0]['attachments'] =[attachments]

	responce: dict = requests.post(
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
	return responce.json()['choices'][0]['message']['content']


def metadata_load_file(file):
	file_name, file_type, _bytes = file

	return (
		file_name,
		_bytes,
		file_type

	)
	
	# if _format == 'txt':
	# 	return (
	# 			f'{file_name}.{_format}',
	# 			_bytes,
	# 			f'text/plain'
	# 		)

	# elif _format in ['docx', 'pdf', 'epub', 'ppt', 'pptx']:
	# 	if _format == 'docx':
	# 		return (
	# 			f'{file_name}.{_format}',
	# 			_bytes,
	# 			# f'application/msword'
	# 			f'application/vnd.openxmlformats-officedocument.wordprocessingml.document'
	# 		)

	# 	else:
	# 		return (
	# 			f'{file_name}.{_format}',
	# 			_bytes,
	# 			f'application/{_format}'
	# 		)
	
	# elif _format in ['jpg', 'png', 'tiff', 'bmp']:
	# 	return (
	# 			f'{file_name}.{_format}',
	# 			_bytes,
	# 			f'image/{_format}'
	# 		)
	


def load_file(file_name: str, access_token: str) -> None:
	"""
		sh
		curl --location --request POST 'https://gigachat.devices.sberbank.ru/api/v1/files' \
		--header 'Authorization: Bearer access_token' \
		--form 'file=@"<путь_к_файлу>/example.jpeg"' \
		--form 'purpose="general"'
	"""

	url: str = 'https://gigachat.devices.sberbank.ru/api/v1/files'

	headers: dict[str: str] = {
		'Authorization': f'Bearer {access_token}',
	}

	payload: dict[str: str] = {
		'purpose': 'general',
	}


	# files: list[tuple[str, tuple[str]]] = [
	# 	(
	# 		'file',
	# 		(
	# 			file_name.name,
	# 			open(f'files/{file_name.name}', 'rb'),
	# 			f'image/{(format:=file_name.name.split('.'))[-1]}'
	# 		)
	# 	)
	# ]

	files = [
		(
			'file',
			metadata_load_file(file_name)
		)
	]

	responce: dict = requests.post(
		url=url,
		headers=headers,
		data=payload,
		files=files,
		verify=False
	)

	return responce.json()


def get_files(access_token: str) -> dict[str: str | int]:
	"""
		sh
		curl -L -X GET 'https://gigachat.devices.sberbank.ru/api/v1/files' \
		-H 'Accept: application/json' \
		-H 'Authorization: Bearer access_token'
	"""

	url: str = 'https://gigachat.devices.sberbank.ru/api/v1/files'

	headers: dict[str: str] = {
		'Accept': 'application/json',
		'Authorization': f'Bearer {access_token}'
	}

	responce: dict = requests.get(
		url=url,
		headers=headers,
		verify=False
	)

	return responce.json()['data']


def get_files_name(file_list):
	return [file['filename'] for file in file_list]


def delete_all_files(access_token: str) -> list[dict[str: str | int]]:
	"""
		sh
		curl -L -X POST 'https://gigachat.devices.sberbank.ru/api/v1/files/:file/delete' \
		-H 'Accept: application/json' \
		-H 'Authorization: Bearer access_token'
	"""

	url: str = 'https://gigachat.devices.sberbank.ru/api/v1/files/:file/delete'

	payload = {}

	headers: dict[str: str] = {
		'Accept': 'application/json',
		'Authorization': f'Bearer {access_token}'
	}

	files = get_files(access_token)

	if not files:
		return {
			'code': 200,
			'message': 'data is empty'
		}
	
	responces: list[dict] = []
	for file in files:
		_id: str | int = file['id']
		_url: str = url.replace(':file', _id, 1)
		responce: dict = requests.post(
			url=_url,
			headers=headers,
			data=payload,
			verify=False
		)

		responces += [responce.json()]

	return responces


def embeddings(access_token: str) -> None:
	"""
		curl https://gigachat.devices.sberbank.ru/api/v1/embeddings \
  		--header 'Content-Type: application/json' \
  		--header 'Authorization: Bearer <токен доступа>' \
		--data '{
			"model": "Embeddings",
			"input": [
				"Расскажи о современных технологиях",
				"Какие новинки в мире IT?"
			]
		}'
	"""

	url: str = 'https://gigachat.devices.sberbank.ru/api/v1/embeddings'

	headers: dict[str: str] = {
		'Content-Type': 'application/json',
		'Accept': 'application/json',
  		'Authorization': f'Bearer {access_token}'
	}

	payload: dict = json.dumps(
		{
			'model': 'Embeddings',
			'input': [
				file 
				for file in os.listdir() 
				if file.endswith('.pdf')
			]
		}
	)

	responce: dict = requests.post(
		url=url,
		headers=headers,
		data=payload,
		verify=False
	)

	return responce.json()


def summarize_text(access_token: str, prompt: str) -> None:
	giga = GigaChat(
		model="GigaChat",
		verify_ssl_certs=False,
		profanity_check=False
	)

	giga.access_token = access_token

	loader = TextLoader("files/МиМ.txt", encoding="utf-8")
	documents = loader.load()

	text_splitter = RecursiveCharacterTextSplitter(
		chunk_size = 4096,
		chunk_overlap  = 0,
		length_function = len,
		is_separator_regex = False,
	)


	_prompt = langchain.prompts.PromptTemplate.from_template(
		template=f"{prompt}\n\n" + '{text}'
	)

	chain = load_summarize_chain(
		giga,
		chain_type='map_reduce',
		map_prompt=_prompt,
		combine_prompt=_prompt,
		verbose=False
	)

	results = chain.invoke(
		{
			'input_documents': documents
		}
	)

	return results['output_text']


def dict_name_id(access_token):
	files = get_files(access_token)
	_dict_name_id = {}

	for file in files:
		_dict_name_id[file['filename']] = file['id']

	return _dict_name_id


def name_file_to_id(access_token, file_name):
	return dict_name_id(access_token)[file_name]