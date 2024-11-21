import streamlit as st
import replicate
import requests
from requests.auth import HTTPBasicAuth
import json
import uuid
import os

#from langchain_core.documents import Document
#from langchain_chroma import Chroma
#from langchain_community.embeddings.gigachat import GigaChatEmbeddings


CLIENT_ID = st.secrets['CLIENT_ID']
SECRET = st.secrets['SECRET']