#ifndef __NET_MONITOR_H__
#define __NET_MONITOR_H__

#include "monitor_inter_.h"

namespace monitor {
    class NetMonitor : public MonitorInterface {
    public:
        NetMonitor() {};
        void updateOnce(monitor::proto::MonitorInfo *monitorInfo) override;
    };
}

#endif // __NET_MONITOR_H__