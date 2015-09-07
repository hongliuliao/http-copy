#include "monitor_handler.h"
#include "flow_handler.h"
#include "file_agent.h"

int main() {
    LogMonitorHandler *h = LogMonitorHandler::get_instance();
    int ret = h->init();
    if (ret != 0) {
        return -1;
    }

    FileAgent fa;
    fa.set_flow_handler(*h);
    fa.start_watch(h->get_log_path().c_str());
    return 0;
}
