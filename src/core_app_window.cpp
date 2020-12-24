#include "CoreAppWindow"
#include "AppCollectionModel"
#include "Apps/AppType"
#include "Log"
#include "Apps/OpenGL/OpenGLAppBase"
#include "Apps/Software/SoftwareAppBase"
#include "ui_core_app_window.h"

#include <QToolBar>
#include <QItemSelectionModel>
#include <algorithm>

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

        // callback to the "Tags" input
        connect( ui->appSearchByTagsLineInput, SIGNAL( textChanged( const QString & ) ), SLOT( searchByTags( const QString & ) ) );
    }

    CoreAppWindow::~CoreAppWindow()
    {
        delete ui;
    }

    bool CoreAppWindow::launchApp()
    {
        const APP_TYPE appType = getViewTabCurrentAppType();
        const QString  appName = getAppName( appType );
        OQ_LOG_INFO << appName << " sender: " << sender()->objectName();

        AppCollectionModel * appCollectionModel = getAppCollectionModelForType( appType );
        if( appCollectionModel )
        {
            AppWindowBase * appWindow = appCollectionModel->getApplication( appName );
            if( appWindow )
            {
                appWindow->isHidden() ? appWindow->show() : appWindow->activateWindow();
                appWindow->setGeometry( geometry().x(), geometry().y(), appWindow->geometry().width(), appWindow->geometry().height() );
                return true;
            }
        }
        return false;
    }

    void CoreAppWindow::updateDescriptionWindowInfo()
    {
        const APP_TYPE appType = getViewTabCurrentAppType();
        const QString  appName = getAppName( appType );

        AppCollectionModel * appCollectionModel = getAppCollectionModelForType( appType );
        AppWindowBase *      appWindow          = appCollectionModel ? appCollectionModel->getApplication( appName ) : nullptr;
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

    void CoreAppWindow::addApplication( AppWindowBase * app, APP_TYPE type )
    {
        AppCollectionModel * appCollectionModel = getAppCollectionModelForType( type );
        if( appCollectionModel )
        {
            appCollectionModel->addApplication( app );
        }
    }

    void CoreAppWindow::searchByName( const QString & name )
    {
        const APP_TYPE       currentChosenType = getViewTabCurrentAppType();
        QVector<QModelIndex> selectedIndices;

        if( currentChosenType == OQ_APP_TYPE_OPENGL )
        {
            QItemSelectionModel * selectionModel = ui->openGLAppsView->selectionModel();
            selectionModel->clear();
            if( name.isEmpty() )
            {
                return;
            }
            for( int nameIndex = 0; nameIndex < openGLAppsCollectionModel->getApplicationNames().size(); ++nameIndex )
            {
                if( openGLAppsCollectionModel->getApplicationNames()[ nameIndex ].contains( name, Qt::CaseInsensitive ) )
                {
                    auto modelIndex = openGLAppsCollectionModel->index( nameIndex, 0 );
                    selectedIndices.push_back( modelIndex );
                    selectionModel->select( modelIndex, QItemSelectionModel::Select );
                }
            }
            // check for exact match
            if( selectedIndices.size() == 1 )
            {
                emit ui->openGLAppsView->clicked( selectedIndices.first() );
            }
        }
        else if( currentChosenType == OQ_APP_TYPE_SOFTWARE )
        {
            QItemSelectionModel * selectionModel = ui->softwareAppsView->selectionModel();
            selectionModel->clear();
            if( name.isEmpty() )
            {
                return;
            }
            for( int nameIndex = 0; nameIndex < softwareAppsCollectionModel->getApplicationNames().size(); ++nameIndex )
            {
                if( softwareAppsCollectionModel->getApplicationNames()[ nameIndex ].contains( name, Qt::CaseInsensitive ) )
                {
                    auto modelIndex = softwareAppsCollectionModel->index( nameIndex, 0 );
                    selectedIndices.push_back( modelIndex );
                    selectionModel->select( modelIndex, QItemSelectionModel::Select );
                }
            }
            // check for exact match
            if( selectedIndices.size() == 1 )
            {
                emit ui->openGLAppsView->clicked( selectedIndices.first() );
            }
        }
    }

    void CoreAppWindow::searchByTags( const QString & tags )
    {
        const APP_TYPE       currentChosenType = getViewTabCurrentAppType();
        QVector<QModelIndex> selectedIndices;
        QStringList          separatedTags = tags.split( ";" );

        if( currentChosenType == OQ_APP_TYPE_OPENGL )
        {
            QItemSelectionModel * selectionModel = ui->openGLAppsView->selectionModel();
            selectionModel->clear();
            const auto & appsNames = openGLAppsCollectionModel->getApplicationNames();
            for( int nameIndex = 0; nameIndex < appsNames.size(); ++nameIndex )
            {
                const auto * app         = openGLAppsCollectionModel->getApplication( appsNames[ nameIndex ] );
                const auto & appTagsList = app->getInfo().getTags();
                if( std::all_of( separatedTags.cbegin(), separatedTags.cend(), [ & ]( const QString & tag ) {
                        return appTagsList.contains( tag, Qt::CaseInsensitive );
                    } ) )
                {
                    auto modelIndex = openGLAppsCollectionModel->index( nameIndex, 0 );
                    selectedIndices.push_back( modelIndex );
                    selectionModel->select( modelIndex, QItemSelectionModel::Select );
                }
            }
            // check for exact match
            if( selectedIndices.size() == 1 )
            {
                emit ui->openGLAppsView->clicked( selectedIndices.first() );
            }
        }
        else if( currentChosenType == OQ_APP_TYPE_SOFTWARE )
        {
            QItemSelectionModel * selectionModel = ui->softwareAppsView->selectionModel();
            selectionModel->clear();
            const auto & appsNames = softwareAppsCollectionModel->getApplicationNames();
            for( int nameIndex = 0; nameIndex < appsNames.size(); ++nameIndex )
            {
                const auto * app         = softwareAppsCollectionModel->getApplication( appsNames[ nameIndex ] );
                const auto & appTagsList = app->getInfo().getTags();
                if( std::all_of( separatedTags.cbegin(), separatedTags.cend(), [ & ]( const QString & tag ) {
                        return appTagsList.contains( tag, Qt::CaseInsensitive );
                    } ) )
                {
                    auto modelIndex = softwareAppsCollectionModel->index( nameIndex, 0 );
                    selectedIndices.push_back( modelIndex );
                    selectionModel->select( modelIndex, QItemSelectionModel::Select );
                }
            }
            // check for exact match
            if( selectedIndices.size() == 1 )
            {
                emit ui->softwareAppsView->clicked( selectedIndices.first() );
            }
        }
    }

    APP_TYPE CoreAppWindow::getViewTabCurrentAppType()
    {
        const auto APP_TABLE_VIEW_CURRENT_TAB_INDEX = ui->appLibraryTabWidget->currentIndex();
        switch( APP_TABLE_VIEW_CURRENT_TAB_INDEX )
        {
        case 0:
            return OQ_APP_TYPE_OPENGL;
        case 1:
            return OQ_APP_TYPE_SOFTWARE;
        default:
            throw std::runtime_error( "Not suitable app type for table view tab index" );
        }
    }

    QString CoreAppWindow::getAppName( APP_TYPE type )
    {
        AppCollectionModel * appCollectionModel = getAppCollectionModelForType( type );
        return appCollectionModel ? appCollectionModel->getCurrentAppInfo().getName() : "";
    }

    AppCollectionModel * CoreAppWindow::getAppCollectionModelForType( APP_TYPE appType )
    {
        switch( appType )
        {
        case OQ_APP_TYPE_OPENGL:
            return openGLAppsCollectionModel;
        case OQ_APP_TYPE_SOFTWARE:
            return softwareAppsCollectionModel;
        default:
            OQ_LOG_WARNING << "No app collection model for given appType: " << appType;
            return nullptr;
        }
    }

} // namespace Ouquitoure
