#include <stdio.h>
#include <curl/curl.h>
#include <jansson.h>

int main(void)
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        // Establecer la URL y los encabezados HTTP apropiados
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.coingecko.com/api/v3/coins/ethereum/market_chart?vs_currency=usd&days=0&interval=daily");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, "Content-Type: application/json");

        // Realizar la solicitud HTTP y obtener la respuesta
        char *response_data = NULL; // inicializo puntero para guardar variable
        long response_code; //variable para controlar solicitud
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &response_data);
        res = curl_easy_perform(curl);
        
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        printf("Respuesta HTTP: %ld\n", response_code);

        // Analizar la respuesta JSON
        json_t *root;
        json_error_t error;
        root = json_loads(response_data, 0, &error);
        if (!root) {
            fprintf(stderr, "Error: no se pudo analizar la respuesta JSON: %s\n", error.text);
            return 1;
        }

        // Obtener el valor flotante de la respuesta JSON
        json_t *valor = json_object_get(root, "prices");
        if (!json_is_number(valor)) {
            fprintf(stderr, "Error: el valor no es un número\n");
            return 1;
        }
        double valor_flotante = json_number_value(valor);
        printf("Valor flotante: %f\n", valor_flotante);

        cotizacion_peso = asm_main(valor_flotante)





        // Liberar la memoria y limpiar las variables
        json_decref(root);
        free(response_data);
        curl_easy_cleanup(curl);
    }
    return 0;
}