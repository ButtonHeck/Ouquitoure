#include "HelloApp.h"
#include <QLabel>

HelloApp::HelloApp(QWidget * parent)
    : QWidget(parent)
{
    setGeometry(100, 100, 300, 300);
    QLabel * label = new QLabel(this);
    label->setText("Hello!");
}
