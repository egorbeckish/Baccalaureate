from library import *


def del_space(document: list) -> list:
	while '' in document:
		document.pop(document.index(''))

	return document