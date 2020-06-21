#include "CoreAppWindow"
#include "Log"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qInstallMessageHandler(Ouquitoure::logHandler);
    Ouquitoure::CoreAppWindow window;
    window.show();

    return a.exec();
}
