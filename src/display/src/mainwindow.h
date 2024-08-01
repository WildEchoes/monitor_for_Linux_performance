#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QWidget>
#include <QStackedLayout>
#include <QTableView>

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

        //void updateData();  // 更新数据

    private slots:
        void clickCPUButtun();  // 点击CPU按钮
        void clickMemoryButtun();  // 点击内存按钮
        void clickNetButtun();  // 点击网络按钮
        void clickSoftIrqButtun();  // 点击软中断按钮

    private:
        QStackedLayout* m_stacked_meun;

        QTableView* m_monitorView;  // 监控视图
        QTableView* m_cpuLoadView;  // CPU负载视图
        QTableView* m_cpuStateView; // CPU状态视图
        QTableView* m_memoryView;   // 内存视图
        QTableView* m_netView;      // 网络视图
    };
}

#endif // __MAINWINDOW_H__