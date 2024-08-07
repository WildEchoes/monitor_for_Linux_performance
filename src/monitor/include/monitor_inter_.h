#ifndef __MONITOR_INTER__H__
#define __MONITOR_INTER__H__

#include "monitor_info.grpc.pb.h"

namespace monitor {
    class MonitorInterface {
    public:
        MonitorInterface() = default;
        virtual ~MonitorInterface() {};

        virtual void updateOnce(monitor::proto::MonitorInfo* monitorInfo) = 0;
        virtual void stop() = 0;
    };
} // namespace monitor

#endif // __MONITOR_INTER_H__