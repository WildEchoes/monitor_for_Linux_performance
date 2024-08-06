#include <grpc/grpc.h>  
#include <grpcpp/server_builder.h>
#include <memory>
#include "rpc_server.h"

void initServer(const grpc::string& server_and_port = "0.0.0.0:50051")
{
    grpc::ServerBuilder builder;  // 创建服务器构建器
    // 添加监听地址
    builder.AddListeningPort(server_and_port, grpc::InsecureServerCredentials());

    // 注册服务
    monitor::RPCServer rpc_server;
    builder.RegisterService(&rpc_server);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());  // 创建服务器
    server->Wait();  // 等待服务器退出
}

int main()
{
    initServer();
    return 0;
}