#ifndef __RPC_CLIENT_H__
#define __RPC_CLIENT_H__

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/grpcpp.h>
#include <string>
#include <memory>

#include "monitor_info.pb.h"
#include "monitor_info.grpc.pb.h"

namespace monitor {
    class RpcClient {
    public:
        explicit RpcClient(const std::string& serverAddress = "localhost:50051");
        virtual ~RpcClient();

        // 设置监控信息
        void setInfo(const monitor::proto::MonitorInfo& monito_info);  
        // 获取监控信息
        void getInfo(monitor::proto::MonitorInfo* monito_info); 

    private:
        std::unique_ptr<monitor::proto::GrpcManager::Stub> m_stub; // 本地代理
    };
}

#endif // __RPC_CLIENT_H__