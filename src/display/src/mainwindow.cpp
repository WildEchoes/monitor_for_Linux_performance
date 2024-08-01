#include "mainwindow.h"

#include <QPushButton>

namespace monior {
    MonitorWindow::MonitorWindow(QWidget *parent) 
    : QWidget(parent) 
    , m_stacked_meun(new QStackedLayout(this))
    , m_monitorView(new QTableView(this))
    , m_cpuLoadView(new QTableView(this))
    , m_cpuStateView(new QTableView(this))
    , m_memoryView(new QTableView(this))
    , m_netView(new QTableView(this))
    {
        // this->setWindowTitle("Monior For Linux");
        // this->setFixedSize(800, 600);
    }

    MonitorWindow::~MonitorWindow() {
        delete m_stacked_meun;
        delete m_monitorView;
        delete m_cpuLoadView;
        delete m_cpuStateView;
        delete m_memoryView;
        delete m_netView;

        m_stacked_meun = nullptr;
        m_monitorView = nullptr;
        m_cpuLoadView = nullptr;
        m_cpuStateView = nullptr;
        m_memoryView = nullptr;
        m_netView = nullptr;
    }

    QWidget* MonitorWindow::showAllWidget(const std::string& name) {
        QWidget* widget = new QWidget(this);

        // 初始化按钮模块
        m_stacked_meun->addWidget(initCPUMonitorWidget());
        m_stacked_meun->addWidget(initMemoryMonitorWidget());
        m_stacked_meun->addWidget(initNetMonitorWidget());
        m_stacked_meun->addWidget(initSoftIrqMonitorWidget());

        QGridLayout* layout = new QGridLayout(this);
        layout->addWidget(initButtunWidget(name), 1, 0); // 添加按钮模块
        layout->addLayout(m_stacked_meun, 2, 0);  // 添加监控模块
        widget->setLayout(layout);  // 设置布局

        return widget;
    }

    QWidget *MonitorWindow::initCPUMonitorWidget()
    {
        QWidget *widget = new QWidget(this);
        return widget;
    }

    QWidget *MonitorWindow::initMemoryMonitorWidget()
    {
        QWidget *widget = new QWidget(this);
        return widget;
    }

    QWidget *MonitorWindow::initNetMonitorWidget()
    {
        QWidget *widget = new QWidget(this);
        return widget;
    }

    QWidget *MonitorWindow::initSoftIrqMonitorWidget()
    {
        QWidget *widget = new QWidget(this);
        return widget;
    }

    QWidget *MonitorWindow::initButtunWidget(const std::string &name)
    {
        // 设置按钮参数
        QPushButton* cpu_button = new QPushButton(QString::fromStdString(name + " CPU"), this);
        QPushButton* memory_button = new QPushButton(QString::fromStdString(name + " Memory"), this);
        QPushButton* net_button = new QPushButton(QString::fromStdString(name + " Net"), this);
        QPushButton* softirq_button = new QPushButton(QString::fromStdString(name + " SoftIrq"), this);
        QFont font{"Microsoft YaHei", 15, 40};
        cpu_button->setFont(font);
        memory_button->setFont(font);
        net_button->setFont(font);
        softirq_button->setFont(font);

        // 设置布局
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(cpu_button);
        layout->addWidget(memory_button);
        layout->addWidget(net_button);
        layout->addWidget(softirq_button);

        QWidget* widget = new QWidget(this);
        widget->setLayout(layout);

        // 连接信号槽
        connect(cpu_button, &QPushButton::clicked, this, &MonitorWindow::clickCPUButtun);
        connect(memory_button, &QPushButton::clicked, this, &MonitorWindow::clickMemoryButtun);
        connect(net_button, &QPushButton::clicked, this, &MonitorWindow::clickNetButtun);
        connect(softirq_button, &QPushButton::clicked, this, &MonitorWindow::clickSoftIrqButtun);

        return widget;
    }

    void MonitorWindow::clickCPUButtun()
    {
        // 更改显示的监控模块
        m_stacked_meun->setCurrentIndex(0);
    }

    void MonitorWindow::clickMemoryButtun()
    {
        m_stacked_meun->setCurrentIndex(1);
    }

    void MonitorWindow::clickNetButtun()
    {
        m_stacked_meun->setCurrentIndex(2);
    }

    void MonitorWindow::clickSoftIrqButtun()
    {
        m_stacked_meun->setCurrentIndex(3);
    }
}
