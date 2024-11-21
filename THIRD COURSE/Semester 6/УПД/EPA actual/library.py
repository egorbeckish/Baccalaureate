from flask import Flask, Blueprint, render_template, session, request, redirect
import psycopg2 as psql
import uuid
import traceback
from prettytable import from_db_cursor
import werkzeug
import time

connect = psql.connect(
	dbname='epa',
	user='postgres',
	password='123'
)

connect.autocommit = True
cursor = connect.cursor()


dict_error_logs = {
	'У': 'SUCCESS',
	'О': 'ERROR',
	'П': 'WARNING'
}

list_home = ['Регион', 'Город', 'Улица', 'Номер дома', 'Номер квартиры', 'Номер подъезда']
list_service = ['Пломбирование счетчиков', 'Уборка подъезда', 'Водоснабжение', 'Отопление']
list_show_service = ['Услуга:', 'Комментарий:', 'Дата:', 'Время:', 'Работник:', 'Статус:']
list_status = ['В работе', 'Выполнено']

dict_employees = {
	'Пломбирование счетчиков': ['Иванов И.И.', 'Михайлов М.М.'],
	'Уборка подъезда': ['Федоров Ф.Ф.', 'Егоров Е.Е.'],
	'Водоснобжение': ['Алексее А.А.', 'Андреев А.А.'],
	'Отопление': ['Романов Р.Р.', 'Максимов М.М.']
}