#include "Net.h"

using namespace std;

Internet::Internet(){
    curl=curl_easy_init();
    open=true;
}
size_t Internet::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
string Internet::load(string url){
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    res=curl_easy_perform(curl);
    if(res != CURLE_OK){
        cerr << "Curl easy preform failed: " << curl_easy_strerror(res);
        return "";
    }
    curl_easy_cleanup(curl);
    return buffer;
}

string Internet::load(string url, string postData){
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    res=curl_easy_perform(curl);
    if(res != CURLE_OK){
        cerr << "Curl easy preform failed: " << curl_easy_strerror(res);
        return "";
    }
    return buffer;
}

bool Internet::load(string url, DataCallbackFunc d){
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, d);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);
    res=curl_easy_perform(curl);
    if(res != CURLE_OK){
        cerr << "Curl easy preform failed: " << curl_easy_strerror(res);
        return false;
    }
    return true;
}
    
bool Internet::load(string url, DataCallbackFunc d, void* cl){
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, d);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, cl);
    res=curl_easy_perform(curl);
    if(res != CURLE_OK){
        cerr << "Curl easy preform failed: " << curl_easy_strerror(res);
        return false;
    }
    return true;
}
bool Internet::load(string url, string postData, DataCallbackFunc d){
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, d);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);
    res=curl_easy_perform(curl);
    if(res != CURLE_OK){
        cerr << "Curl easy preform failed: " << curl_easy_strerror(res);
        return false;
    }
    return true;
}
bool Internet::load(string url, string postData, DataCallbackFunc d, void* cl){
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, d);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, cl);
    res=curl_easy_perform(curl);
    if(res != CURLE_OK){
        cerr << "Curl easy preform failed: " << curl_easy_strerror(res);
        return false;
    }
    return true;
}

void Internet::close(){
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    open=false;
}

Internet::~Internet(){
    if(open)
        close();
}