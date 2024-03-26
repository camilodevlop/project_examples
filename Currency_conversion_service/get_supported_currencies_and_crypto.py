import requests

def get_supported_currencies_and_crypto():
    response_currencies = requests.get('https://api.coinbase.com/v2/currencies')
    response_cryptos = requests.get('https://api.coinbase.com/v2/currencies/crypto')
    currencies_and_cryptos = {}

    if response_currencies.status_code == 200 and response_cryptos.status_code == 200:
        currencies = response_currencies.json()['data']
        currencies = {currency['id']: currency['name'] for currency in currencies}
        cryptos = response_cryptos.json()['data']
        cryptos = {crypto['code']: crypto['name'] for crypto in cryptos}
        currencies_and_cryptos = {**currencies, **cryptos}

    return currencies_and_cryptos

#---------------------------------------------------------------------------------------------------
