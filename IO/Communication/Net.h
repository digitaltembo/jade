/*******************************************************************************************
 *   Last Modified: 8/13                                                                   *
 *   Compiler Flags: -lcurl                                                                *
 *                                                                                         *
 *   Links:                                                                                *
 *  http://stackoverflow.com/questions/9786150/save-curl-content-result-into-a-string-in-c *
 *******************************************************************************************/

#ifndef INTERNET
#define INTERNET

#include <curl/curl.h>
#include <iostream>
#include <string>

typedef size_t DataCallbackFunc(void *contents, size_t size, size_t nmemb, void *userp);

class Internet{
public:
    Internet();
   ~Internet();
    std::string load(std::string url);
    std::string load(std::string url, std::string postData);
    
    bool load(std::string url, DataCallbackFunc d);
    bool load(std::string url, DataCallbackFunc d, void* cl);
    bool load(std::string url, std::string postData, DataCallbackFunc d);
    bool load(std::string url, std::string postData, DataCallbackFunc d, void* cl);
    void close();
private:
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
    bool open;
    CURL* curl;
    CURLcode res;
    std::string buffer;
};

#endif