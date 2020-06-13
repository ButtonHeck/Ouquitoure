#include "CoreAppWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Ouquitoure::CoreAppWindow window;
    window.setWindowTitle("Rename me");
    window.show();

    return a.exec();
}
