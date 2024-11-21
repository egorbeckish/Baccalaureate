from flask import Flask, jsonify, Blueprint
from flasgger import Swagger
# Подключение части нашего веб-сервиса с использованием Blueprint
from sitepart.sitepart import sitepart


# Приложение Flask
app = Flask(__name__)
# Инициализация для нашего API сервиса документации Swagger
swagger = Swagger(app)
# Создаем основной Blueprint сайта
main = Blueprint("/", __name__, template_folder =' templates', static_folder = 'static')
# объявляем декоратор для метода http get
# Информация, которая будет выдаваться по URL/info/something
# Параметр в <> при вводе URL будет передан в переменную about функции info


@main.route('/info/<about>/')
def info(about):

	"""Example endpoint returning about info
	This is using docstrings for specifications.
	---
	parameters:
	- name: about
	in: path
	type: string
	enum: ['all','version', 'author', 'year']
	required: true
	default: all

	definitions:
	About:
	type: string

	responses:
	200:
	description: A string
	schema:
	$ref: '#/definitions/About'
	examples:
	version: '1.0'
	"""


	all_info = {

		'all' : 'main_author 1.0 2020',
		'version' : '1.0',
		'author' : 'main_author',
		'year' : '2020'
	}

	return jsonify({'about' : all_info[about]})

# Регистрируем основной Blueprint и Blueprint другой части сайта
app.register_blueprint(main, url_prefix = '/')
# url_prefix указывает URL в контексте которого будет доступна часть данного Blueprint
app.register_blueprint(sitepart, url_prefix = '/sitepart')


# Запуск приложения Flask в режиме debug
app.run(debug = True)
