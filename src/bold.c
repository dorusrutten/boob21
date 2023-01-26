
/*#include <string>
#include <curl/curl.h>

int main() {
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, "https://api.technoviumunlimited.nl/v1/score/fY0cJVemqT0UKI43rMNu/users/level_data");
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    }
    curl_easy_cleanup(curl);
  }
  return 0;
}*/