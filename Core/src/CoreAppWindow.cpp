#include "CoreAppWindow.h"
#include "ui_CoreAppWindow.h"
#include "AppCollectionModel.h"
#include "src/HelloApp.h"
#include <QDebug>

namespace Ouquitoure
{
    CoreAppWindow::CoreAppWindow( QWidget * parent )
        : QMainWindow(parent)
        , ui( new Ui::CoreAppWindow )
        , OpenGLAppsCollectionModel( new AppCollectionModel(this) )
        , softwareAppsCollectionModel( new AppCollectionModel(this) )
        , invisibleParentForApps()
    {
        ui->setupUi(this);
        ui->OpenGLApps->setModel(OpenGLAppsCollectionModel);
        ui->SoftwareApps->setModel(softwareAppsCollectionModel);

        connect(ui->OpenGLApps, SIGNAL(clicked(const QModelIndex &)), OpenGLAppsCollectionModel, SLOT(debugMouseClickSlot(const QModelIndex &)));
        connect(ui->OpenGLApps, SIGNAL(doubleClicked(const QModelIndex &)), OpenGLAppsCollectionModel, SLOT(debugDoubleMouseClickSlot(const QModelIndex &)));

        OpenGLAppsCollectionModel->addNewAppData("hello app", "tag1; tag2");
        OpenGLAppsCollectionModel->addNewAppData("fucking awesome app!", "holy shit this is amazing!!");

        connect(ui->launchAppButton, SIGNAL(clicked()), SLOT(launchApp()));
    }

    CoreAppWindow::~CoreAppWindow()
    {
        delete ui;
    }

    bool CoreAppWindow::launchApp()
    {
        QString currentAppName = OpenGLAppsCollectionModel->getCurrentAppData().first;
        qDebug() << currentAppName;
        if (currentAppName == "hello app")
        {
            auto findResult = std::find_if(apps.cbegin(), apps.cend(), [&](const QPair<QString, QMainWindow*> app)
            {
                qDebug() << currentAppName << app.first;
                return currentAppName == app.first;
            });
            if (findResult == apps.cend())
            {
                HelloApp * newApp = new HelloApp{&invisibleParentForApps};
                apps << QPair{currentAppName, newApp};
                newApp->show();
            }
            else
            {
                QMainWindow * window = findResult->second;
                window->isHidden() ? window->show() : window->activateWindow();
            }
            return true;
        }
        return false;
    }
}
