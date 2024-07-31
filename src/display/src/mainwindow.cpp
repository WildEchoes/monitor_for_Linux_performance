#include "mainwindow.h"

namespace monior {
    MonitorWindow::MonitorWindow(QWidget *parent) 
    : QWidget(parent) 
    , m_stacked_meun(new QStackedLayout(this))
    {
        this->setWindowTitle("Monior For Linux");
        this->setFixedSize(800, 600);
    }

    MonitorWindow::~MonitorWindow() {
        delete m_stacked_meun;

        m_stacked_meun = nullptr;
    }

    QWidget* MonitorWindow::showAllWidget(const std::string& name) {
        QWidget* widget = new QWidget(this);

        // 初始化按钮模块
        // m_stacked_meun = new QStackedLayout();
        m_stacked_meun->addWidget(initCPUMonitorWidget());
        m_stacked_meun->addWidget(initMemoryMonitorWidget());
        m_stacked_meun->addWidget(initNetMonitorWidget());
        m_stacked_meun->addWidget(initSoftIrqMonitorWidget());

        QGridLayout* layout = new QGridLayout(this);
        layout->addWidget(initButtunWidget(name), 1, 0);
        layout->addLayout(m_stacked_meun, 2, 0);
        widget->setLayout(layout);
        return widget;
    }
    
}
