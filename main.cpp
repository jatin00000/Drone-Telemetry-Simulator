#include <QApplication>

#include "MainWindow.h"

#include "Logger.h"

int main(int argc, char *argv[])

{

    QApplication a(argc, argv);

    // ensure our TelemetrySnapshot type is registered (also in TelemetryTypes.cpp)

    qRegisterMetaType<TelemetrySnapshot>("TelemetrySnapshot");

    qRegisterMetaType<TelemetrySnapshot::GpsFix>("TelemetrySnapshot::GpsFix");

    MainWindow w;

    w.show();

    Logger::instance().log("Application started.");

    return a.exec();
}