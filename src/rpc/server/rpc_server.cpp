#include "rpc_server.h"
#include <iostream>

monitor::RPCServer::RPCServer()
    : m_monitor_info(monitor::proto::MonitorInfo())
{
}

monitor::RPCServer::~RPCServer()
{
}

::grpc::Status monitor::RPCServer::SetMonitorInfo(
    ::grpc::ServerContext *context, 
    const ::monitor::proto::MonitorInfo *request, 
    ::google::protobuf::Empty *response)
{
    m_monitor_info.Clear();  // 清空原有数据
    // m_monitor_info = *request;
    m_monitor_info.CopyFrom(*request);
    // std::cout << "soft irq size: " << request->soft_irq_size() << std::endl;
    // std::cout << "Server running... " << m_monitor_info.cpu_stat_size() 
    //           << m_monitor_info.net_info_size() << std::endl;

    return ::grpc::Status::OK;
}

::grpc::Status monitor::RPCServer::GetMonitorInfo(
    ::grpc::ServerContext *context, 
    const ::google::protobuf::Empty *request, 
    ::monitor::proto::MonitorInfo *response)
{
    // *response = m_monitor_info;
    response->CopyFrom(m_monitor_info);

    return ::grpc::Status::OK;
}
