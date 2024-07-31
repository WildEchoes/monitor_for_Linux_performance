#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QMainWindow>
#include <QWidget>
#include <QStackedLayout>
#include <string>
#include <thread>

namespace monior {
    class MonitorWindow : public QWidget {
        Q_OBJECT
    public:
        explicit MonitorWindow(QWidget *parent = nullptr);
        ~MonitorWindow();

        QWidget* showAllWidget(const std::string& name); // 显示所有的监控模块
        QWidget* initCPUMonitorWidget();  // 初始化CPU监控模块
        QWidget* initMemoryMonitorWidget();  // 初始化内存监控模块
        QWidget* initNetMonitorWidget();  // 初始化网络监控模块
        QWidget* initSoftIrqMonitorWidget();  // 初始化软中断监控模块
        QWidget* initButtunWidget(const std::string& name);  // 初始化按钮模块

    private:
        QStackedLayout* m_stacked_meun;
    };
}

#endif // __MAINWINDOW_H__