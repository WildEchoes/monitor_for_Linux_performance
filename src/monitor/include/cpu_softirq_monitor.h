#ifndef __CPU_SOFTIRQ_MONITOR_H__
#define __CPU_SOFTIRQ_MONITOR_H__

#include <unordered_map>
#include <boost/chrono.hpp>

#include "monitor_inter_.h"
#include "monitor_info.pb.h"
#include "monitor_info.grpc.pb.h"

namespace monitor {
    class CPUSoftIRQMonitor final : public MonitorInterface {
        public:
            struct SoftIrq
            {
                std::string cpu_name;
                int64_t hi;     // 高优先级软中断的计数
                int64_t timer;  // 定时器软中断的计数
                int64_t net_tx; // 网络发送软中断的计数
                int64_t net_rx; // 网络接收软中断的计数
                int64_t block;  // 块设备软中断的计数
                int64_t irq_poll;  // 中断轮询软中断的计数
                int64_t tasklet;  // tasklet软中断的计数
                int64_t sched;  // 调度器软中断的计数
                int64_t hrtimer;  // 高精度定时器软中断的计数
                int64_t rcu;    // RCU（Read-Copy Update）软中断的计数
                boost::chrono::steady_clock::time_point timepoint;
            };
            
            CPUSoftIRQMonitor();
            virtual ~CPUSoftIRQMonitor() {}

            void updateOnce(monitor::proto::MonitorInfo* monitorInfo) override;
            void stop() override {}

        private:
            std::unordered_map<std::string, SoftIrq> m_map;
    };
} // namespace monitor

#endif // __CPU_SOFTIRQ_MONITOR_H__