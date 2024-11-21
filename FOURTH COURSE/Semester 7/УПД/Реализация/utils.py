from library import *
from big_text import *

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

def send_prompt(prompt: str, access_token: str) -> str:
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

	payload: dict = json.dumps(
		{
			'model': 'GigaChat',
			'messages': [
				{
					'role': 'user',
					'content': prompt
				},
			],
		}
	)

	responce: dict = requests.post(
		url=url,
		headers=headers,
		data=payload,
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

	files: list[tuple[str, tuple[str]]] = [
		(
			'file',
			(
				file_name,
				open(file_name, 'rb'),
				f'image/{(format:=file_name.split('.'))[-1]}'
			)
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

	return responce.json()

def delete_all_files(access_token: str) -> list[dict[str: str | int]]:
	"""
		sh
		curl -L -X POST 'https://gigachat.devices.sberbank.ru/api/v1/files/:file/delete' \
		-H 'Accept: application/json' \
		-H 'Authorization: Bearer access_token'
	"""

	url: str = 'https://gigachat.devices.sberbank.ru/api/v1/files/:file/delete'

	payload: dict[None] = {}

	headers: dict[str: str] = {
		'Accept': 'application/json',
		'Authorization': f'Bearer {access_token}'
	}

	files: list[dict[str: str | int]] = get_files(access_token)['data']

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


def word(word_file: str) -> None:
	#open('file.txt', 'wb').write(bytes([b for b in open(word_file, 'rb').read()]))
	print(open(word_file, 'rb').read().decode())

if __name__ == '__main__':
	word('llm модель 04.09.2024.docx')