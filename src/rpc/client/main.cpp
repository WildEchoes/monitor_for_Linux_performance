#include <string>
#include "rpc_client.h"
#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

int main() {
    monitor::proto::MonitorInfo info;
    
    
    monitor::RpcClient client;
    client.setInfo(info);

    return 0;
}
    