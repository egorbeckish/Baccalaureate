from library import *

app = Flask(__name__)

@app.route('/')
def home():
	return render_template(
		'home.html'
	)

@app.route('/money', methods=['GET', 'POST'])
def money():
	if request.method == 'POST':
		
		input_rate = request.form['input_rate']
		output_rate = request.form['output_rate']
		kof = all_exachange_rate[input_rate][output_rate]
		result = f"""{float(request.form['money']) * kof:.3f}"""

		a = {
			'input_rate': input_rate,
			'output_rate': output_rate,
			'kof': kof,
			'result': result
		}
		
		print(json.loads(json.dumps(a)))

		return render_template(
			'money.html',
			list_exchange_rate=list_exchange_rate,
			result=result
		)
	
	return render_template(
		'money.html',
		list_exchange_rate=list_exchange_rate
	)


@app.route('/cu', methods=['GET', 'POST'])
def cu():
	if request.method == 'POST':
		
		input_rate = request.form['input_rate']
		output_rate = request.form['output_rate']
		kof = all_dict_measurements[input_rate][output_rate]
		result = f"""{float(request.form['value']) * kof:.3f}"""

		a = {
			'input_rate': input_rate,
			'output_rate': output_rate,
			'kof': kof,
			'result': result
		}
		
		print(json.loads(json.dumps(a)))

		return render_template(
			'cu.html',
			list_measurements=list_measurements,
			result=result
		)
	
	return render_template(
		'cu.html',
		list_measurements=list_measurements
	)
