#include <QApplication>
#include <thread>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    std::string name{"Display1"};

    monior::MonitorWindow monior_window;

    QWidget* widget = monior_window.showAllWidget(name);

    widget->show();
    // monior_window.show();

    return app.exec();
}