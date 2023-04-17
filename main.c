#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

extern double multiply(double a, double b);
void usage();
void function_pt(void *ptr, size_t size, size_t nmemb, void *stream);
char crypto1[32], crypto2[32];
double dolarhoy = 0.0;

int main(int argc, char *argv[])
{
    if (argc != 4 || !(!strcmp(argv[2], "USDT") || !strcmp(argv[2], "EUR")))
       usage();
    strcpy(crypto1,argv[1]);
    strcpy(crypto2,argv[2]);
    dolarhoy = atof(argv[3]);


    char buffer[100];
    snprintf(buffer, sizeof(buffer), "https://api.binance.com/api/v3/ticker/price?symbol=%s%s", argv[1], argv[2]);

    CURL *curl;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, buffer);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, function_pt);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return 0;
}


void function_pt(void *ptr, size_t size, size_t nmemb, void *stream)
{   

    printf("%s\n", ptr);
    char* chrptr = strchr(ptr, 'e');
    if (chrptr != NULL) {
        chrptr += 4;
    }
    else
        exit(EXIT_FAILURE);
    double us_value = strtod(chrptr, NULL);
    printf("%s %s: %lf\n", crypto1, crypto2, us_value);

    double ars_value = multiply(us_value, dolarhoy);
    printf("%s ARS: %lf\n", crypto1, ars_value);
}
void usage()
{
  fprintf(stderr, "usage: main crypto1 currency currency_to_ARS\n");
  fprintf(stderr, "    crypto:          cryptocurrency to convert\n");
  fprintf(stderr, "    currency:        currency of conversion\n");
  fprintf(stderr, "    currency_to_ARS: value of currency in ARS\n");
  exit(EXIT_FAILURE);
}

