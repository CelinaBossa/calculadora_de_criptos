#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

extern double multiply(double a, double b);

void function_pt(void *ptr, size_t size, size_t nmemb, void *stream);

int main(void)
{
  CURL *curl;
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.binance.com/api/v3/ticker/price?symbol=BTCUSDT");
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
    printf("BTCUSDT: %lf\n", us_value);

    double ars_value = multiply(us_value, 213.10);
    printf("BTCARS: %lf\n", ars_value);
}

