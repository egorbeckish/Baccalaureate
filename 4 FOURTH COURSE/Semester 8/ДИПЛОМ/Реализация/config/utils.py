from config import *


def get_gigachat_token():
	"""
		curl -L -X POST 'https://ngw.devices.sberbank.ru:9443/api/v2/oauth' \
		-H 'Content-Type: application/x-www-form-urlencoded' \
		-H 'Accept: application/json'
		--dara 'scope=GIGACHAT_API_PERS'
	"""

	url: str = 'https://ngw.devices.sberbank.ru:9443/api/v2/oauth'

	headers = {
		'Content-Type': 'application/x-www-form-urlencoded',
		'Accept': 'application/json',
		'RqUID': str(uuid.uuid4()),
	}

	payload: dict[str: str] = {
		'scope': 'GIGACHAT_API_PERS',
	}

	request = requests.post(
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


def get_files_name():
	files = st.session_state.knowledge_files + st.session_state.files

	files_name = []
	for file in files:
		files_name += [file['filename']]

	return files_name


def get_name_files_to_id():
	files = st.session_state.knowledge_files + st.session_state.files

	dict_files_id = {}
	for file in files:
		dict_files_id[file['filename']] = file['id']

	return dict_files_id


def get_models():
	return ['GigaChat'] + [model.split()[0] for model in os.popen('ollama list')][1:]


def sql_cursor():
	connect = psql.connect(**DB_DATA)
	connect.autocommit = True
	return connect.cursor()


def get_knowledge():
	st.session_state.cursor.execute(
		# "SELECT filename, format, convert_from(data, 'utf-8')::text FROM knowledge;"
		"SELECT * FROM knowledge;"
	)

	data = st.session_state.cursor.fetchall()
	
	files = []
	for file in data:
		files += [
			{
				'filename': f'{file[0]}.{file[1]}',
				'id': f'{file[2]}/{file[0]}/{file[1]}',
			}
		]

	return files