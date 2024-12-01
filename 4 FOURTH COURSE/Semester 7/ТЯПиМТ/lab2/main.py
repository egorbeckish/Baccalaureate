import regex

file_regex = regex.compile(open('reg.txt').read())

def analyze_syntax(file_regex, syntax, c):
	for a in regex.finditer(file_regex, syntax, partial=True):
		__ids = a.capturesdict()['id']

		if __ids:
			for __id in __ids:
				if __id in c or __id in ['int', 'float', 'double', 'char', 'long', 'short']:
					return f'{__id=}\t{c=}'

				c.add(__id)

	return True