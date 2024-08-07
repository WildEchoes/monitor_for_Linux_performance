#include "cpu_stat_monitor.h"
#include "read_flie.h"
#include "monitor_info.pb.h"
#include "monitor_info.grpc.pb.h"

namespace monitor {
    CPUStatMonitor::CPUStatMonitor()
    {
    }

    void CPUStatMonitor::updateOnce(
        monitor::proto::MonitorInfo* monitorInfo
    )
    {
        // "cat /proc/stat" 
        /*
             user nice system idle iowait irq softirq steal guest guest_nice
        cpu  30820 0 18122 13408582 3569 0 4076 0 0 0
        cpu0 2065 0 1321 669033 289 0 3164 0 0 0
        cpu1 1656 0 639 670443 396 0 409 0 0 0
        intr 3650426 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1385 1 3 24 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
        ctxt 12957326
        btime 1722995167
        processes 74159
        procs_running 2
        procs_blocked 0
        softirq 3345916 0 322913 1 217487 8373 0 244400 1298327 0 1254415
        */
        
        ReadFile cpu_stat_file(std::string("/proc/stat"));
        std::vector<std::string> cpu_stat_list{};

        while (cpu_stat_file.readLine(&cpu_stat_list))
        {
            // 只对CPU信息进行处理
            if(cpu_stat_list[0].find("cpu") != std::string::npos)
            {
                // 解析读取的cpu信息
                CPUStat cpuStat;
                cpuStat.cpu_name = cpu_stat_list[0];
                cpuStat.user = std::stof(cpu_stat_list[1]);
                cpuStat.nice = std::stof(cpu_stat_list[2]);
                cpuStat.system = std::stof(cpu_stat_list[3]);
                cpuStat.idle = std::stof(cpu_stat_list[4]);
                cpuStat.io_wait = std::stof(cpu_stat_list[5]);
                cpuStat.irq = std::stof(cpu_stat_list[6]);
                cpuStat.soft_irq = std::stof(cpu_stat_list[7]);
                cpuStat.steal = std::stof(cpu_stat_list[8]);
                cpuStat.guest = std::stof(cpu_stat_list[9]);
                cpuStat.guest_nice = std::stof(cpu_stat_list[10]);

                // 
                auto it = m_map.find(cpuStat.cpu_name);
                if(it != m_map.end())
                {
                    CPUStat oldStat;
                    oldStat = it->second;
                    // 向该对象中添加一个新的cpu_stat消息，并返回一个指向该消息的指针
                    auto stat_message = monitorInfo->add_cpu_stat();
                    // cpu运行时间
                    float new_cpu_total_time = cpuStat.user + cpuStat.system
                                             + cpuStat.nice + cpuStat.idle 
                                             + cpuStat.io_wait + cpuStat.irq 
                                             + cpuStat.soft_irq + cpuStat.steal;
                    
                    float old_cpu_total_time = oldStat.user + oldStat.system
                                                + oldStat.nice + oldStat.idle 
                                                + oldStat.io_wait + oldStat.irq 
                                                + oldStat.soft_irq + oldStat.steal;

                    // cpu繁忙时间
                    float new_cpu_busy_time = new_cpu_total_time - cpuStat.idle - cpuStat.io_wait;
                    float old_cpu_busy_time = old_cpu_total_time - oldStat.idle - oldStat.io_wait;

                    // cpu使用率
                    float cpu_percent = (new_cpu_busy_time - old_cpu_busy_time) / (new_cpu_total_time - old_cpu_total_time) * 100.00;
                    // cpu用户态使用率
                    float user_percent = (cpuStat.user - oldStat.user) / (new_cpu_total_time - old_cpu_total_time) * 100.00;
                    // cpu内核态使用率
                    float system_percent = (cpuStat.system - oldStat.system) / (new_cpu_total_time - old_cpu_total_time) * 100.00;
                    // cpu nice使用率
                    float nice_percent = (cpuStat.nice - oldStat.nice) / (new_cpu_total_time - old_cpu_total_time) * 100.00;
                    // cpu 空闲率
                    float idle_percent = (cpuStat.idle - oldStat.idle) / (new_cpu_total_time - old_cpu_total_time) * 100.00;
                    // cpu io等待率
                    float io_wait_percent = (cpuStat.io_wait - oldStat.io_wait) / (new_cpu_total_time - old_cpu_total_time) * 100.00;
                    // cpu 硬中断率
                    float irq_percent = (cpuStat.irq - oldStat.irq) / (new_cpu_total_time - old_cpu_total_time) * 100.00;
                    // cpu 软中断率
                    float soft_irq_percent = (cpuStat.soft_irq - oldStat.soft_irq) / (new_cpu_total_time - old_cpu_total_time) * 100.00;

                    stat_message->set_cpu_name(cpuStat.cpu_name);
                    stat_message->set_cpu_percent(cpu_percent);
                    stat_message->set_usr_percent(user_percent);
                    stat_message->set_sys_percent(system_percent);
                    stat_message->set_nice_percent(nice_percent);
                    stat_message->set_idle_percent(idle_percent);
                    stat_message->set_iowait_percent(io_wait_percent);
                    stat_message->set_irq_percent(irq_percent);
                    stat_message->set_softirq_percent(soft_irq_percent);
                }
                m_map[cpuStat.cpu_name] = cpuStat;
            }

            cpu_stat_list.clear();
        }
    }
}