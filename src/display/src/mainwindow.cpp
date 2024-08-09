#include "mainwindow.h"

#include <QPushButton>
#include <QLabel>

namespace monitor {
    MonitorWindow::MonitorWindow(QWidget *parent) 
    : QWidget(parent) 
    , m_widget(new QWidget())
    , m_stacked_meun(new QStackedLayout())
    , m_monitorView(new QTableView())
    , m_cpuLoadView(new QTableView())
    , m_cpuStateView(new QTableView())
    , m_cpuSoftirqView(new QTableView())
    , m_memoryView(new QTableView())
    , m_netView(new QTableView())
    , m_cpu_load_model(new CPULoadModel())
    , m_cpu_stat_model(new CPUStatModel())
    , m_cpu_softirq_model(new CPUSoftIrqModel())
    , m_memory_stat_model(new MemoryModel())
    , m_net_stat_model(new NetModel())
    {
        this->setWindowTitle("Monior For Linux");
        this->setFixedSize(800, 600);
        // qDebug() << "MonitorWindow";
    }

    MonitorWindow::~MonitorWindow() {
        delete m_widget;

        m_widget = nullptr;
        m_stacked_meun = nullptr;
        m_monitorView = nullptr;
        m_cpuLoadView = nullptr;
        m_cpuStateView = nullptr;
        m_cpuSoftirqView = nullptr;
        m_memoryView = nullptr;
        m_netView = nullptr;
        m_cpu_load_model = nullptr;
        m_cpu_stat_model = nullptr;
        m_cpu_softirq_model = nullptr;
        m_memory_stat_model = nullptr;
        m_net_stat_model = nullptr;
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
        QWidget* widget = new QWidget();

        // CPU负载
        QLabel* cpuLoadLabel = new QLabel(m_widget);
        cpuLoadLabel->setText(tr("CPU Load")); // 设置标签内容(自动翻译)
        cpuLoadLabel->setFont(QFont("Microsoft YaHei", 10, 40)); // 设置字体

        m_cpuLoadView->setModel(m_cpu_load_model); // 设置数据模型
        m_cpuLoadView->show();

        // CPU状态
        QLabel* cpuStateLabel = new QLabel(m_widget);
        cpuStateLabel->setText(tr("CPU State"));
        cpuStateLabel->setFont(QFont("Microsoft YaHei", 10, 40));

        m_cpuStateView->setModel(m_cpu_stat_model);
        m_cpuStateView->show();

        // 设置布局
        QGridLayout* layout = new QGridLayout();

        layout->addWidget(cpuLoadLabel, 4, 0);
        layout->addWidget(m_cpuLoadView, 5, 0, 2, 2);

        layout->addWidget(cpuStateLabel, 1, 0);
        layout->addWidget(m_cpuStateView, 2, 0, 2, 2);

        widget->setLayout(layout);

        return widget;
    }

    QWidget *MonitorWindow::initMemoryMonitorWidget()
    {
        QWidget *widget = new QWidget();
        
        QLabel* memoryLabel = new QLabel();
        memoryLabel->setText(tr("Memory"));
        memoryLabel->setFont(QFont("Microsoft YaHei", 10, 40));

        m_memoryView->setModel(m_memory_stat_model);
        m_memoryView->show();

        QGridLayout* layout = new QGridLayout();
        layout->addWidget(memoryLabel, 1, 0);
        layout->addWidget(m_memoryView, 2, 0, 4, 2);

        widget->setLayout(layout);

        return widget;
    }

    QWidget *MonitorWindow::initNetMonitorWidget()
    {
        QWidget *widget = new QWidget();

        QLabel* netLabel = new QLabel();
        netLabel->setText(tr("Network"));
        netLabel->setFont(QFont("Microsoft YaHei", 10, 40));

        m_netView->setModel(m_net_stat_model);
        m_netView->show();

        QGridLayout* layout = new QGridLayout();
        layout->addWidget(netLabel, 1, 0);
        layout->addWidget(m_netView, 2, 0, 2, 2);

        widget->setLayout(layout);

        return widget;
    }

    QWidget *MonitorWindow::initSoftIrqMonitorWidget()
    {
        QWidget *widget = new QWidget();

        QLabel* softIrqLabel = new QLabel();
        softIrqLabel->setText(tr("Software Interrupt Request"));

        m_cpuSoftirqView->setModel(m_cpu_softirq_model);
        m_cpuSoftirqView->show();

        QGridLayout* layout = new QGridLayout();
        layout->addWidget(softIrqLabel, 1, 0);
        layout->addWidget(m_cpuSoftirqView, 2, 0, 4, 2);

        widget->setLayout(layout);
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

    void MonitorWindow::updateData(const monitor::proto::MonitorInfo &moniorInfo)
    {
        m_cpu_load_model->UpdateMonitorInfo(moniorInfo);
        m_cpu_stat_model->UpdateMonitorInfo(moniorInfo);
        m_cpu_softirq_model->UpdateMonitorInfo(moniorInfo);
        m_memory_stat_model->UpdateMonitorInfo(moniorInfo);
        m_net_stat_model->UpdateMonitorInfo(moniorInfo);
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
