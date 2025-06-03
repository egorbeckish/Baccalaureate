import streamlit as st
import requests
from requests.auth import HTTPBasicAuth
import uuid
import os
import psutil
import json
import pandas as pd
import time
from docx import Document
from pypdf import PdfReader
from pptx import Presentation
import psycopg2 as psql
from langchain_ollama import OllamaLLM
from langchain_community.document_loaders import TextLoader
from langchain.text_splitter import RecursiveCharacterTextSplitter
from langchain_core.prompts import PromptTemplate
from langchain.chains.summarize import load_summarize_chain
from langchain_gigachat import GigaChat
from langchain_community.document_loaders import SQLDatabaseLoader
from langchain_community.utilities import SQLDatabase


CLIENT_ID = st.secrets['CLIENT_ID']
SECRET = st.secrets['SECRET']
AUTH_KEY = st.secrets['AUTH_KEY']
DB_DATA = st.secrets['postgresql']
DB_LINK = st.secrets['postgreslink']['link']


# python.exe -m pip install --upgrade pip
# pip freeze > packages.txt; pip uninstall -r packges.txt -y
# C:\Users\ebeck\.ollama\models\manifests\registry.ollama.ai\library