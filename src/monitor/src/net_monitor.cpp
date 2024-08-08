#include "net_monitor.h"
#include "read_flie.h"

namespace monitor {
    void NetMonitor::updateOnce(monitor::proto::MonitorInfo *monitorInfo)
    {
        ReadFile net_file(std::string("/proc/net/dev"));
        std::vector<std::string> net_info;
        while (net_file.readLine(&net_info))
        {
            if(net_info[0].find(":") != std::string::npos)
            {
                NetInfo net_data;
                net_data.name = net_info[0];
                net_data.name.pop_back();

                net_data.rcv_bytes = std::stoll(net_info[1]);
                net_data.rcv_packets = std::stoll(net_info[2]);
                net_data.err_in = std::stoll(net_info[3]);
                net_data.drop_in = std::stoll(net_info[4]);

                net_data.snd_bytes = std::stoll(net_info[9]);
                net_data.snd_packets = std::stoll(net_info[10]);
                net_data.err_out = std::stoll(net_info[11]);
                net_data.drop_out = std::stoll(net_info[12]);

                net_data.timepoint = boost::chrono::steady_clock::now();

                auto iter = m_net_info.find(net_data.name);
                if(iter != m_net_info.end())
                {
                    // 上一次的数据
                    auto old_data = std::move(iter->second);
                    
                    // 两次时间间隔
                    double time_interval = boost::chrono::duration_cast<boost::chrono::seconds>(net_data.timepoint - old_data.timepoint).count();
                    
                    auto it = monitorInfo->add_net_info();
                    it->set_name(net_data.name);
                    // 换算为 KiB
                    it->set_rcv_rate((net_data.rcv_bytes - old_data.rcv_bytes) / 1024 / time_interval);
                    it->set_rcv_packets_rate((net_data.rcv_packets - old_data.rcv_packets) / 1024 / time_interval);
                    it->set_send_rate((net_data.snd_bytes - old_data.snd_bytes) / 1024 / time_interval);
                    it->set_send_packets_rate((net_data.snd_packets - old_data.snd_packets) / 1024 / time_interval);

                }

                m_net_info[net_data.name] = net_data;
            }
            net_info.clear();
        }
        
    }
}

/*
cat /proc/net/dev
Inter-|   Receive                                                |  Transmit
 face |bytes    packets errs drop fifo frame compressed multicast|bytes    packets errs drop fifo colls carrier compressed
    lo: 193834278  224353    0    0    0     0          0         0 193834278  224353    0    0    0     0       0          0
services1: 177073790  166494    0    0    0     0          0         0 63722344  228616    0    0    0     0       0          0
  eth0: 80037594  253332    0    0    0     0          0         0 205376130  289537    0    0    0     0       0          0
docker0:       0       0    0    0    0     0          0         0        0       0    0    0    0     0       0          0
*/