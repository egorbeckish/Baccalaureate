from langchain.prompts import load_prompt
import langchain.prompts
from langchain.chains.summarize import load_summarize_chain
from langchain_community.chat_models import GigaChat
from langchain_community.document_loaders import TextLoader
from langchain.text_splitter import RecursiveCharacterTextSplitter
import os
import langchain

def foo(access_token: str, prompt: str) -> None:
	giga = GigaChat(
		model="GigaChat",
		verify_ssl_certs=False,
		profanity_check=False
	)

	giga.access_token = access_token

	loader = TextLoader(os.listdir()[-5])
	document = loader.load()

	text_splitter = RecursiveCharacterTextSplitter(
		chunk_size = 7000,
		chunk_overlap  = 0,
		length_function = len,
		is_separator_regex = False,
	)


	#_prompt = load_prompt("prompt.yaml")
	_prompt = langchain.prompts.PromptTemplate.from_template(
		template=f"{prompt}\n\n" + '{text}'
	)

	chain = load_summarize_chain(
		giga,
		chain_type='map_reduce',
		map_prompt=_prompt,
		combine_prompt=_prompt,
		verbose=False
	)

	results = chain.invoke(
		{
			'input_documents': document
		}
	)

	return results['output_text']
