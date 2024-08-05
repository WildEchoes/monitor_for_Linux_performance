#ifndef __RPC_CLIENT_H__
#define __RPC_CLIENT_H__

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/grpcpp.h>
#include <string>
#include <memory>

namespace monitor {
    class RpcClient {
    public:
        explicit RpcClient(const std::string& serverAddress = "localhost:50051");
        virtual ~RpcClient();

        void sendInfo(const monitor::proto::MonitorInfo& monito_info);
        void getInfo(monitor::proto::MonitorInfo& monito_info);

    private:
        std::unique_ptr<monitor::proto::MonitorService::Stub> m_stub; // 本地代理
    };
}

#endif // __RPC_CLIENT_H__