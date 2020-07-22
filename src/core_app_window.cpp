#include "CoreAppWindow"

#include <QToolBar>
#include <QItemSelectionModel>

#include "AppCollectionModel"
#include "Apps/AppType"
#include "Log"
#include "Apps/OpenGL/OpenGLAppBase"
#include "Apps/Software/SoftwareAppBase"
#include "ui_core_app_window.h"

namespace Ouquitoure
{
    CoreAppWindow::CoreAppWindow( QWidget * parent )
        : QMainWindow( parent )
        , ui( new Ui::CoreAppWindow )
        , openGLAppsCollectionModel( new AppCollectionModel{ this } )
        , softwareAppsCollectionModel( new AppCollectionModel{ this } )
        , appLibraryManager()
    {
        ui->setupUi( this );
        setWindowIcon( QIcon( ":/icons/logo.ico" ) );
        setWindowTitle( "Ouquitoure sandbox" );
        QToolBar * toolbar = new QToolBar( "Toolbar", this );
        addToolBar( toolbar );
        toolbar->addAction( QIcon( ":/icons/show_description_icon.png" ), "Show description", this,
                            SLOT( switchDescriptionWindowVisible() ) );

        // load applications
        connect( &appLibraryManager, SIGNAL( applicationCreated( AppWindowBase *, APP_TYPE ) ), this,
                 SLOT( addApplication( AppWindowBase *, APP_TYPE ) ) );
        appLibraryManager.loadApplications();

        // opengl stuff
        ui->openGLAppsView->setModel( openGLAppsCollectionModel );
        connect( ui->openGLAppsView, SIGNAL( clicked( const QModelIndex & ) ), openGLAppsCollectionModel,
                 SLOT( updateCurrentAppInfo( const QModelIndex & ) ) );
        connect( ui->openGLAppsView, SIGNAL( clicked( const QModelIndex & ) ), this, SLOT( updateDescriptionWindowInfo() ) );
        connect( ui->openGLAppsView, SIGNAL( doubleClicked( const QModelIndex & ) ), SLOT( launchApp() ) );

        // software stuff
        ui->softwareAppsView->setModel( softwareAppsCollectionModel );
        connect( ui->softwareAppsView, SIGNAL( clicked( const QModelIndex & ) ), softwareAppsCollectionModel,
                 SLOT( updateCurrentAppInfo( const QModelIndex & ) ) );
        connect( ui->softwareAppsView, SIGNAL( clicked( const QModelIndex & ) ), this, SLOT( updateDescriptionWindowInfo() ) );
        connect( ui->softwareAppsView, SIGNAL( doubleClicked( const QModelIndex & ) ), SLOT( launchApp() ) );

        // callback to the "Launch" button
        connect( ui->launchAppButton, SIGNAL( clicked() ), SLOT( launchApp() ) );

        // callback to the "App name" input
        connect( ui->appSearchByNameLineEdit, SIGNAL( textChanged( const QString & ) ), SLOT( searchByName( const QString & ) ) );
    }

    CoreAppWindow::~CoreAppWindow()
    {
        delete ui;
    }

    /**
     * @brief slot to launch an application. An application is chosen based on the app name and
     * its type that is currently in the selected state of the view
     */
    bool CoreAppWindow::launchApp()
    {
        const APP_TYPE appType = getAppType();
        const QString  appName = getAppName( appType );
        OQ_LOG_INFO << appName << " sender: " << sender()->objectName();

        switch( appType )
        {
        case OPENGL_APP:
        {
            AppWindowBase * appWindow = openGLAppsCollectionModel->getApplication( appName );
            if( appWindow )
            {
                appWindow->isHidden() ? appWindow->show() : appWindow->activateWindow();
                appWindow->setGeometry( geometry().x(), geometry().y(), appWindow->geometry().width(), appWindow->geometry().height() );
                return true;
            }
        }
        case SOFTWARE_APP:
        {
            AppWindowBase * appWindow = softwareAppsCollectionModel->getApplication( appName );
            if( appWindow )
            {
                appWindow->isHidden() ? appWindow->show() : appWindow->activateWindow();
                appWindow->setGeometry( geometry().x(), geometry().y(), appWindow->geometry().width(), appWindow->geometry().height() );
                return true;
            }
        }
        default:
            return false;
        }
    }

    /**
     * @brief slot to update an application HTML info in the description view window.
     * An application is chosen based on the app name and
     * its type that is currently in the selected state of the view
     */
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

    /**
     * @brief slot to switch description view window visibility
     */
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

    /**
     * @brief slot to add application to one of the models defined by the given type
     */
    void CoreAppWindow::addApplication( AppWindowBase * app, APP_TYPE type )
    {
        switch( type )
        {
        case OPENGL_APP:
        {
            openGLAppsCollectionModel->addApplication( app );
            break;
        }
        case SOFTWARE_APP:
        {
            softwareAppsCollectionModel->addApplication( app );
            break;
        }
        default:
            throw std::invalid_argument( "Not suitable application type" );
        }
    }

    void CoreAppWindow::searchByName( const QString & name )
    {
        const APP_TYPE currentChosenType = getAppType();
        if( currentChosenType == OPENGL_APP )
        {
            QItemSelectionModel * selectionModel = ui->openGLAppsView->selectionModel();
            selectionModel->clear();
            for( int nameIndex = 0; nameIndex < openGLAppsCollectionModel->getApplicationNames().size(); ++nameIndex )
            {
                if( openGLAppsCollectionModel->getApplicationNames()[ nameIndex ].contains( name, Qt::CaseInsensitive ) )
                {
                    auto modelIndex = ui->openGLAppsView->model()->index( nameIndex, 0 );
                    selectionModel->select( modelIndex, QItemSelectionModel::Select );
                    emit ui->openGLAppsView->clicked( modelIndex );
                    return;
                }
            }
        }
        else if( currentChosenType == SOFTWARE_APP )
        {
            QItemSelectionModel * selectionModel = ui->softwareAppsView->selectionModel();
            selectionModel->clear();
            for( int nameIndex = 0; nameIndex < softwareAppsCollectionModel->getApplicationNames().size(); ++nameIndex )
            {
                if( softwareAppsCollectionModel->getApplicationNames()[ nameIndex ].contains( name, Qt::CaseInsensitive ) )
                {
                    auto modelIndex = ui->softwareAppsView->model()->index( nameIndex, 0 );
                    selectionModel->select( modelIndex, QItemSelectionModel::Select );
                    emit ui->softwareAppsView->clicked( modelIndex );
                    return;
                }
            }
        }
    }

    /**
     * @brief utility function to get application type based on the view tab widget current index
     */
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

    /**
     * @brief utility function to get currently chosen application's name from one of the models
     * defined by the given type
     */
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
