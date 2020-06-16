#include "CoreAppWindow.h"
#include "ui_CoreAppWindow.h"
#include "AppCollectionModel.h"

namespace Ouquitoure
{
    CoreAppWindow::CoreAppWindow( QWidget * parent )
        : QMainWindow(parent)
        , ui( new Ui::CoreAppWindow )
        , OpenGLAppsCollectionModel( new AppCollectionModel(this) )
        , softwareAppsCollectionModel( new AppCollectionModel(this) )
    {
        ui->setupUi(this);
        ui->OpenGLApps->setModel(OpenGLAppsCollectionModel);
        ui->SoftwareApps->setModel(softwareAppsCollectionModel);

        connect(ui->OpenGLApps, SIGNAL(clicked(const QModelIndex &)), OpenGLAppsCollectionModel, SLOT(debugMouseClickSlot(const QModelIndex &)));
        connect(ui->OpenGLApps, SIGNAL(doubleClicked(const QModelIndex &)), OpenGLAppsCollectionModel, SLOT(debugDoubleMouseClickSlot(const QModelIndex &)));

        OpenGLAppsCollectionModel->addNewAppData("hello app", "tag1; tag2");
        OpenGLAppsCollectionModel->addNewAppData("fucking awesome app!", "holy shit this is amazing!!");
    }

    CoreAppWindow::~CoreAppWindow()
    {
        delete ui;
    }
}
