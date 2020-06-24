#include "CoreAppWindow"

#include <QToolBar>

#include "AppCollectionModel"
#include "AppType"
#include "Log"
#include "OpenGLApps/OpenGLAppBase"
#include "SoftwareApps/SoftwareAppBase"
#include "ui_core_app_window.h"

namespace Ouquitoure
{
    CoreAppWindow::CoreAppWindow( QWidget * parent )
        : QMainWindow( parent )
        , ui( new Ui::CoreAppWindow )
        , openGLAppsCollectionModel( new AppCollectionModel{ this } )
        , softwareAppsCollectionModel( new AppCollectionModel{ this } )
        , appLibraryManager( *openGLAppsCollectionModel, *softwareAppsCollectionModel )
    {
        ui->setupUi( this );
        setWindowIcon( QIcon( ":/icons/logo.ico" ) );
        setWindowTitle( "Ouquitoure sandbox" );
        QToolBar * toolbar = new QToolBar( "Toolbar", this );
        addToolBar( toolbar );
        toolbar->addAction( QIcon( ":/icons/show_description_icon.png" ), "Show description", this,
                            SLOT( switchDescriptionWindowVisible() ) );

        // opengl stuff
        ui->openGLAppsView->setModel( openGLAppsCollectionModel );
        connect( ui->openGLAppsView, SIGNAL( clicked( const QModelIndex & ) ), openGLAppsCollectionModel,
                 SLOT( tableEntryClick( const QModelIndex & ) ) );
        connect( ui->openGLAppsView, SIGNAL( clicked( const QModelIndex & ) ), this,
                 SLOT( updateDescriptionWindowInfo() ) );
        connect( ui->openGLAppsView, SIGNAL( doubleClicked( const QModelIndex & ) ), SLOT( launchApp() ) );

        // software stuff
        ui->softwareAppsView->setModel( softwareAppsCollectionModel );
        connect( ui->softwareAppsView, SIGNAL( clicked( const QModelIndex & ) ), softwareAppsCollectionModel,
                 SLOT( tableEntryClick( const QModelIndex & ) ) );
        connect( ui->softwareAppsView, SIGNAL( clicked( const QModelIndex & ) ), this,
                 SLOT( updateDescriptionWindowInfo() ) );
        connect( ui->softwareAppsView, SIGNAL( doubleClicked( const QModelIndex & ) ), SLOT( launchApp() ) );

        connect( ui->launchAppButton, SIGNAL( clicked() ), SLOT( launchApp() ) );
    }

    CoreAppWindow::~CoreAppWindow()
    {
        delete ui;
    }

    bool CoreAppWindow::launchApp()
    {
        const APP_TYPE appType = getAppType();
        const QString  appName = getAppName( appType );
        OQ_LOG_INFO << appName << "sender:(" << sender()->objectName() << ")";

        switch( appType )
        {
        case OPENGL_APP:
        {
            AppWindowBase * appWindow = openGLAppsCollectionModel->getApplication( appName );
            if( appWindow )
            {
                appWindow->isHidden() ? appWindow->show() : appWindow->activateWindow();
                return true;
            }
        }
        case SOFTWARE_APP:
        {
            AppWindowBase * appWindow = softwareAppsCollectionModel->getApplication( appName );
            if( appWindow )
            {
                appWindow->isHidden() ? appWindow->show() : appWindow->activateWindow();
                return true;
            }
        }
        default:
            return false;
        }
    }

    void CoreAppWindow::updateDescriptionWindowInfo()
    {
        const APP_TYPE appType = getAppType();
        const QString  appName = getAppName( appType );

        AppWindowBase * appWindow = nullptr;
        if( appType == OPENGL_APP )
        {
            appWindow = openGLAppsCollectionModel->getApplication( appName );
        }
        else if( appType == SOFTWARE_APP )
        {
            appWindow = softwareAppsCollectionModel->getApplication( appName );
        }
        if( appWindow )
        {
            ui->descriptionView->setHtml( appWindow->getInfo().getDescription().getFullDescription() );
        }
    }

    void CoreAppWindow::switchDescriptionWindowVisible()
    {
        if( ui->descriptionDockWidget->isHidden() )
        {
            ui->descriptionDockWidget->show();
        }
        else
        {
            ui->descriptionDockWidget->hide();
        }
    }

    APP_TYPE CoreAppWindow::getAppType()
    {
        const auto APP_TABLE_VIEW_CURRENT_TAB_INDEX = ui->appLibraryTabWidget->currentIndex();
        switch( APP_TABLE_VIEW_CURRENT_TAB_INDEX )
        {
        case 0:
            return OPENGL_APP;
        case 1:
            return SOFTWARE_APP;
        default:
            throw std::runtime_error( "Not suitable app type for table view tab index" );
        }
    }

    QString CoreAppWindow::getAppName( APP_TYPE type )
    {
        switch( type )
        {
        case OPENGL_APP:
            return openGLAppsCollectionModel->getCurrentAppInfo().getName();
        case SOFTWARE_APP:
            return softwareAppsCollectionModel->getCurrentAppInfo().getName();
        default:
            throw std::invalid_argument( "Not suitable application type" );
        }
    }
} // namespace Ouquitoure
