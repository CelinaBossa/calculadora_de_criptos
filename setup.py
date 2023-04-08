import ctypes
import requests
import json


# Carga la biblioteca compartida
mylib = ctypes.CDLL('./multiplication.so') 

# Genera peticion HTTL
url = 'https://api.coingecko.com/api/v3/simple/price?ids=bitcoin%2Cethereum&vs_currencies=usd'

respuesta = requests.get(url)

objeto_json = json.loads(respuesta.text)
valor_reportado = objeto_json['bitcoin']
value = valor_reportado.get('usd')
# Utiliza el valor reportado en tu código
print('El valor reportado es:', value)
value = float(value)
print(type(value))

# Llama a la función 'add_numbers' y muestra el resultado
result = mylib.multiply(value, 2)
print(result) 
