from docs_settings import *


def metadata_file(file, file_bytes):
	return (
		file.name,
		file_bytes,
		file.type if file.name.split('.')[-1] != 'docx' else 'application/msword'
	)


def load_file(metadata, token):
	"""
		sh
		curl --location --request POST 'https://gigachat.devices.sberbank.ru/api/v1/files' \
		--header 'Authorization: Bearer access_token' \
		--form 'file=@"<путь_к_файлу>/example.jpeg"' \
		--form 'purpose="general"'
	"""

	url = "https://gigachat.devices.sberbank.ru/api/v1/files"

	headers = {
		'Authorization': f'Bearer {token}'
	}

	payload = {
		'purpose': 'general'
	}

	file = [
		(
			'file',
			metadata
		)
	]


	responce = requests.post(
		url=url,
		headers=headers,
		data=payload,
		files=file,
		verify=False
	)


	return responce.json()


def load_files(files, token):
	with st.status('Обработка файлов...'):
		st.write('Получаем файлы...')
		time.sleep(3)

		st.write('Загружаем файлы в хранилище...')
		for file in files:
			load_file(metadata_file(file, file.getvalue()), token)
			time.sleep(2)

		st.write('Файлы успешно сохранены в хранилище.')
		time.sleep(3)

	view_success_message(
		'Файлы успешно загружены',
		5,
		'✅'
	)


def get_files(token):
	"""
		sh
		curl -L -X GET 'https://gigachat.devices.sberbank.ru/api/v1/files' \
		-H 'Accept: application/json' \
		-H 'Authorization: Bearer access_token'
	"""

	url = 'https://gigachat.devices.sberbank.ru/api/v1/files'

	headers = {
		'Accept': 'application/json',
		'Authorization': f'Bearer {token}'
	}

	responce = requests.get(
		url=url,
		headers=headers,
		verify=False
	)


	return responce.json()['data']


def df_files():
	files = st.session_state.knowledge_files + st.session_state.files
	# files = st.session_state.files
	# files = st.session_state.knowledge_files

	data_files = []
	for file in files:
		file_name, _type = file['filename'].split('.')
		_id = file['id']
		data_files += [[file_name, _type, _id]]
	
	return pd.DataFrame(
		data_files,
		columns=['Название файла', 'Формат', 'ID']
	)


def delete_file(file_id, token):
	"""
		sh
		curl -L -X POST 'https://gigachat.devices.sberbank.ru/api/v1/files/:file/delete' \
		-H 'Accept: application/json' \
		-H 'Authorization: Bearer access_token'
	"""

	url = f'https://gigachat.devices.sberbank.ru/api/v1/files/{file_id}/delete'


	headers: dict[str: str] = {
		'Accept': 'application/json',
		'Authorization': f'Bearer {token}'
	}

	responce = requests.post(
		url=url,
		headers=headers,
		verify=False
	)

	return responce


def delete_all_files(files_ids, token):
	with st.spinner('Происходит удаление всех файлов...'):
		for file_id in files_ids:
			if 'memory' in file_id:
				continue
			
			delete_file(file_id, token)
			time.sleep(2)

	view_success_message(
		'Все документы успешно удалены',
		5,
		'✅'
	)
	
	st.session_state.files = []
	st.session_state.files_name = []
	st.rerun()


def view_success_message(text, seconds, icon=None):
	success = st.success(
		text,
		icon=icon
	)

	time.sleep(seconds)
	success.empty()


def write_file_bytes(file_name, bytes):
	with open(rf'{os.getcwd()}\docs_settings\{file_name}', 'wb') as tmp_file:
		tmp_file.write(bytes)


def open_docx(path):
	return Document(path)


def get_paragraphs_docx(document):
	return document.paragraphs


def paragraphs2text(paragraphs):
	return '\n\n'.join([paragraph.text for paragraph in paragraphs if paragraph.text])


def docx2bytes(path):
	document = open_docx(path)
	paragraphs = get_paragraphs_docx(document)
	text = paragraphs2text(paragraphs)
	return bytes(text, 'utf-8')


def open_pdf(path):
	return PdfReader(path)


def get_pdf_pages(document):
	return document.pages


def extract_pdf(pages):
	return '\n\n'.join([page.extract_text() for page in pages])


def pdf2bytes(path):
	document = open_pdf(path)
	pages = get_pdf_pages(document)
	text = extract_pdf(pages)
	return bytes(text, 'utf-8')


def open_pptx(path):
	return Presentation(path)


def get_slides_pptx(document):
	return document.slides


def get_shapes_pptx(slide):
	return slide.shapes

def get_paragraphs_pptx(shape):
	return shape.text_frame.paragraphs


def get_runs(paragraph):
	return paragraph.runs


def runs2text(runs):
	text = ''
	for run in runs:
		text += f'{run.text}\n\n'
	
	return text


def pptx2bytes(path):
	document = open_pptx(path)
	text = ''
	count_slide = 0

	slides = get_slides_pptx(document)
	for slide in slides:
		count_slide += 1

		shapes = get_shapes_pptx(slide)
		for shape in shapes:
			if not shape.has_text_frame:
				continue

			paragraphs = get_paragraphs_pptx(shape)
			for paragraph in paragraphs:
				runs = get_runs(paragraph)
				if runs:
					text_slide = f'[Слайд №{count_slide}]\n\n{runs2text(runs)}[Слайд №{count_slide}]'
			
					text += f'{text_slide}\n'

	return bytes(text, 'utf-8')


def txt2bytes(path):
	return bytes(open(path, encoding='utf-8').read(), 'utf-8')


def file2bytes(file_name, file_format):
	path = rf'{os.getcwd()}\docs_settings\{file_name}'
	match file_format:
		case 'docx':
			return docx2bytes(path) 
			
		case 'pdf':
			return pdf2bytes(path) 

		case 'pptx':
			return pptx2bytes(path)

		case 'txt':
			return txt2bytes(path)
		

def delete_load_file(file_name):
	os.remove(rf'{os.getcwd()}\docs_settings\{file_name}')


def insert_file_data(file_name, file_format, bytes):
	st.session_state.cursor.execute(
		'INSERT INTO knowledge values (%s, %s, %s)',
		(file_name, file_format, bytes)
	)


def load_file_knowledge(file, file_name, file_format):
	write_file_bytes(file.name, file.getvalue())
	bytes = file2bytes(file.name, file_format)
	delete_load_file(file.name)
	insert_file_data(file_name, file_format, bytes)
	


def load_files_knowledge(files):
	for file in files:
		file_name, file_format = file.name.split('.')
		load_file_knowledge(file, file_name, file_format)
		