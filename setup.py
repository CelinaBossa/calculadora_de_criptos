import ctypes
import requests
import json

cripto = ['bitcoin','ethereum']
moneda = ['euro','dolar']
cotizacion_moneda = []

# Carga la biblioteca compartida
mylib = ctypes.CDLL('./main.so') 
mylib.multiply.restype = ctypes.c_double #defino retorno
mylib.multiply.argtypes = (ctypes.c_double, ctypes.c_double) #defino parametros de llamada

# Genera peticion HTTL
url_cripto = 'https://api.coingecko.com/api/v3/simple/price?ids=bitcoin%2Cethereum&vs_currencies=ars'
url_moneda_b = 'https://www.dolarsi.com/api/api.php?type='

#Obtención de cotizacion de dolar y euro
for j in range(len(moneda)):
    url_moneda = url_moneda_b+moneda[j] #completo el URL
    datos = requests.get(url_moneda)
    datos_json = json.loads(datos.text)
    valor = datos_json[2] # 2 porque en ambos URL el label 2 tiene cotizacion
    cotizacion = (valor.get('casa')).get('venta') #el label 'venta' esta dentro de 'casa
    cotizacion = cotizacion.replace(',','.') #remplazo ',' por '.' para convertir en double
    cotizacion_moneda.append(1/double(cotizacion))

#Obtencion de cotizacion de criptos
respuesta = requests.get(url_cripto)
objeto_json = json.loads(respuesta.text)

for k in range(len(moneda)):
    print("Moneda:"+moneda[k])
    print(" ")
    for i in range(len(cripto)):
        print("Cripto:"+cripto[i])
        valor_reportado = objeto_json[cripto[i]]
        value = valor_reportado.get('ars')
        # Utiliza el valor reportado en tu código
        print('El valor reportado es:', value)

        # Llama a la función 'multiply' y muestra el resultado
        resultado = mylib.multiply(ctypes.c_double(value),ctypes.c_double(cotizacion_moneda[k]))

        #   multiply (cotizacion cripto, cotizacion euro, cotizacion dolar) todo referenciado a ars
        print(resultado)
        print("------------------ ")
    print("***************************")
    print(" ")