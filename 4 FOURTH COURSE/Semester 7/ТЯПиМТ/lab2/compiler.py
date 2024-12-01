import streamlit as st
from main import *
import time

st.set_page_config(
	layout='centered'
)

st.title(
	'Компилятор(частичный) С++'
)

st.code(
	"""
\s*
(
	int(?:\s+long|\s+short)?|
	double(?:\s+long)?|
	long(?:\s+int|\s+double)?|
	short(?:\s+int)?|
	float|
	char
)
\s+
(
	(?:
		(?<id>
			[_a-zA-Z][_a-zA-Z0-9]*
		)

		(?:
			\s*\[
				\s*
				[1-9]\d*
			\]
			\s*
		)*
	)
	\s*
	(
		,
		(?=
			\s*
			[_a-zA-Z]
		)|
		;
	)
	\s*
)*
	"""
)


text = st.text_area(
	'Окно вводимого кода',
	height=200,
)

compiler = st.button('Скомпилировать')
if compiler and text:
	file_regex = regex.compile(open('reg.txt').read())
	container = set()
	attempt = analyze_syntax(file_regex, text, container)
	
	with st.spinner('Идет компиляция, пожалуйста, подождите...'):
			time.sleep(5)
	if attempt == True:
		success = st.success('Код успешно скомпилирован', icon='✅')
		time.sleep(10)
		success.empty()
	
	else:
		error = st.error(attempt, icon='❌')
		#time.sleep(10)
		#error.empty()