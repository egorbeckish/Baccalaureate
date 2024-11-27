import streamlit as st
from main import *
import time

st.set_page_config(
	layout='centered'
)

st.title(
	'Компилятор(частичный) С++'
)


col = st.columns([1, 1])
with col[0]:
	st.image(
		'граф переходов.png',
		'Граф переходов',
	)

with col[1]:
	st.write(
		'Таблица функций перехода'
	)

	st.dataframe(
		func_transition('func_transition.xlsx'),
		width=800,
		height=680
	)

text = st.text_area(
	'Окно вводимого кода',
	height=200,
)

compiler = st.button('Скомпилировать')
if compiler and text:
	table_func_transition = func_transition('func_transition.xlsx')
	__header = header(table_func_transition)
	print('\n' * 50)
	print(__header)

	attempt = analyze_syntax(text, __header, table_func_transition)
	
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