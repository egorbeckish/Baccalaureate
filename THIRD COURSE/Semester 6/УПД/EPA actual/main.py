from user import *
from admin import *
from employee import *

app = Flask(__name__)
app.secret_key = ' '

app.register_blueprint(user)
app.register_blueprint(admin, url_prefix='/admin')
app.register_blueprint(employee, url_prefix='/employee')