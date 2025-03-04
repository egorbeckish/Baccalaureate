from utils import *


class TFIDF:

	def __init__(self, path: str, t: str) -> None:
		self.__path: str = path
		self.__documents = [doc for doc in os.listdir(self.__path) if os.path.isfile(fr"{self.__path}\{doc}")]
		self.__t: list = ' '.join(re.split(r"[\s\.\,\!\?()«»\-]", t)).lower().split()
		self.__D: int = len(self.__documents)


	@property
	def __tf(self) -> dict:
		tf: dict = dict()

		for document in self.__documents:
			with open(fr"{self.__path}\{document}", encoding="utf-8") as file:
				file: list = ' '.join(del_space(re.split(r"[\s\.\,\!\?()«»\-]", file.read()))).lower().split()
				all_words: int = len(file)
				clear_document: str = ' '.join(file)

			tf[document]: dict = dict()
			for t in self.__t:
				n_t: int = len(re.findall(fr"{t}[а-я]*", clear_document))
				tf[document][t] = n_t / all_words
		
		return tf

	@property
	def __idf(self) -> dict:
		idf: dict = dict()

		for t in self.__t:
			counter_documents = 0
			for document in self.__documents:
				if self.tf[document][t]:
					counter_documents += 1
			
			idf[t] = log(self.__D / counter_documents)

		return idf


	@property
	def __tfidf(self) -> dict:
		tfidf: dict = dict()
		tmp_tf: dict = self.tf
		tmp_idf: dict = self.idf

		for file in tmp_tf:
			tfidf[file]: dict = dict()
			for t in tmp_tf[file]:
				tfidf[file][t] = tmp_tf[file][t] * tmp_idf[t]

			tfidf[file] = dict(sorted(tfidf[file].items(), key=lambda x: x[1], reverse=True))

		return tfidf


	@property
	def t(self):
		return self.__t
	

	@property
	def D(self) -> int:
		return self.__D
	

	@property
	def tf(self) -> dict:
		return self.__tf


	@property
	def idf(self) -> dict:
		return self.__idf


	@property
	def tfidf(self) -> dict:
		pprint(self.tf)
		print('\n')
		pprint(self.idf)
		print('\n')
		return self.__tfidf

		
if __name__ == "__main__":
	tf_idf = TFIDF(
		path=r"",
		t=""
	)

	pprint(tf_idf.tfidf, sort_dicts=False)