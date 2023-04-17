# calculadora_de_criptos

Se desarrollaron 3 calculadoras. Las 3 calculadoras hacen uso de la convención de llamadas de C, para implementar la función “multiply”, escrita en assembler. En primer lugar, se desarrolló una calculadora en python, que permite obtener el valor de bitcoin (BTC) y ethereum (ETH) en dólares a partir de sus valores en pesos argentinos. Los valores de las criptomonedas son obtenidos a partir de la API REST de “coingecko.com”.
  En segundo lugar, se desarrollaron 2 calculadoras en C, que permiten obtener el valor de alguna criptomoneda en pesos argentinos, a partir de sus valores en dólares o euros. Para obtener los valores de las criptomonedas en dólares o euros, estas aplicaciones hacen uso de la API REST de “binance.com”.
  A continuación se muestra una tabla que sintetiza la implementación de cada calculadora:
                    
                              CALC 1      CALC2           CALC3
mian()                        Python        C               C
Peticion HTTP                 Python      Python            C
Librería para petición HTTP   request     Python/request  curl  
Llamada a asm                    C          C               C

CALC 1 la podrán encontrar en el branch python-driver
CALC 2 la podrán encontrar en el branch c-driver
CALC 3 la podrán encontrar en el branch libcurl-driver
