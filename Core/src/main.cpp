#include "core_app_window.h"
#include "logger.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Ouquitoure::CoreAppWindow window;
    qInstallMessageHandler(Ouquitoure::Logger::logHandler);
    window.setWindowTitle("Rename me");
    window.show();

    return a.exec();
}
