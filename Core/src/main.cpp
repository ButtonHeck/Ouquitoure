#include "CoreAppWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CoreAppWindow w;
    w.setWindowTitle("Rename me");
    w.show();
    return a.exec();
}
