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
        , invisibleParentForApps()
    {
        ui->setupUi(this);

        //opengl stuff
        ui->openGLApps->setModel(openGLAppsCollectionModel);
        connect(ui->openGLApps, SIGNAL(clicked(const QModelIndex &)), openGLAppsCollectionModel, SLOT(tableTokenClick(const QModelIndex &)));
        connect(ui->openGLApps, SIGNAL(doubleClicked(const QModelIndex &)), SLOT(launchApp()));
        openGLAppsCollectionModel->addAppInfoEntry( AppInfo("hello app", {"tag1", "tag2"}, OPENGL_APP) );

        //software stuff
        ui->softwareApps->setModel(softwareAppsCollectionModel);
        connect(ui->softwareApps, SIGNAL(clicked(const QModelIndex &)), softwareAppsCollectionModel, SLOT(tableTokenClick(const QModelIndex &)));
        connect(ui->softwareApps, SIGNAL(doubleClicked(const QModelIndex &)), SLOT(launchApp()));

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


        QString APP_NAME_FROM_MODEL;
        QVector<AppTableEntry> * appStorage = [&](const APP_TYPE TYPE)
        {
            switch(TYPE)
            {
            case OPENGL_APP:
                APP_NAME_FROM_MODEL = openGLAppsCollectionModel->getCurrentAppInfo().getName();
                return &openGLAppCollection;
            case SOFTWARE_APP:
                APP_NAME_FROM_MODEL = softwareAppsCollectionModel->getCurrentAppInfo().getName();
                return &softwareAppCollection;
            default:
                throw std::invalid_argument("Not suitable application type");
            }
        }(appType);
        OQ_LOG_INFO << APP_NAME_FROM_MODEL << "sender:(" << sender()->objectName() << ")";


        auto appEntry = std::find_if(appStorage->cbegin(), appStorage->cend(), [&](const AppTableEntry app)
        {
            OQ_LOG_INFO << APP_NAME_FROM_MODEL << app.first;
            return APP_NAME_FROM_MODEL == app.first;
        });
        if (appEntry == appStorage->cend())
        {
            if (appType == OPENGL_APP)
            {
//                OpenGLAppBase * newApp = new OpenGLAppBase{&invisibleParentForApps};
//                appStorage->push_back(QPair{APP_NAME_FROM_MODEL, newApp});
//                newApp->show();
            }
            else
            {
//                SoftwareAppBase * newApp = new SoftwareAppBase{&invisibleParentForApps};
//                appStorage->push_back(QPair{APP_NAME_FROM_MODEL, newApp});
//                newApp->show();
            }
        }
        else
        {
            QMainWindow * window = appEntry->second;
            window->isHidden() ? window->show() : window->activateWindow();
        }
        return true;
    }
}
