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

        // opengl stuff
        ui->openGLAppsView->setModel( openGLAppsCollectionModel );
        connect( ui->openGLAppsView, SIGNAL( clicked( const QModelIndex & ) ), openGLAppsCollectionModel,
                 SLOT( tableEntryClick( const QModelIndex & ) ) );
        connect( ui->openGLAppsView, SIGNAL( doubleClicked( const QModelIndex & ) ), SLOT( launchApp() ) );

        // software stuff
        ui->softwareAppsView->setModel( softwareAppsCollectionModel );
        connect( ui->softwareAppsView, SIGNAL( clicked( const QModelIndex & ) ), softwareAppsCollectionModel,
                 SLOT( tableEntryClick( const QModelIndex & ) ) );
        connect( ui->softwareAppsView, SIGNAL( doubleClicked( const QModelIndex & ) ), SLOT( launchApp() ) );

        connect( ui->launchAppButton, SIGNAL( clicked() ), SLOT( launchApp() ) );
    }

    CoreAppWindow::~CoreAppWindow()
    {
        delete ui;
    }

    bool CoreAppWindow::launchApp()
    {
        const APP_TYPE appType = [ & ]() {
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
        }();

        const QString appName = [ & ]( const APP_TYPE TYPE ) {
            switch( TYPE )
            {
            case OPENGL_APP:
                return openGLAppsCollectionModel->getCurrentAppInfo().getName();
            case SOFTWARE_APP:
                return softwareAppsCollectionModel->getCurrentAppInfo().getName();
            default:
                throw std::invalid_argument( "Not suitable application type" );
            }
        }( appType );
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
} // namespace Ouquitoure
