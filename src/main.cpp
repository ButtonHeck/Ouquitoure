#include "CoreAppWindow"
#include "Log"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Ouquitoure::CoreAppWindow window;
    qInstallMessageHandler(Ouquitoure::logHandler);
    window.setWindowTitle("Rename me");
    window.show();

    return a.exec();
}
