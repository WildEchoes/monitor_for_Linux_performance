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

        struct CPUStat {
            std::string cpu_name;  // cpu, cpu0, cpu1, ...
            float user;   // 用户态时间 不包括 nice 值为负进程 
            float nice;   // 低优先级用户态时间 nice 值为负的进程所占用的CPU时间
            float system; // 内核态时间
            float idle;   // 系统启动开始累计的空闲时间
            float io_wait; // 等待IO时间
            float irq;    // 硬中断时间
            float soft_irq;  // 软中断时间
            float steal;   // 被其他虚拟机占用的 CPU 时间
            float guest;   // 系统运行在虚拟机中的时候，虚拟机运行时间
            float guest_nice;  // 低优先级运行虚拟机的时间（包含在nice）
        };
    private:
        std::unordered_map<std::string, CPUStat> m_map;  // 保留上一次的CPU状态信息
    };
} // namespace monitor

#endif // __CPU_STAT_MONITOR_H__