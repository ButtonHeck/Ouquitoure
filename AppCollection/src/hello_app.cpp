#include "hello_app.h"
#include <QLabel>
#include <QDebug>

HelloApp::HelloApp(QWidget * parent)
    : QMainWindow(parent)
{
    setGeometry(100, 100, 300, 300);
    QLabel * label = new QLabel(this);
    setWindowTitle("Hello App");
    label->setText("Hello!");
    qDebug() << "HelloApp ctor";
}

HelloApp::~HelloApp()
{
    qDebug() << "HelloApp dtor";
}
