from flask import Flask, render_template, request
from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField
import requests
app = Flask(__name__)




@app.route('/login', methods=['POST', 'GET'])
def login():
    
    error = None
    if request.method == 'POST':
        if valid_login(request.form['username'], request.form['password']):
            return log_the_user_in(request.form['username'])
        else:
            error = 'Invalid username/password'
    # the code below is executed if the request method
    # was GET or the credentials were invalid
    return render_template('login.html', error = error)


def do_the_login():
    return 'Do Login'

def show_the_login_form():
    return 'Show Form'

@app.route('/login2', methods=['GET', 'POST'])
def login2():
    if request.method == 'POST':
        return do_the_login()
    else:
        return show_the_login_form()


@app.route('/')
def hello_world():
    return 'Hello World!'




@app.route('/')
@app.route('/home')
def home():
    return render_template('home.html')


@app.route('/login_main')
def login_main():
    return render_template('login.html')



@app.route('/data_to')
def data_to():

    some_pars = {'user':'Egor','color':'purple'}
    some_str = 'Hello my dear friends!'
    some_value = 18
    #передаем данные в шаблон и вызываем его
    return render_template('simple.html', some_str = some_str, some_value = some_value, some_pars = some_pars)


# модули работы с формами и полями в формах
from flask_wtf import FlaskForm,RecaptchaField
from wtforms import StringField, SubmitField, TextAreaField

# модули валидации полей формы
from wtforms.validators import DataRequired
from flask_wtf.file import FileField, FileAllowed, FileRequired

# используем csrf токен, можете генерировать его сами
SECRET_KEY = '123'
app.config['SECRET_KEY'] = SECRET_KEY

# используем капчу и полученные секретные ключи с сайта Google
app.config['RECAPTCHA_USE_SSL'] = False
app.config['RECAPTCHA_PUBLIC_KEY'] = '6Lds6p8fAAAAAL237IIpbjjnAfHlG6gfdA5TyNXV'
app.config['RECAPTCHA_PRIVATE_KEY'] = '6Lds6p8fAAAAALdP59uKoDTWI-M1TGvwkyDAXEeG'
app.config['RECAPTCHA_OPTIONS'] = {'theme': 'white'}

# обязательно добавить для работы со стандартными шаблонами
from flask_bootstrap import Bootstrap
bootstrap = Bootstrap(app)




class NetForm(FlaskForm):
    # поле для введения строки, валидируется наличием данных
    # валидатор проверяет введение данных после нажатия кнопки submit
    # и указывает пользователю ввести данные, если они не введены
    # или неверны
    openid = StringField('openid', validators = [DataRequired()])
    # поле загрузки файла
    # здесь валидатор укажет ввести правильные файлы
    upload = FileField('Load image', validators = [FileRequired(), FileAllowed(['jpg', 'png', 'jpeg'], 'Images only!')])
    # поле формы с capture
    recaptcha = RecaptchaField()
    #кнопка submit, для пользователя отображена как send
    submit = SubmitField('send')



# функция обработки запросов на адрес 127.0.0.1:5000/net
# модуль проверки и преобразование имени файла
# для устранения в имени символов типа / и т.д.
from werkzeug.utils import secure_filename
import os

# подключаем наш модуль и переименовываем
# для исключения конфликта имен
import net as neuronet


# # метод обработки запроса GET и POST от клиента
@app.route("/net", methods = ['GET', 'POST'])
def net():
    # создаем объект формы
    form = NetForm()
    # обнуляем переменные, передаваемые в форму
    filename = None
    neurodic = {}
    
    # проверяем нажатие сабмит и валидацию введенных данных
    if form.validate_on_submit():
        # файлы с изображениями читаются из каталога static
        filename = os.path.join('./photo', secure_filename(form.upload.data.filename))
        fcount, fimage = neuronet.read_image_files(10,'./photo')
        # передаем все изображения в каталоге на классификацию
        # можете изменить немного код и передать только загруженный файл
        decode = neuronet.getresult(fimage)
    
        # записываем в словарь данные классификации
        for elem in decode:
            neurodic[elem[0][1]] = elem[0][2]
        # сохраняем загруженный файл
        form.upload.data.save(filename)
        # передаем форму в шаблон, так же передаем имя файла и результат работы нейронной
        # сети, если был нажат сабмит, либо передадим falsy значения
    return render_template('net.html', form = form, image_name = filename, neurodic = neurodic)





from flask import request
from flask import Response
import base64
from PIL import Image
from io import BytesIO
import json



# метод для обработки запроса от пользователя
@app.route("/apinet", methods = ['GET', 'POST'])
def apinet():

    neurodic = {}
    # проверяем, что в запросе json данные
    if request.mimetype == 'application/json':
        # получаем json данные
        data = request.get_json()
        # берем содержимое по ключу, где хранится файл
        # закодированный строкой base64
        # декодируем строку в массив байт, используя кодировку utf-8
        # первые 128 байт ascii и utf-8 совпадают, потому можно
        filebytes = data['imagebin'].encode('utf-8')
        # декодируем массив байт base64 в исходный файл изображение
        cfile = base64.b64decode(filebytes)
        # чтобы считать изображение как файл из памяти, используем BytesIO
        img = Image.open(BytesIO(cfile))
        decode = neuronet.getresult([img])
        neurodic = {}
        for elem in decode:
            neurodic[elem[0][1]] = str(elem[0][2])
            print(elem)
        # пример сохранения переданного файла
        handle = open('./photo/copy.png','wb')
        handle.write(cfile)
        handle.close()
    
    # преобразуем словарь в json-строку
    ret = json.dumps(neurodic)
    # готовим ответ пользователю
    resp = Response(response = ret, status = 200, mimetype = "application/json")
    # возвращаем ответ
    return resp




import lxml.etree as ET
@app.route("/apixml",methods=['GET', 'POST'])
def apixml():
    #парсим xml файл в dom
    dom = ET.parse("./xml/file.xml")
    #парсим шаблон в dom
    xslt = ET.parse("./xml/file.xslt")
    #получаем трансформер
    transform = ET.XSLT(xslt)
    #преобразуем xml с помощью трансформера xslt
    newhtml = transform(dom)
    #преобразуем из памяти dom в строку, возможно, понадобится указать кодировку
    strfile = ET.tostring(newhtml)
    return strfile





if __name__ == '__main__':
    app.run(debug = True)
