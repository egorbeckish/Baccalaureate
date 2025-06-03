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


CLIENT_ID = st.secrets['CLIENT_ID']
SECRET = st.secrets['SECRET']
AUTH_KEY = st.secrets['AUTH_KEY']
DB_DATA = st.secrets['postgresql']
DB_LINK = st.secrets['postgreslink']


# python.exe -m pip install --upgrade pip
# pip freeze > packages.txt; pip uninstall -r packges.txt -y