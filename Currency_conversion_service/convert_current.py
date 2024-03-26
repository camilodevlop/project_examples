import requests

def convert_current(service):
    # Get the conversion rates for the "from" currency
    response = requests.get(f'https://api.coinbase.com/v2/exchange-rates?currency={service["input"]["from"]}')
    data = response.json()

    # Get the conversion rate for the "to" currency
    rate = data['data']['rates'][service['input']['to']]

    # Convert the amount
    result = float(rate) * service['input']['amount']

    return result

#---------------------------------------------------------------------------------------------------
