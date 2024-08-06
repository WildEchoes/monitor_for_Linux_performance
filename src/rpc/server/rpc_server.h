#ifndef __RPC_SERVER_H__
#define __RPC_SERVER_H__

#include <grpcpp/support/status.h>

#include "monitor_info.grpc.pb.h"
#include "monitor_info.pb.h"

namespace monitor {
    class RPCServer final : public monitor::proto::GrpcManager::Service {
        public:
            RPCServer();
            virtual ~RPCServer();

            // 设置监控信息
            ::grpc::Status SetMonitorInfo(
                ::grpc::ServerContext* context,
                const ::monitor::proto::MonitorInfo* request,
                ::google::protobuf::Empty* response
            ) override;

            // 获取监控信息
            ::grpc::Status GetMonitorInfo(
                ::grpc::ServerContext* context,
                const ::google::protobuf::Empty* request,
                ::monitor::proto::MonitorInfo* response
            ) override;

        private:
            monitor::proto::MonitorInfo m_monitor_info;  // 监控信息
    };
} // namespace monitor

#endif // __RPC_SERVER_H__