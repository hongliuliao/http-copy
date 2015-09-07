/*
 * curl_utils.cpp
 *
 *  Created on: Jul 29, 2014
 *      Author: liao
 */
#include <string>
#include <sstream>
#include "curl/curl.h"
#include "curl_utils.h"
#include "simple_log.h"

int res_writer(char *data, size_t size, size_t nmemb, std::string *write_data) {
	if(write_data == NULL) {
		return 0;
	}
	write_data->append(data, size * nmemb);
	return size * nmemb;
}

CURLcode HttpClient::init() {
    curl = curl_easy_init();
    if(!curl) {
        LOG_ERROR("curl_easy_init error!");
        return CURLE_FAILED_INIT;
    }
    return CURLE_OK;
}

CURLcode HttpClient::get(std::string &url, std::string &result) {
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    CURLcode res_code = curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, res_writer);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 3);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);

    res_code = curl_easy_perform(curl);

    if(res_code != CURLE_OK) {
        LOG_ERROR("curl_easy_perform faild : %s, url:%s", curl_easy_strerror(res_code), url.c_str());
    }
    return res_code;
}

int HttpClient::close() {
    curl_easy_cleanup(curl);
    return 0;
}
