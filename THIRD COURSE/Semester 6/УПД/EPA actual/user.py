from utilits import *

user = Blueprint('user', __name__)


@user.route('/')
def home_page():
	try:
		if 'AUTH_STATUS' in session:

			session['STATUS'] = get_status(session['ID'])
			print(session)

			return render_template(
				'user/home_page.html',
				auth_status=session,
				status=session['STATUS']
			)
		
		else:
			ip, port = request.host.split(':')
			session['IP'] = ip
			session['PORT'] = port
			session['ID'] = str(uuid.uuid4())

			print(session)

			return render_template(
				'user/home_page.html'
			)
	
	except Exception as error:
		write_logs(
			type_status='О',
			error_msg=error
		)
		return render_template(
			'user/home_page.html',
			auth_status=session
		)


@user.route('/registration', methods=['POST', 'GET'])
def registration():
	try:
		if 'AUTH_STATUS' in session:
			write_logs(
				type_status='П',
				text=f'Попытка воспользоваться регистрацией в онлайн-статусе.',
			)
			return redirect('/')
		
		print(session)
		if request.method == 'POST':
			login = request.form['login']
			if check_user(login):
				write_logs(
					type_status='П',
					text=f'Данный пользователь с login: {login} уже существует.',
				)
				return render_template('user/reg.html')
			
			new_user(request.form, session)
			write_logs(
				type_status='У',
				text='Новый пользователь зарегистрирован.',
			)

			session['AUTH_STATUS'] = True
			return redirect('/')

		return render_template('user/reg.html')
	
	except Exception as error:
		write_logs(
			type_status='О',
			text='Возникли трудности при регистрации.',
			error_msg=error
		)
		return render_template('user/reg.html')


@user.route('/authorization', methods=['POST', 'GET'])
def auth():
	try:
		if 'AUTH_STATUS' in session:
			write_logs(
				type_status='П',
				text=f'Попытка воспользоваться регистрацией в онлайн-статусе.',
			)
			return redirect('/')
		
		if request.method == 'POST':
			login = request.form['login']
			if not check_user(login):
				write_logs(
					type_status='П',
					text=f'Данный пользователь с login: {login} не существует. Введите логин еще раз.',
				)
				return render_template('user/auth.html')
			
			password = request.form['password']
			if not check_auth(login, password):
				write_logs(
					type_status='П',
					text=f'Введен неверный логин или пароль. Попробуйте еще раз.',
				)
				return render_template('user/auth.html')
			
			session['AUTH_STATUS'] = True
			session['ID'] = get_uuid(login)

			write_logs(
				type_status='У',
				text=f'Прошла авторизация.',
			)
			return redirect('/')
			
		return render_template('user/auth.html')
	
	except Exception as error:
		write_logs(
			type_status='О',
			text='Возникли трудности при авторизации.',
			error_msg=error
		)
		return render_template('user/auth.html')


@user.route('/profile', methods=['POST', 'GET'])
def profile():
	try:
		if 'AUTH_STATUS' not in session:
			return redirect('/')

		
		full_name, data = get_data(session['ID'])
		home = get_home(session['ID'])
		n = get_count_home(session['ID'])
		return render_template(
			'user/profile.html',
			full_name=full_name,
			data=data,
			list_home=list_home,
			home=home,
			n=n
		)
	
	except Exception as error:
		write_logs(
			type_status='О',
			error_msg=error
		)
		return render_template('user/profile.html')


@user.route('/services', methods=['POST', 'GET'])
def services():
	try:
		if request.method == 'POST':
			if 'AUTH_STATUS' not in session:
				return redirect('/services')

			insert_service(session['ID'], request.form)
			
		return render_template(
			'user/service.html',
			auth_status=session,
			list_service=list_service
		)
	
	except Exception as error:
		print(error)
		return render_template('user/service.html')


@user.route('/admin_call')
def admin_call():
	return {
		'page': 'Admin call page'
	}


@user.route('/logout')
def logout():
	try:
		del session['AUTH_STATUS']
		del session['STATUS']
		write_logs(
			type_status='У',
			text='Выход из аккаунта.'
		)

		return redirect('/')
	
	except Exception as error:
		write_logs(
			type_status='О',
			error_msg=error
		)
		return redirect('/')



@user.route('/update_profile', methods=['POST', 'GET'])
def update_profile():
	try:
		if 'AUTH_STATUS' not in session:
			return redirect('/')
		

		if request.method == 'POST':
			update_user(request.form, session)
			return redirect('/profile')
		
		full_name, data = get_data(session['ID'])
		home = get_home(session['ID'])
		n = get_count_home(session['ID'])
		return render_template(
			'user/profile.html',
			full_name=full_name,
			data=data,
			list_home=list_home,
			flag=True,
			home=home,
			n=n
		)
		
	
	except Exception as error:
		write_logs(
			type_status='О',
			error_msg=error
		)
		return render_template('user/profile.html')
	

@user.route('/update_home', methods=['POST', 'GET'])
def update_home():
	try:
		if 'AUTH_STATUS' not in session:
			return redirect('/')

		if request.method == 'POST':
			update_home_(request.form, session)
			return redirect('/profile')

		full_name, data = get_data(session['ID'])
		home = get_home(session['ID'])
		n = get_count_home(session['ID'])
		return render_template(
			'user/profile.html',
			full_name=full_name,
			data=data,
			list_home=list_home,
			home=home,
			n=n,
			flag_home=True
		)
	
	except Exception as error:
		write_logs(
			type_status='О',
			error_msg=error
		)
		return redirect('/profile')
	


@user.route('/insert_home', methods=['POST', 'GET'])
def insert_home():
	try:
		if 'AUTH_STATUS' not in session:
			return redirect('/')
		
		if request.method == 'POST':
			insert_home_(request.form, session)
			return redirect('/profile')
		return render_template(
			'user/home.html',
			list_home=list_home
		)
	
	except Exception as error:
		write_logs(
			type_status='О',
			error_msg=error
		)
		return redirect('/profile')
	

@user.route('/delete_home', methods=['POST', 'GET'])
def delete_home():
	try:
		delete_home_(session['ID'], request.form['number'])
		return redirect('/profile')
	except Exception as error:
		write_logs(
			type_status='О',
			error_msg=error
		)
		return redirect('/profile')
	


@user.route('/show_service', methods=['POST', 'GET'])
def show_service():
	try:
		if 'AUTH_STATUS' not in session:
			return redirect('/')
		
		if check_service(session['ID']):

			info = info_service(session['ID'])
			return render_template(
				'user/show_service.html',
				flag=True,
				info=info,
				name=list_show_service
			)
		else:
			return render_template('user/show_service.html')
	except Exception as error:
		write_logs(
			type_status='О',
			error_msg=error
		)
		return redirect('/profile')
	