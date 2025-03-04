from utils import *


class BM25:

	def __init__(self, path: str, q: str) -> None:
		self.__path: str = path
		self.__documents: list = [doc for doc in os.listdir(self.__path) if os.path.isfile(fr"{self.__path}\{doc}")]
		self.__q: list = " ".join(re.split(r"[\s\.\,\!\?()«»\-]", q)).lower().split()
		self.__D: int = len(self.__documents)
		self.__k1: float = 1.2
		self.__b: float = .5


	@property
	def k1(self) -> float:
		return self.__k1


	@property
	def b(self) -> float:
		return self.__b


	@property
	def D(self) -> int:
		return self.__D


	@property
	def __avgdl(self) -> float:
		avgdl: int = 0
		
		for document in self.__documents:
			with open(fr"{self.__path}\{document}", encoding="utf-8") as file:
				avgdl += len(" ".join(del_space(re.split(r"[\s\.\,\!\?()«»\-]", file.read()))).lower().split())
		
		return avgdl / self.D


	@property
	def avgdl(self) -> float:
		return self.__avgdl


	@property
	def __norm(self) -> float:
		return 1 / (1 - self.b + (self.b * (self.D / self.avgdl)))

	@property
	def norm(self) -> float:
		return self.__norm


	def __frequence(self, q: str, D: str) -> int:
		with open(fr"{self.__path}\{D}", encoding="utf-8") as file:
			file: list = " ".join(del_space(re.split(r"[\s\.\,\!\?()«»\-]", file.read()))).lower()

		return len(re.findall(fr"{q}[а-я]*", file))


	def frequence(self, q: str, D: str) -> int:
		return self.__frequence(q, D)


	def __n_q(self, q: str) -> int:
		_n_q: int = 0

		for document in self.__documents:
			_n_q += self.frequence(q, document)

		return _n_q


	def n_q(self, q: str) -> int:
		return self.__n_q(q)


	def __idf(self, q: str) -> float:
		return log1p((self.D - self.n_q(q) + .5)/(self.n_q(q) + .5))


	def idf(self, q: str) -> float:
		return self.__idf(q)


	def __frequence_document(self, q: str, D: str) -> float:
		return (self.frequence(q, D) * (self.k1 + 1)) / (self.k1 + 1)


	def frequence_document(self, q: str, D: str) -> float:
		return self.__frequence_document(q, D)


	def __tf(self, q: str, D: str) -> float:
		return self.frequence_document(q, D) * self.norm


	def tf(self, q: str, D: str) -> float:
		return self.__tf(q, D)


	@property
	def __bm25(self) -> float:
		bm25: dict = dict()

		for document in self.__documents:
			bm25[document]: dict = {"tfidf": dict(), "score": None}
			score: float = 0.0

			for q in self.__q:
				tf: float = self.tf(q, document)
				idf: float = self.idf(q)
				bm25[document]["tfidf"][q]: dict = dict()
				bm25[document]["tfidf"][q]["tf"]: float = tf
				bm25[document]["tfidf"][q]["idf"]: float = idf
				score += tf * idf

			bm25[document]["score"] = score
		
		return dict(sorted(bm25.items(), key=lambda x: x[1]["score"], reverse=True))

	@property
	def bm25(self) -> float:
		return self.__bm25


if __name__ == "__main__":
	bm25 = BM25(
		path=r"",
		q=""
	)

	pprint(bm25.bm25)