#include "AppSelector.h"
#include "ui_AppSelector.h"

AppSelector::AppSelector( QWidget * parent ) :
    QWidget(parent),
    ui( new Ui::AppSelector )
{
    ui->setupUi(this);
}

AppSelector::~AppSelector()
{
    delete ui;
}
