#ifndef __MAINWINDOW_H__
#define __MAINWINDOW_H__

#include <QWidget>
#include <QStackedLayout>
#include <QTableView>

#include <string>
#include <thread>

#include "cpu_stat.h"
#include "cpu_load.h"
#include "cpu_softirq.h"
#include "memory_stat.h"
#include "net_stat.h"


namespace monitor {
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

        void updateData(const monitor::proto::MonitorInfo &moniorInfo);  // 更新数据

    private slots:
        void clickCPUButtun();  // 点击CPU按钮
        void clickMemoryButtun();  // 点击内存按钮
        void clickNetButtun();  // 点击网络按钮
        void clickSoftIrqButtun();  // 点击软中断按钮

    private:
        QStackedLayout* m_stacked_meun; // 堆叠布局

        QTableView* m_monitorView;  // 监控视图
        QTableView* m_cpuLoadView;  // CPU负载视图
        QTableView* m_cpuStateView; // CPU状态视图
        QTableView* m_cpuSoftirqView;  // CPU软中断视图
        QTableView* m_memoryView;   // 内存视图
        QTableView* m_netView;      // 网络视图

        CPULoadModel* m_cpu_load_model;  // CPU负载数据模型
        CPUStatModel* m_cpu_stat_model;  // CPU状态数据模型
        CPUSoftIrqModel* m_cpu_softirq_model;  // CPU软中断数据模型
        MemoryModel* m_memory_stat_model;  // 内存数据模型
        NetModel* m_net_stat_model;  // 网络数据模型

        QWidget* m_widget;  // 当前显示的widget
    };
}

#endif // __MAINWINDOW_H__