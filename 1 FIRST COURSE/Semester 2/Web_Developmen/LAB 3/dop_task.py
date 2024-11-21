from flask import Flask
from PIL import Image
from flask import render_template, request
from werkzeug.utils import secure_filename
from flask_wtf import FlaskForm, RecaptchaField
from wtforms import StringField, SubmitField, TextAreaField
from wtforms.validators import DataRequired
from flask import Flask, render_template, request
from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, SubmitField
import requests
# модули работы с формами и полями в формах
from flask_wtf import FlaskForm,RecaptchaField
from wtforms import StringField, SubmitField, TextAreaField

# модули валидации полей формы
from flask_colorpicker import colorpicker
from wtforms.validators import DataRequired
from wtforms.validators import AnyOf
from flask_wtf.file import FileField, FileAllowed, FileRequired


app = Flask(__name__)

app.config['SECRET_KEY'] = "123"

# ключи recaptcha от google
app.config['RECAPTCHA_USE_SSL'] = False
app.config['RECAPTCHA_PUBLIC_KEY'] = "6Lds6p8fAAAAAL237IIpbjjnAfHlG6gfdA5TyNXV"
app.config['RECAPTCHA_PRIVATE_KEY'] = "6Lds6p8fAAAAALdP59uKoDTWI-M1TGvwkyDAXEeG"
app.config['RECAPTCHA_OPTIONS'] = {'theme': 'white'}

@app.route('/')
@app.route('/home')
def home():
    return '<h1>Hello</h1>'


from flask_bootstrap import Bootstrap
bootstrap = Bootstrap(app)


colorpicker(app)

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
    red = StringField(('Change red'), validators = [DataRequired()])
    green = StringField(('Change green'), validators = [DataRequired()])
    blue = StringField(('Change blue'), validators = [DataRequired()])
    #кнопка submit, для пользователя отображена как send
    submit = SubmitField('send')

from werkzeug.utils import secure_filename
import os
import numpy as np
from flask import request
from flask import Response
import base64
from PIL import Image
from io import BytesIO
import json
from skimage import io
import matplotlib
import matplotlib.pyplot as plt
import seaborn as sns


def draw(filename, red, green, blue):

	img = Image.open(filename)
	height = 224
	width = 224
	img = np.array(img.resize((height, width))) / 255.0

	_ = plt.hist(image.ravel(), bins=256, color='orange', )
	_ = plt.hist(image[:, :, 0].ravel(), bins=256, color='Red', alpha = 0.5)
	_ = plt.hist(image[:, :, 1].ravel(), bins=256, color='Green', alpha = 0.5)
	_ = plt.hist(image[:, :, 2].ravel(), bins=256, color='Blue', alpha = 0.5)
	_ = plt.xlabel('Intensity Value')
	_ = plt.ylabel('Count')
	_ = plt.legend(['Total', 'Red Channel', 'Green Channel', 'Blue Channel'])
	# plt.savefig(root)


	plt_img2 = np.zeros((224, 20, 3))
	plt_img2[:, 0, :] = (np.average(img, (0))).astype(np.float)
	for i in range(1, 19):
		plt_img[:, i, :] = plt_img[:, 0, :]
	plt_img2 = Image.fromarray((plt_img2 * 255).astype(np.uint8))


	plt_img2 = np.zeros((20, 224, 3))
	plt_img2[0, :, :] = (np.average(img, (1))).astype(np.float)
	for i in range(1, 19):
		plt_img[i, :, :] = plt_img[0, :, :]
	plt_img = Image.fromarray((plt_img2 * 255).astype(np.uint8))


	
	path = './static/newgr.png'
	plt.savefig(path)
	plt.close()
	new_path = './static/horizgr.png'
	plt_img.savefig(new_path)
	last_path = './static/vertgr.png'
	plt_img2.savefig(last_path)

	result = np.zeros((224, 224, 3))

	red = red[4:-1]
	redlist = red.split(',')
	list(map(float, redlist))
	redlist = np.array(redlist).astype('float')/255.0

	result[:, :, 0] = img[:, :, 0] * redlist[0]
	result[:, :, 1] = img[:, :, 1] * redlist[1]
	result[:, :, 2] = img[:, :, 2] * redlist[2]


	green = red[4:-1]
	greenlist = green.split(',')
	list(map(float, greenlist))
	greenlist = np.array(greenlist).astype('float')/255.0

	result[:, :, 0] += img[:, :, 0] * greenlist[0]
	result[:, :, 1] += img[:, :, 1] * greenlist[1]
	result[:, :, 2] += img[:, :, 2] * greenlist[2]


	blue = red[4:-1]
	bluelist = blue.split(',')
	list(map(float, bluelist))
	bluelist = np.array(bluelist).astype('float')/255.0

	result[:, :, 0] += img[:, :, 0] * bluelist[0]
	result[:, :, 1] += img[:, :, 1] * bluelist[1]
	result[:, :, 2] += img[:, :, 2] * bluelist[2]


	result[1.0 < result] = 1.0
	print(result)

	result = Image.fromarray((result * 255).astype(np.uint8))

	start_path = './static/new.png'
	img = Image.fromarray((img * 255).astype(np.uint8))
	finish_path = './static/old.png'
	img.save(finish_path)
	result.save(start_path)

	return new_path, path, last_path, finish_path, start_path


@app.route("/net", methods = ['GET', 'POST'])
def net():
    # создаем объект формы
    form = NetForm(meta = {'csrf' : False})
    # обнуляем переменные, передаваемые в форму
    filename = None
    newfilename = None
    grname = None
    oldimgname = None
    vertgr_name = None
    horizgr_name = None
    # neurodic = {}
    
    # проверяем нажатие сабмит и валидацию введенных данных
    if form.validate_on_submit():
        # файлы с изображениями читаются из каталога static
        filename = os.path.join('./static', secure_filename(form.upload.data.filename))
        # fcount, fimage = neuronet.read_image_files(10,'./photo')
        red = form.red.data
        green = form.green.data
        blue = form.blue.data
        form.upload.data.save(filename)
        newfilename, grname, oldimgname, vertgr_name, horizgr_name = draw(filename, red, green, blue)


    return render_template('new_net.html', form = form, image_name = newfilename, gr_name = grname, 
    	old_img =  oldimgname, vertgr = vertgr_name, horizgr = horizgr_name)

	
if __name__ == "__main__":
	app.run(debug = True)
