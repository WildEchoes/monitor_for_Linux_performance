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

void monitor::RpcClient::sendInfo(const monitor::proto::MonitorInfo& monitor_info) 
{
    // 客户端发送数据（全局命名空间）
    ::grpc::ClientContext context;

}

void monitor::RpcClient::getInfo(monitor::proto::MonitorInfo &monito_info)
{
}
