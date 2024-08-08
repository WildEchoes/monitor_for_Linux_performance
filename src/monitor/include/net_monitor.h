#ifndef __NET_MONITOR_H__
#define __NET_MONITOR_H__

#include <unordered_map>
#include <boost/chrono.hpp>
#include "monitor_inter_.h"

namespace monitor {
    class NetMonitor : public MonitorInterface {
    public:
        struct NetInfo {
            std::string name;
            int64_t rcv_bytes;
            int64_t rcv_packets;
            int64_t err_in;
            int64_t drop_in;
            int64_t snd_bytes;
            int64_t snd_packets;
            int64_t err_out;
            int64_t drop_out;
            boost::chrono::steady_clock::time_point timepoint;
        };
        NetMonitor() {};
        void updateOnce(monitor::proto::MonitorInfo *monitorInfo) override;
        void stop() override {};
    private:
        std::unordered_map<std::string, NetInfo> m_net_info;
    };
}

/*
    bytes: （接口发送或接收的数据的总字节数）
    packets: （接口发送或接收的数据包总数）
    errs:（由设备驱动程序检测到的发送或接收错误的总数）
    drop: （设备驱动程序丢弃的数据包总数）
    fifo: （FIFO缓冲区错误的数量）
    frame: T（分组帧错误的数量）
    colls: （接口上检测到的冲突数）
    compressed:（设备驱动程序发送或接收的压缩数据包数）
    carrier: （由设备驱动程序检测到的载波损耗的数量）
    multicast: （设备驱动程序发送或接收的多播帧数）
*/
#endif // __NET_MONITOR_H__