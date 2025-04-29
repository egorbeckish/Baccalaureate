import streamlit as st
# import replicate
import requests
from requests.auth import HTTPBasicAuth
import json
import uuid
import os
import psutil

from langchain.prompts import load_prompt
import langchain.prompts
from langchain.chains.summarize import load_summarize_chain
# from langchain_community.chat_models import GigaChat
from langchain_gigachat import GigaChat
from langchain_community.document_loaders import TextLoader
from langchain.text_splitter import RecursiveCharacterTextSplitter
import os
import langchain

#from langchain_core.documents import Document
#from langchain_chroma import Chroma
#from langchain_community.embeddings.gigachat import GigaChatEmbeddings


CLIENT_ID = st.secrets['CLIENT_ID']
SECRET = st.secrets['SECRET']
AUTH_KEY = st.secrets['AUTH_KEY']