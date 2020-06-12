#include "CoreAppWindow.h"
#include "ui_CoreAppWindow.h"

CoreAppWindow::CoreAppWindow( QWidget * parent )
    : QMainWindow(parent)
    , ui( new Ui::CoreAppWindow )
{
    ui->setupUi(this);
}

CoreAppWindow::~CoreAppWindow()
{
    delete ui;
}

