from app import db
import json

def update_user_services(user, service, new_service_counter):
    services_dict = json.loads(user.services)
    services_dict.update({service['date']+'--'+service['time']: service})
    user.services = json.dumps(services_dict)
    user.service_counter = json.dumps(new_service_counter)
    db.session.commit()

#---------------------------------------------------------------------------------------------------
