from utilits import *

admin = Blueprint('admin', __name__)

@admin.route('/', methods=['GET', 'POST'])
def admin_page():
	if request.method == 'POST':
		update_employees(request.form)
		return redirect('/admin/')

	if admin_info_service():
		info = admin_service()
		
		return render_template(
			'admin/admin_service.html',
			flag=True,
			info=info,
			name=list_show_service,
			dict_employees=dict_employees
		)
	
	return render_template('admin/admin_service.html')