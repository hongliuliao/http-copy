/*
 * curl_utils.h
 *
 *  Created on: Jul 29, 2014
 *      Author: liao
 */

#ifndef CURL_UTILS_H_
#define CURL_UTILS_H_

#include "curl/curl.h"
#include <string>
#include <map>

class HttpClient {
private:
    CURL *curl;
public:
    CURLcode init();

    CURLcode get(std::string &url, std::string &result);

    int close();
};

#endif /* CURL_UTILS_H_ */
