import ctypes
import requests
import json

cripto = ['bitcoin','ethereum']
moneda = ['peso','euro','dolar']

# Carga la biblioteca compartida
mylib = ctypes.CDLL('./multiplication.so') 
mylib.multiply.restype = ctypes.c_float
mylib.multiply.argtypes = (ctypes.c_float,ctypes.c_float)

# Genera peticion HTTL
url = 'https://api.coingecko.com/api/v3/simple/price?ids=bitcoin%2Cethereum&vs_currencies=usd'

respuesta = requests.get(url)

objeto_json = json.loads(respuesta.text)

for i in range(len(cripto)):
    valor_reportado = objeto_json[cripto[i]]
    value = valor_reportado.get('usd')
    # Utiliza el valor reportado en tu código
    print('El valor reportado es:', value)

    # Llama a la función 'add_numbers' y muestra el resultado
    result = mylib.multiply(ctypes.c_float(value), 2)
    print(result) 
