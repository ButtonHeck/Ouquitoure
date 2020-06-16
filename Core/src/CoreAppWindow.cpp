#include "CoreAppWindow.h"
#include "ui_CoreAppWindow.h"
#include "AppCollectionModel.h"
#include "HelloApp.h"
#include <QDebug>
#include <QToolBar>

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
        connect(ui->OpenGLApps, SIGNAL(doubleClicked(const QModelIndex &)), SLOT(launchApp()));

        QToolBar * toolbar = new QToolBar("Toolbar", this);
        addToolBar(toolbar);
        toolbar->setIconSize(QSize(32, 32));

        const QIcon LOG_ICON {":/icons/log_icon.png"};
        toolbar->addAction(LOG_ICON, "Log", this, SLOT(switchLogVisibility()));
        const QIcon LOG_SETTINGS_ICON{":/icons/settings.png"};
        toolbar->addAction(LOG_SETTINGS_ICON, "Log settings");

        addDockWidget(Qt::BottomDockWidgetArea, ui->logDockWidget);
        ui->logDockWidget->setWindowTitle("Log window");
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

    void CoreAppWindow::switchLogVisibility()
    {
        ui->logDockWidget->setVisible(!ui->logDockWidget->isVisible());
    }
}
