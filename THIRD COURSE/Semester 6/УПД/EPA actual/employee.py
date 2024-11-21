from utilits import *

employee = Blueprint('employee', __name__)

@employee.route('/', methods=['GET', 'POST'])
def employee_page():
	if request.method == 'POST':
		update_status(request.form)
		return redirect('/employee/')

	if admin_info_service():
		info = admin_service()
		
		return render_template(
			'employee/employee_service.html',
			flag=True,
			info=info,
			name=list_show_service,
			list_status=list_status
		)
	
	return render_template('employee/employee_service.html')