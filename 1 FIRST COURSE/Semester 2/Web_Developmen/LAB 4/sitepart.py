from flask import Blueprint,jsonify


# Создаем Blueprint для отдельной части веб API
sitepart = Blueprint("sitepart", __name__, template_folder = 'templates', static_folder = 'static')
# Возвращает цветовую палитру по имени палитры (rgb, cmyk ...)
@sitepart.route('/colors/<palette>/')
def colors(palette):


	"""Example endpoint returning a list of colors by palette
	This is using docstrings for specifications.
	---
	parameters:
	- name: palette
	in: path
	type: string
	enum: ['all', 'rgb', 'cmyk']
	required: true
	default: all

	definitions:
	Palette:
	type: object
	properties:
	palette_name:
	type: array
	items:
	$ref: '#/definitions/Color'
	Color:
	type: string

	responses:
	200:
	description: A list of colors (may be filtered by palette)
	schema:
	$ref: '#/definitions/Palette'
	examples:
	rgb: ['red', 'green', 'blue']
	"""

	
	all_colors = {
		'cmyk': ['cian', 'magenta', 'yellow', 'black'],
		'rgb': ['red', 'green', 'blue']
	}
	# что возвратить, если URL all
	if palette == 'all':
		result = all_colors
	else:
		# возврат в зависимости от имени палитры
		result = {palette: all_colors.get(palette)}
	
	# преобразуем словарь в json строку и возвращаем ее
	return jsonify(result)
