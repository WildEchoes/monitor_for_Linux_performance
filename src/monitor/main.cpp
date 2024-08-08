#include <memory>
#include <thread>
#include <vector>
#include <chrono>

#include "monitor_inter_.h"
#include "cpu_load_monitor.h"
#include "cpu_stat_monitor.h"
#include "cpu_softirq_monitor.h"
#include "memory_monitor.h"
#include "net_monitor.h"

#include "client/rpc_client.h"

#include "monitor_info.pb.h"
#include "monitor_info.grpc.pb.h"

int main(){
    std::vector<std::unique_ptr<monitor::MonitorInterface>> manarger;
    manarger.push_back(std::make_unique<monitor::CPULoadMonitor>());
    manarger.push_back(std::make_unique<monitor::CPUStatMonitor>());
    manarger.push_back(std::make_unique<monitor::CPUSoftIRQMonitor>());
    manarger.push_back(std::make_unique<monitor::MemoryMonitor>());
    manarger.push_back(std::make_unique<monitor::NetMonitor>());

    monitor::RpcClient client;  // 构建客户端服务
    char *name = getenv("USER");

    std::unique_ptr<std::thread> thread_{
        std::make_unique<std::thread>(
            [&](){
                while(true){
                    monitor::proto::MonitorInfo info{};
                    info.set_name(name);
                    // 更新监控信息
                    for(auto& member : manarger){
                        member->updateOnce(&info);
                    }
                    client.setInfo(info);
                    std::this_thread::sleep_for(std::chrono::seconds(3));
                }
            }
        )
    };
    
    thread_->join();
    return 0;
}