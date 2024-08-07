#ifndef __CPU_STAT_MONITOR_H__
#define __CPU_STAT_MONITOR_H__

#include "monitor_inter_.h"

namespace monitor {
    class CPUStatMonitor : public MonitorInterface {
    public:
        CPUStatMonitor();
        virtual ~CPUStatMonitor() {};

        void updateOnce(monitor::proto::MonitorInfo* monitorInfo) override;
        void stop() override {};

    private:
        
    };
} // namespace monitor

#endif // __CPU_STAT_MONITOR_H__