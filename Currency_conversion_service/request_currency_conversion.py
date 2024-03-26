from datetime import datetime
from have_requests import have_requests

def request_currency_conversion(service_counter):
    service = {}
    now = datetime.now()

    if service_counter['date'] == now.strftime("%d-%m-%Y"):
        if not have_requests(service_counter['counter'], now.strftime("%A")):
            return service, service_counter
        service_counter['counter'] += 1
    else:
        service_counter['counter'] = 1

    service_counter['date'] = now.strftime("%d-%m-%Y")
    service_counter['time'] = now.strftime("%H:%M:%S")

    service['date'] = now.strftime("%d-%m-%Y")
    service['time'] = now.strftime("%H:%M:%S")
    service['day'] = now.strftime("%A")
    service['input'] = {'from': '', 'to': '', 'amount': 0}
    service['output'] = {'result': 0}

    return service, service_counter

#---------------------------------------------------------------------------------------------------
