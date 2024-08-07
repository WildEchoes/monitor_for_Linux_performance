#include "cpu_load_monitor.h"
#include "read_flie.h"

namespace monitor {
    CPULoadMonitor::CPULoadMonitor()
        : m_load_avg_1(0.0f)
        , m_load_avg_3(0.0f)
        , m_load_avg_15(0.0f)
    {
    }

    void CPULoadMonitor::updateOnce(
        monitor::proto::MonitorInfo* monitorInfo
    )
    {
        // "cat /proc/loadavg" 测试读取文件
        ReadFile cpu_load_file(std::string("/proc/loadavg"));
        std::vector<std::string> load_list{};

        cpu_load_file.readLine(&load_list);
        m_load_avg_1 = std::stof(load_list[0]);
        m_load_avg_3 = std::stof(load_list[1]);
        m_load_avg_15 = std::stof(load_list[2]);
        
        // 写入读取到的cpu load 数据
        auto message = monitorInfo->mutable_cpu_load();

        message->set_load_avg_1(m_load_avg_1);
        message->set_load_avg_3(m_load_avg_3);
        message->set_load_avg_15(m_load_avg_15);
    }
}