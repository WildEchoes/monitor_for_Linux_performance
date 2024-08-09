#include <QApplication>
#include <thread>

#include "mainwindow.h"
#include "client/rpc_client.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 构建rpc服务
    std::string address{"localhost:50051"};
    if (argc > 1) {
        address = argv[1];
    }

    monitor::RpcClient rpc_client{address};
    monitor::proto::MonitorInfo monitor_info{};
    rpc_client.getInfo(&monitor_info);

    std::string name{monitor_info.name()};

    // 构建监控窗口
    monitor::MonitorWindow monitor_window{};
    QWidget* widget = monitor_window.showAllWidget(name);
    widget->show();
    
    // 持续监控
    std::unique_ptr<std::thread> monitor_thread {
        std::make_unique<std::thread>(
            [&](){
                while (true) {
                    rpc_client.getInfo(&monitor_info);
                    monitor_window.updateData(monitor_info);
                    monitor_info.Clear();
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                }
            }
        )
    };

    monitor_thread->detach();

    return app.exec();
}