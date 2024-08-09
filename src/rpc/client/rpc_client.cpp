#include "rpc_client.h"

monitor::RpcClient::RpcClient(const std::string& serverAddress)
    : m_stub(monitor::proto::GrpcManager::NewStub(grpc::CreateChannel(serverAddress, grpc::InsecureChannelCredentials())))
{
    // 不安全通道：grpc::InsecureChannelCredentials()， 安全通道：grpc::SslCredentials()
    // auto channel = grpc::CreateChannel(serverAddress, grpc::InsecureChannelCredentials()); 
    // m_stub = monitor::proto::MonitorService::NewStub(channel);
}

monitor::RpcClient::~RpcClient() 
{
}

void monitor::RpcClient::setInfo(const monitor::proto::MonitorInfo& monitor_info) 
{
    // 客户端发送数据（全局命名空间）
    ::grpc::ClientContext context;      // 客户端上下文
    ::google::protobuf::Empty response; // 空响应
    // 调用gRPC服务
    ::grpc::Status status = m_stub->SetMonitorInfo(&context, monitor_info, &response);

    // 等待调用完成
    if (status.ok()){
    }
    else{
        std::cerr << "Failed to connect!!!" << std::endl;
        std::cerr << status.error_details() << std::endl;
        std::cerr << "Error Message: " << status.error_message() << std::endl;
    }
}

void monitor::RpcClient::getInfo(monitor::proto::MonitorInfo *monito_info)
{
    // 客户端获取数据
    ::grpc::ClientContext context; 
    ::google::protobuf::Empty request; 
    ::grpc::Status status = m_stub->GetMonitorInfo(&context, request, monito_info);

    if (status.ok()){
    }
    else{
        std::cerr << "Failed to connect!!!" << std::endl;
        std::cerr << status.error_details() << std::endl;
        std::cerr << "Error Message: " << status.error_message() << std::endl;
    }

}
