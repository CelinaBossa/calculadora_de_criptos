import requests
import json
import sys

# Defining Binance API URL
key = "https://api.binance.com/api/v3/ticker/price?symbol="

url = key + sys.argv[1] + sys.argv[2]
data = requests.get(url)
data = data.json()
value = data.get('price')
print(value)