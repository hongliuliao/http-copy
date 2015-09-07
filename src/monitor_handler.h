/*
 * log_monitor_handler.h
 *
 *  Created on: Apr 7, 2015
 *      Author: liao
 */

#ifndef LOG_MONITOR_HANDLER_H_
#define LOG_MONITOR_HANDLER_H_

#include <map>
#include "flow_handler.h"
#include "curl_utils.h"

class LogMonitorHandler : public LineFlowHandler {

public:
    ~LogMonitorHandler() {
        if (INSTANCE != NULL) {
            delete INSTANCE;
            INSTANCE = NULL;
        }
    }

    static LogMonitorHandler *get_instance() {
        if (INSTANCE == NULL) {
            INSTANCE = new LogMonitorHandler();
        }
        return INSTANCE;
    }

    int init();

    int load_configs(const char *config_file);

    int handle_lines(std::vector<std::string> lines);

    std::string get_log_path() {
        return _log_path;
    }

private:
    LogMonitorHandler() {
        INSTANCE = NULL;
    }
    std::map<std::string, std::string> configs;
    static LogMonitorHandler *INSTANCE;
    std::string _dist_host;
    std::string _log_path;
    HttpClient _http_client;
};


#endif /* LOG_MONITOR_HANDLER_H_ */
