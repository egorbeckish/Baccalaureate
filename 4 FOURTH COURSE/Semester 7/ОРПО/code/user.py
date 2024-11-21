from flask import Flask, render_template, request, redirect

app = Flask(__name__)

@app.route('/reg')
def reg():
	return render_template('registration.html')

@app.route('/auth')
def auth():
	return render_template('authorization.html')