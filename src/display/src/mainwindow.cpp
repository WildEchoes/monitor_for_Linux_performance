#include "mainwindow.h"

#include <QPushButton>
#include <QLabel>

namespace monior {
    MonitorWindow::MonitorWindow(QWidget *parent) 
    : QWidget(parent) 
    , m_widget(new QWidget())
    , m_stacked_meun(new QStackedLayout())
    , m_monitorView(new QTableView(m_widget))
    , m_cpuLoadView(new QTableView(m_widget))
    , m_cpuStateView(new QTableView(m_widget))
    , m_memoryView(new QTableView(m_widget))
    , m_netView(new QTableView(m_widget))
    
    {
        this->setWindowTitle("Monior For Linux");
        this->setFixedSize(800, 600);
        // qDebug() << "MonitorWindow";
    }

    MonitorWindow::~MonitorWindow() {
        delete m_widget;

        m_widget = nullptr;
    }

    QWidget* MonitorWindow::showAllWidget(const std::string& name) {
        // 初始化监控模块
        m_stacked_meun->addWidget(initCPUMonitorWidget());
        m_stacked_meun->addWidget(initMemoryMonitorWidget());
        m_stacked_meun->addWidget(initNetMonitorWidget());
        m_stacked_meun->addWidget(initSoftIrqMonitorWidget());

        QGridLayout* layout = new QGridLayout();  // 不要添加this
        layout->addWidget(initButtunWidget(name), 1, 0); // 添加按钮模块
        layout->addLayout(m_stacked_meun, 2, 0);  // 添加监控模块
        m_widget->setLayout(layout);  // 设置布局

        return m_widget;
    }

    QWidget *MonitorWindow::initCPUMonitorWidget()
    {
        QWidget* widget = new QWidget(m_widget);

        // CPU负载
        QLabel* cpuLoadLabel = new QLabel(m_widget);
        cpuLoadLabel->setText(tr("CPU Load")); // 设置标签内容(自动翻译)
        cpuLoadLabel->setFont(QFont("Microsoft YaHei", 10, 40)); // 设置字体

        
        return widget;
    }

    QWidget *MonitorWindow::initMemoryMonitorWidget()
    {
        QWidget *widget = new QWidget(m_widget);
        return widget;
    }

    QWidget *MonitorWindow::initNetMonitorWidget()
    {
        QWidget *widget = new QWidget(m_widget);
        return widget;
    }

    QWidget *MonitorWindow::initSoftIrqMonitorWidget()
    {
        QWidget *widget = new QWidget(m_widget);
        return widget;
    }

    QWidget *MonitorWindow::initButtunWidget(const std::string &name)
    {
        // 设置按钮参数
        QPushButton* cpu_button = new QPushButton(QString::fromStdString(name + " CPU"), m_widget);
        QPushButton* memory_button = new QPushButton(QString::fromStdString(name + " Memory"), m_widget);
        QPushButton* net_button = new QPushButton(QString::fromStdString(name + " Net"), m_widget);
        QPushButton* softirq_button = new QPushButton(QString::fromStdString(name + " SoftIrq"), m_widget);
        QFont font{"Microsoft YaHei", 15, 40};
        cpu_button->setFont(font);
        memory_button->setFont(font);
        net_button->setFont(font);
        softirq_button->setFont(font);

        // 设置布局
        QHBoxLayout* layout = new QHBoxLayout();
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
