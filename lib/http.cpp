/*
Copyright (c) 2006 Pluron Inc.

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "http.h"

#include <curl/curl.h>

namespace Restful {

string Http::get(const string &url)
{
    string buffer;
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl)
    {
        //setting url
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        //setting follow redirect to true
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
        //using HTTP GET
        curl_easy_setopt(curl, CURLOPT_HTTPGET, true);
        //capturing the output
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Http::writeData);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        //performing the request
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if (res == CURLE_OK)
            return buffer;
    }
    throw GetException();
}

void Http::put(const string &url, const string &data)
{
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl)
    {
        //setting url
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        //setting follow redirect to true
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
        //using HTTP PUT
        curl_easy_setopt(curl, CURLOPT_PUT, true);
        //setting the input
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, Http::readData);
        curl_easy_setopt(curl, CURLOPT_READDATA, &data);
        curl_easy_setopt(curl, CURLOPT_INFILESIZE, data.size());
        //performing the request
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if (res != CURLE_OK)
            throw PutException();
    }
}

size_t Http::writeData(void *buffer, size_t size, size_t nmemb, string *data)
{
    if (data == 0)
        return 0;
    data->append((const char *)buffer, size*nmemb);
    return size*nmemb;
}

size_t Http::readData(void *buffer, size_t size, size_t nmemb, string *data)
{
    if (data == 0)
        return 0;
    const char *str = data->c_str();
    strncpy((char*)buffer, str, size*nmemb);
    return size*nmemb;
}

}
