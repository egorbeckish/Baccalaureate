from library import *

def new_user(
		form: werkzeug.datastructures.structures.ImmutableMultiDict,
		session: werkzeug.local.LocalProxy
		) -> None:
	try:
		query = f"""
				insert into 
				users
				values
				(
					'{session['ID']}',
					'{form['login']}',
					'{form['password']}',
					'{form['name']}',
					'{form['surname']}',
					'{form['thurname']}',
					'{form['phone_number']}'
				);
				"""
		
		cursor.execute(query)

		query = f"""
				insert into 
				home
				values
				(
					'{session['ID']}',
					'1',
					'{form['region']}',
					'{form['city']}',
					'{form['street']}',
					'{form['home_number']}',
					'{form['floor_number']}',
					'{form['entrance_number']}'
				);
				"""
		cursor.execute(query)

		print(form['entrance_number'])
		write_logs(
			type_status='У',
			text='Данные успешное добавлены в БД (регистрация).',
		)

	except Exception as error:
		write_logs(
			type_status='О',
			text='При регистрации данные не добавились в БД.',
			error_msg=error
		)
	return


def check_user(login: str) -> bool:
	query = f"""
			select count(*) from
			users
			where
			login='{login}'	
			"""
	
	cursor.execute(query)
	return cursor.fetchone()[0]


def write_logs(type_status: str=None, text: str=None, error_msg: any=None) -> None:
	file = open('logs.txt', mode='+a')
	
	time_ = time.localtime()
	time_data = time.strftime('%d/%m/%y', time_)
	time_clock = time.strftime('%H:%M:%S', time_)
	time_str = f"""[DATA --- {time_data}][TIME --- {time_clock}]"""
	status = f'[STATUS --- {dict_error_logs[type_status]}]'

	if not isinstance(error_msg, type(None)):
		number_error = str(error_msg).split()[0]
		error_msg = traceback.TracebackException(
			exc_type=type(error_msg),
			exc_traceback=error_msg.__traceback__,
			exc_value=error_msg
		).stack[-1]
		
		if isinstance(text, str):
			error_msg = f'{'\t' * 18}Обратитесь к файлу: {error_msg.filename.split("\\")[-1]}\n\
					{'\t' * 13}в функции/переменной или т.п.: {error_msg.name}\n\
					{'\t' * 13}в строке: {error_msg.lineno} -> {error_msg.line}'
			
			file.write(
				f'{time_str}{status:25}->{'':5}{text}\n{error_msg}\n'
			)
			return

		else:
			error_msg = f'{'':5}Обратитесь к файлу: {error_msg.filename.split("\\")[-1]}\n\
					{'\t' * 13}в функции/переменной или т.п.: {error_msg.name}\n\
					{'\t' * 13}в строке: {error_msg.lineno} -> {error_msg.line}'
			file.write(
				f'{time_str}{status:25}->{error_msg}\n'
			)
			return
	
	file.write(
		f'{time_str}{status:25}->{'':5}{text}\n'
	)


def get_uuid(login: str) -> str:
	query = f"""
			select
			uuid
			from users
			where login='{login}'
			; 
			"""
	cursor.execute(query)

	_uuid = cursor.fetchone()[0]
	return _uuid


def get_data(_uuid: str) -> list[tuple]:
	query = f"""
			select
			surname, name, thurname
			from users
			where uuid='{_uuid}'
			; 
			"""
	cursor.execute(query)

	full_name = ' '.join(list(map(str, cursor.fetchall()[0])))

	query = f"""
			select
			login, password, phone_number
			from users
			where uuid='{_uuid}'
			; 
			"""
	cursor.execute(query)

	dict_data = {
		'Логин': None,
		'Пароль': None,  
		'Телефон': None,
	}

	data = cursor.fetchone()
	for i, key in enumerate(dict_data.keys()):
		dict_data[key] = data[i]

	return full_name, dict_data


def update_user(
		form: werkzeug.datastructures.structures.ImmutableMultiDict,
		session: werkzeug.local.LocalProxy
		) -> None:
	query = f"""
			update users
			set 
			login='{form['Логин']}',
			password='{form['Пароль']}',
			phone_number='{form['Телефон']}'
			where
			uuid='{session['ID']}'
			;
			""" 
	cursor.execute(query)
	write_logs(
		type_status='У',
		text='Данные пользователя обновлены.'
	)


def print_function_name(decorated_function):
	def wrapper_function(*args, **kwargs):
		print('Print from {0}'.format(decorated_function.__name__))
		return decorated_function(*args, **kwargs)

	return wrapper_function


def check_auth(login: str, password: str):
	query = f"""
			select count(*)
			from users
			where
			login='{login}' and password='{password}'
			;
			"""
	cursor.execute(query)
	return cursor.fetchone()[0]


def get_count_home(uuid: str):
	query = f"""
			select count(*)
			from home
			where uuid='{uuid}'
			;
			"""
	cursor.execute(query)
	return cursor.fetchone()[0]


def get_home(uuid: str):
	query = f"""
			select 
			number, region, city, street, home_number, floor_number, entrance_number
			from home
			where uuid='{uuid}'
			order by number
			;
			"""
	cursor.execute(query)
	return cursor.fetchall()


def update_home_(
		form: werkzeug.datastructures.structures.ImmutableMultiDict,
		session: werkzeug.local.LocalProxy
		) -> None:
	
	query = f"""
			update home
			set 
			region='{form['Регион']}',
			city='{form['Город']}',
			street='{form['Улица']}',
			home_number='{form['Номер дома']}',
			floor_number='{form['Номер квартиры']}',
			entrance_number='{form['Номер подъезда']}'
			where
			uuid='{session['ID']}' and number='{form['button']}'
			;
			""" 
	cursor.execute(query)

	write_logs(
		type_status='У',
		text='Данные пользователя обновлены.'
	)


def insert_home_(
		form: werkzeug.datastructures.structures.ImmutableMultiDict,
		session: werkzeug.local.LocalProxy
	):

	query = f"""
			insert into
			home
			values (
				'{session['ID']}',
				'{get_count_home(session['ID']) + 1}',
				'{form['Регион']}',
				'{form['Город']}',
				'{form['Улица']}',
				'{form['Номер дома']}',
				'{form['Номер квартиры']}',
				'{form['Номер подъезда']}'
			)
			;
			"""
	cursor.execute(query)

	#print(query)
	write_logs(
		type_status='У',
		text='Данные новой квартиры добавлены.'
	)


def get_count_home(uuid: str):
	query = f"""
			select count(*)
			from home
			where uuid='{uuid}'
			;
			"""
	cursor.execute(query)
	[count] = cursor.fetchone()
	return count



def delete_home_(uuid: str, home_number: str):
	query = f"""
			delete from
			home
			where
			uuid='{uuid}' and number='{home_number}'
			;
			"""
	cursor.execute(query)


def insert_service(uuid: str, form):
	query = f"""
			insert into
			services
			values (
			'{uuid}',
			"""
	
	for i, key in enumerate(form):
		if form[key] == '':
			query += """'Отсутствует',\n"""
		else:
			if i == len(form) - 1:
				query += f"""'{form[key]}')\n;"""
			else:
				query += f"""'{form[key]}',\n"""
	
	cursor.execute(query)


def check_service(uuid: str):
	query = f"""
			select count(*)
			from
			services
			where
			uuid='{uuid}'
			;"""

	cursor.execute(query)
	return cursor.fetchone()[0] > 0



def info_service(uuid: str):
	query = f"""
			select
			service, comment, date, time, employee, status
			from
			services
			where
			uuid='{uuid}'
			order by date
			;
			"""

	cursor.execute(query)
	
	return cursor.fetchall()

def info_service2(uuid: str):
	query = f"""
			select
			*
			from
			services
			where
			uuid='{uuid}'
			order by date
			;
			"""

	cursor.execute(query)
	
	return cursor.fetchall()


def get_status(uuid: str):
	query = f"""
			select status
			from
			users
			where
			uuid='{uuid}'
			;
			"""
	cursor.execute(query)
	return cursor.fetchone()[0]



def admin_service():
	query = """
			select distinct uuid 
			from
			users
			where
			status!='Работник' and status!='Администратор'
			;
			"""
	
	cursor.execute(query)

	uuids = cursor.fetchall()
	data = []
	for uuid in uuids:
		info = info_service2(uuid[0])

		if len(info) > 1:
			for j in range(len(info)):
				data += [info[j]]
		else:
			data += [info[0]]
	
	return data

def admin_info_service():
	query = f"""
			select count(*)
			from
			services
			;"""

	cursor.execute(query)
	return cursor.fetchone()[0] > 0



def get_employees():
	query = """
			select 
			name, surname, thurname, profession
			from
			employees
			where status='Работник'
			;
			"""

	cursor.execute(query)
	return cursor.fetchall()


def update_employees(form):
	for key in form:
		if form[key] == 'Выбрать работника':
			continue
		
		else:
			query = f"""update services
					set
					employee='{form[key]}'
					where
					uuid='{key}'
					;
					"""
			cursor.execute(query)


def update_status(form):
	for key in form:
		if form[key] == 'Ожидание':
			continue
		
		else:
			query = f"""update services
					set
					status='{form[key]}'
					where
					uuid='{key}'
					;
					"""
			cursor.execute(query)
