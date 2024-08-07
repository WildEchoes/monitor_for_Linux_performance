#ifndef __CPU_LOAD_MONITOR_H__
#define __CPU_LOAD_MONITOR_H__

#include "monitor_inter_.h"

namespace monitor {
    class CPULoadMonitor : public MonitorInterface {
    public:
        CPULoadMonitor();
        virtual ~CPULoadMonitor() {};

        void updateOnce(monitor::proto::MonitorInfo* monitorInfo) override;
        void stop() override {};

    private:
        float m_load_avg_1;  // 1 minute load average
        float m_load_avg_3;
        float m_load_avg_15;
    };
} // namespace monitor

#endif // __CPU_LOAD_MONITOR_H__