#include <stdio.h>
#include <curl/curl.h>
#include <string.h>


size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
    
  printf("%.*s", (int)(size * nmemb), ptr);
  return size*nmemb;
}       

int main(void)
{
  CURL *curl;
  CURLcode res;
  
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.binance.com/api/v3/ticker/price?symbol=BTCUSDT");
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));

    printf("\n");
    
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.binance.com/api/v3/ticker/price?symbol=ETHUSDT");

    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));

    
    curl_easy_cleanup(curl);
  }
  
  

  return 0;
}
