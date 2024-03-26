from flask import request, render_template
from flask_login import current_user
from request_currency_conversion import request_currency_conversion
from convert_current import convert_current
from update_user_services import update_user_services
import json

def handle_post_request():
    service, new_service_counter = request_currency_conversion(json.loads(current_user.service_counter))
    if not service:
        return render_template('limit_reached.html', name=current_user.name)

    conversion_dict = {
        "from": request.form.get("from"),
        "to": request.form.get("to"),
        "amount": float(request.form.get("amount"))
    }
    service['input'] = conversion_dict
    service['output'] = {'result': convert_current(service)}
    update_user_services(current_user, service, new_service_counter)

    return render_template('login.html', name=current_user.name, result=service['output']['result'])

#---------------------------------------------------------------------------------------------------
