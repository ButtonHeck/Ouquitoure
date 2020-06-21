#include "CoreAppWindow"

#include <QToolBar>

#include "ui_core_app_window.h"
#include "AppCollectionModel"
#include "AppType"
#include "Log"
#include "OpenGLApps/OpenGLAppBase"
#include "SoftwareApps/SoftwareAppBase"

namespace Ouquitoure
{
    CoreAppWindow::CoreAppWindow( QWidget * parent )
        : QMainWindow(parent)
        , ui( new Ui::CoreAppWindow )
        , openGLAppsCollectionModel( new AppCollectionModel{this} )
        , softwareAppsCollectionModel( new AppCollectionModel{this} )
    {
        ui->setupUi(this);

        //opengl stuff
        ui->openGLApps->setModel(openGLAppsCollectionModel);
        connect(ui->openGLApps, SIGNAL(clicked(const QModelIndex &)), openGLAppsCollectionModel, SLOT(tableEntryClick(const QModelIndex &)));
        connect(ui->openGLApps, SIGNAL(doubleClicked(const QModelIndex &)), SLOT(launchApp()));
        for (const auto & appInfo : appLibraryManager.getAppInfos(OPENGL_APP))
        {
            openGLAppsCollectionModel->addAppInfoEntry( appInfo );
        }

        //software stuff
        ui->softwareApps->setModel(softwareAppsCollectionModel);
        connect(ui->softwareApps, SIGNAL(clicked(const QModelIndex &)), softwareAppsCollectionModel, SLOT(tableEntryClick(const QModelIndex &)));
        connect(ui->softwareApps, SIGNAL(doubleClicked(const QModelIndex &)), SLOT(launchApp()));
        for (const auto & appInfo : appLibraryManager.getAppInfos(SOFTWARE_APP))
        {
            softwareAppsCollectionModel->addAppInfoEntry(appInfo);
        }

        connect(ui->launchAppButton, SIGNAL(clicked()), SLOT(launchApp()));
    }

    CoreAppWindow::~CoreAppWindow()
    {
        delete ui;
    }

    bool CoreAppWindow::launchApp()
    {
        const APP_TYPE appType = [&]()
        {
            const auto APP_TABLE_VIEW_CURRENT_TAB_INDEX = ui->appLibraryTabWidget->currentIndex();
            switch(APP_TABLE_VIEW_CURRENT_TAB_INDEX)
            {
            case 0:
                return OPENGL_APP;
            case 1:
                return SOFTWARE_APP;
            default:
                throw std::runtime_error("Not suitable app type for table view tab index");
            }
        }();

        const QString appName = [&](const APP_TYPE TYPE)
        {
            switch(TYPE)
            {
            case OPENGL_APP:
                return openGLAppsCollectionModel->getCurrentAppInfo().getName();
            case SOFTWARE_APP:
                return softwareAppsCollectionModel->getCurrentAppInfo().getName();
            default:
                throw std::invalid_argument("Not suitable application type");
            }
        }(appType);
        OQ_LOG_INFO << appName << "sender:(" << sender()->objectName() << ")";

        QMainWindow * appWindow = appLibraryManager.getApplication(appType, appName);
        if (appWindow)
        {
            appWindow->isHidden() ? appWindow->show() : appWindow->activateWindow();
            return true;
        }
        return false;
    }
}
