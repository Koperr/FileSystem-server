#include "CurlMethods.h"

size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void CurlMethods::PerformGetRequest(const std::string& url)
{
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        std::cout << "Response: [" << readBuffer << "]\n";

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

void CurlMethods::PerformPostRequest(const std::string& url)
{
    // TODO
}

void CurlMethods::PerformPutRequest(const std::string& url)
{
    // TODO
}

void CurlMethods::PerformDeleteRequest(const std::string& url)
{
    // TODO
}