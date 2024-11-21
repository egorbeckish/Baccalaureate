from flask import Flask, Blueprint
from flask_restplus import Api, Resource, fields, reqparse
from werkzeug.wrappers import Request, Response
from collections.abc import MutableMapping
from collections import MutableMapping, OrderedDict
from collections.abc import MutableMapping
from collections import OrderedDict
from random import random

from collections import abc
import collections as abc
from babel._compat import pickle, string_types, abc
from flask_restplus import Api, Resource, fields, reqparse

app = Flask(__name__)
api = Api(app = app)

# описание главного блока нашего API http://127.0.0.1:5000/main/.
name_space = api.namespace('main', description = 'Main APIs')

@name_space.route("/")
class MainClass(Resource):
	
	def get(self):
		return {'status' : 'Got new data'}

	def post(self):
		return {'status' : 'Posted new data'}

# data
list_ = api.model('list',
	{
		'id' : fields.Integer(required = True, description = 'id film'),
		'author' : fields.String(required = True, description = 'author film'),
		'name' : fields.String(required = True, description = 'name film'),
		'time' : fields.Float(required = True, description = 'time film'),
		'score' : fields.Float(required = True, description = 'score film'),
		'array' : fields.List(fields.Raw, required = True, description = 'array film')
	})


# data in operation memory
ls = [
	{
		'id' : 0,
		'author' : 'Christopher Nolan',
		'name' : 'Interstellar',
		'time' : 169,
		'score' : 8.601
	}]

universal_id = int(0)
all_array = li
name_space1 = api.namespace('list', description = 'list APIs')

@name_space1.route('/')
class ListClass(Resource):
	
	@name_space.doc("")
	@name_space1.marshal_with(list_)

	def get(self):
		#get array
		return {'array' : ls}

	@name_space1.doc("")
	@name_space1.expect(list_)
	@name_space1.marshal_with(list_)

	def put(self):
		global all_array
		film = {
			'id' : api.payload['id'],
			'author' : api.payload['author'],
			'name' : api.payload['name'],
			'time' : api.payload['time'],
			'score' : api.payload['score'],
		}

		ls.append(film)

		return {'array' : ls}

sort_sc = api.model('list', {
		fields.List(fields.Raw, required = True, description = 'all_array')
	})


@name_space1.route('/getsortScore')
class getsortScore(Resource):
	
	@name_space1.doc("")
	@name_space1.marshal_with(sort_sc)

	def get(self):
		# get sort for a score
		global ls
		sort_ = sorted(ls, key = lambda film : film['score'])

		return {'array' : sort_}


@name_space1.route('/getsortTime')
class getsortTime(Resource):
	
	@name_space1.doc("")
	@name_space1.marshal_with(sort_sc)

	def get(self):
		# get sort for a time
		global ls
		time_ = sorted(ls, key = lambda film : film['time'])

		return {'array' : time_}


@name_space1.route('/getsortAuthor')
class getsortAuthor(Resource):
	
	@name_space1.doc("")
	@name_space1.marshal_with(sort_sc)

	def get(self):
		# get sort for a author
		global ls
		author_ = sorted(ls, key = lambda film : film['author'])

		return {'array' : author_}


@name_space1.route('/getsortName')
class getsortName(Resource):
	
	@name_space1.doc("")
	@name_space1.marshal_with(sort_sc)

	def get(self):
		# get sort for a name
		global ls
		name_ = sorted(ls, key = lambda film : film['name'])

		return {'array' : name_}


@name_space1.route('/getsortId')
class getsortId(Resource):
	
	@name_space1.doc("")
	@name_space1.marshal_with(sort_sc)

	def get(self):
		# get sort for a id
		global ls
		id_ = sorted(ls, key = lambda film : film['id'])

		return {'array' : id_}



one_value = api.model('one', {'value' : fields.String}, required = True, description = 'one value')






@name_space1.route('/getmaxScore')
class getmaxScore(Resource):

	@name_space1.doc("")
	@name_space1.marshal_with(one_value)

	def get(self):
		# get max point for a score
		global ls
		maxim = max([film['score'] for film in ls])

		return {'value' : maxim}



@name_space1.route('/getmaxTime')
class getmaxTime(Resource):

	@name_space1.doc("")
	@name_space1.marshal_with(one_value)

	def get(self):
		# get max point for a time
		global ls
		maxim = max([film['time'] for film in ls])

		return {'value' : maxim}



@name_space1.route('/getminScore')
class getminScore(Resource):

	@name_space1.doc("")
	@name_space1.marshal_with(one_value)

	def get(self):
		# get min point for a score
		global ls
		minim = min([film['score'] for film in ls])

		return {'value' : minim}



@name_space1.route('/getminTime')
class getminTime(Resource):

	@name_space1.doc("")
	@name_space1.marshal_with(one_value)

	def get(self):
		# get min point for a time
		global ls
		maxim = min([film['time'] for film in ls])

		return {'value' : minim}



@name_space1.route('/getmiddleScore')
class getmiddleScore(Resource):

	@name_space1.doc("")
	@name_space1.marshal_with(one_value)

	def get(self):
		# get middle point for a score
		global ls
		middle = sum([film['score'] for film in ls]) / len(ls)

		return {'value' : middle}




@name_space1.route('/getmiddleTime')
class getmiddleTime(Resource):

	@name_space1.doc("")
	@name_space1.marshal_with(one_value)

	def get(self):
		# get middle point for a time
		global ls
		middle = sum([film['time'] for film in ls]) / len(ls)

		return {'value' : middle}


api.add_namespace(name_space1)


req = reqparse.RequestParser()
req.add_argument('id', type = int, required = False)




@name_space1.route('/modificationfilm')
class ModificationFilm(Resource):

	@name_space1.doc('')
	@name_space1.expect(req)
	@name_space1.marshal_with(list_)


	def delete(self):

		global ls
		# delete film for a id
		args = req.parse_args()
		ls = [film for film in ls if film['id'] != args['id']]

		return {'array' : ls}


	@name_space1.doc('')
	@name_space1.expect(req)
	@name_space1.marshal_with(list_)


	def patch(self):

		global ls
		# Change film for a id
		for film in ls:
			if api.payload['id'] == film['id']:
				film['author'] = api.payload['author']
				film['name'] = api.payload['name']
				film['time'] = api.payload['time']
				film['score'] = api.payload['score']

				return {'array' : ls}


		film = {
			'id' : api.payload['id'],
			'author' : api.payload['author'],
			'name' : api.payload['name'],
			'time' : api.payload['time'],
			'score' : api.payload['score'],
		}

		ls.append(film)

		return ls


if __name__ == '__main__':
	app.run()
