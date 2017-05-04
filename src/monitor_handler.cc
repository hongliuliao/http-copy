/*
 * log_monitor_handler.cpp
 *
 *  Created on: Apr 7, 2015
 *      Author: liao
 */
#include <sstream>
#include <sys/time.h>
#include "simple_config.h"
#include "simple_log.h"
#include "monitor_handler.h"
#include "reg_utils.h"

const char *LINE_REG_NAME = "log_reg";
const char *LOG_PATH_NAME = "log_path";
const char *HOST_NAME = "dist_host";

const int excepted_match_size = 2; // 0: whole, 1: url
const int INDEX_OF_URL = 1;

LogMonitorHandler *LogMonitorHandler::INSTANCE = NULL;

int LogMonitorHandler::init() {
    int ret = this->load_configs("conf/copy.conf");
    if (ret != 0) {
        return ret;
    }
    return _http_client.init();
}

int LogMonitorHandler::load_configs(const char *config_file) {
    get_config_map(config_file, configs);
    if (configs[LINE_REG_NAME].empty()) {
        LOG_ERROR("log_reg is empty!");
        return -1;
    }
    if (configs[HOST_NAME].empty()) {
        LOG_ERROR("dist_host is empty!");
        return -1;
    }
    _dist_host = configs[HOST_NAME];
    _log_path = configs[LOG_PATH_NAME];
    return 0;
}

int LogMonitorHandler::handle_lines(std::vector<std::string> lines) {
    if (lines.empty()) {
        return 0;
    }
    for (unsigned i = 0; i < lines.size(); i++) { int matched_size = 0;
        std::string match_str_array[excepted_match_size];
        bool match_ret = is_match_reg(lines[i], configs[LINE_REG_NAME], excepted_match_size, match_str_array, matched_size);

        if (!match_ret || matched_size < excepted_match_size - 1) {
            LOG_DEBUG("can not match line for reg:%s, match_ret:%d, matched_size:%d", 
                configs[LINE_REG_NAME].c_str(), match_ret, matched_size);
            continue;
        }
        std::string uri = match_str_array[1];

        std::string url = "http://";
        url += _dist_host;
        url += uri;
        
        LOG_INFO("start copy url:%s, dist_host:%s", url.c_str(), _dist_host.c_str());

        struct timeval start, end;
        gettimeofday(&start, NULL);
        
        std::string result;
        CURLcode cc = _http_client.get(url, result);
        
        gettimeofday(&end, NULL);
        int cost_time = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000;

        LOG_INFO("copy complete url:%s, ret:%d, cost_time:%d ms", url.c_str(), cc, cost_time);
    }
    return 0;
}

