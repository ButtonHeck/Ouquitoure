#include "CoreAppWindow"
#include "AppCollectionModel"
#include "Apps/AppType"
#include "Log"
#include "Apps/OpenGL/OpenGLAppBase"
#include "Apps/Software/SoftwareAppBase"
#include "Utils/LogicalTokens"
#include "CameraSettingsDialog"
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
        , cameraSettingsDialog( new CameraSettingsDialog( this ) )
    {
        ui->setupUi( this );
        setWindowIcon( QIcon( ":/icons/logo.ico" ) );
        setWindowTitle( "Ouquitoure sandbox" );
        QToolBar * toolbar = new QToolBar( "Toolbar", this );
        addToolBar( toolbar );
        toolbar->addAction( QIcon( ":/icons/show_description_icon.png" ), "Show description", this,
                            SLOT( switchDescriptionWindowVisible() ) );
        toolbar->addAction( QIcon( ":/icons/camera.png" ), "Camera settings", this, SLOT( showCameraSettingsDialog() ) );

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
        const QString  appName = getCurrentlyChosenAppName( appType );
        OQ_LOG_INFO << appName << " sender: " << sender()->objectName();

        AppWindowBase * appWindow = getCurrentlyChosenAppWindow( appType, appName );
        if( appWindow )
        {
            appWindow->isHidden() ? appWindow->show() : appWindow->activateWindow();
            appWindow->setGeometry( geometry().x(), geometry().y(), appWindow->geometry().width(), appWindow->geometry().height() );
            return true;
        }
        return false;
    }

    void CoreAppWindow::updateDescriptionWindowInfo()
    {
        const APP_TYPE appType = getViewTabCurrentAppType();
        const QString  appName = getCurrentlyChosenAppName( appType );

        const AppWindowBase * appWindow = getCurrentlyChosenAppWindow( appType, appName );
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

        AppCollectionView *   appCollectionView  = getAppCollectionViewForType( currentChosenType );
        QItemSelectionModel * selectionModel     = getSelectionModelForType( currentChosenType );
        AppCollectionModel *  appCollectionModel = getAppCollectionModelForType( currentChosenType );
        if( not selectionModel || not appCollectionModel || not appCollectionView )
        {
            return;
        }
        selectionModel->clear();
        if( name.isEmpty() )
        {
            return;
        }

        // accumulate selections based on current name input
        for( int nameIndex = 0; nameIndex < appCollectionModel->getApplicationNames().size(); ++nameIndex )
        {
            if( appCollectionModel->getApplicationNames()[ nameIndex ].contains( name, Qt::CaseInsensitive ) )
            {
                auto modelIndex = appCollectionModel->index( nameIndex, 0 );
                selectedIndices.push_back( modelIndex );
                selectionModel->select( modelIndex, QItemSelectionModel::Select );
            }
        }

        // check for exact match
        if( selectedIndices.size() == 1 )
        {
            emit appCollectionView->clicked( selectedIndices.first() );
        }
    }

    void CoreAppWindow::searchByTags( const QString & tags )
    {
        const APP_TYPE       currentChosenType = getViewTabCurrentAppType();
        QVector<QModelIndex> selectedIndices;
        QStringList          separatedTags = tags.split( ";" );

        AppCollectionView *   appCollectionView  = getAppCollectionViewForType( currentChosenType );
        QItemSelectionModel * selectionModel     = getSelectionModelForType( currentChosenType );
        AppCollectionModel *  appCollectionModel = getAppCollectionModelForType( currentChosenType );
        if( not selectionModel || not appCollectionModel || not appCollectionView )
        {
            return;
        }
        selectionModel->clear();

        // accumulate selections based on current tags input
        const auto & appsNames = appCollectionModel->getApplicationNames();
        for( int nameIndex = 0; nameIndex < appsNames.size(); ++nameIndex )
        {
            const auto * app         = appCollectionModel->getApplication( appsNames[ nameIndex ] );
            const auto & appTagsList = app->getInfo().getTags();
            if( std::all_of( separatedTags.cbegin(), separatedTags.cend(), [ & ]( const QString & tag ) {
                    return appTagsList.contains( tag, Qt::CaseInsensitive );
                } ) )
            {
                auto modelIndex = appCollectionModel->index( nameIndex, 0 );
                selectedIndices.push_back( modelIndex );
                selectionModel->select( modelIndex, QItemSelectionModel::Select );
            }
        }

        // check for exact match
        if( selectedIndices.size() == 1 )
        {
            emit appCollectionView->clicked( selectedIndices.first() );
        }
    }

    void CoreAppWindow::showCameraSettingsDialog()
    {
        cameraSettingsDialog->show();
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

    QString CoreAppWindow::getCurrentlyChosenAppName( APP_TYPE type )
    {
        const AppCollectionModel * appCollectionModel = getAppCollectionModelForType( type );
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

    AppWindowBase * CoreAppWindow::getCurrentlyChosenAppWindow( APP_TYPE appType, const QString & appName )
    {
        AppCollectionModel * appCollectionModel = getAppCollectionModelForType( appType );
        return appCollectionModel ? appCollectionModel->getApplication( appName ) : nullptr;
    }

    AppCollectionView * CoreAppWindow::getAppCollectionViewForType( APP_TYPE appType )
    {
        switch( appType )
        {
        case OQ_APP_TYPE_OPENGL:
            return ui->openGLAppsView;
        case OQ_APP_TYPE_SOFTWARE:
            return ui->softwareAppsView;
        default:
            OQ_LOG_WARNING << " No app collection view for a given type: " << appType;
            return nullptr;
        }
    }

    QItemSelectionModel * CoreAppWindow::getSelectionModelForType( APP_TYPE appType )
    {
        const AppCollectionView * appCollectionView = getAppCollectionViewForType( appType );
        return appCollectionView ? appCollectionView->selectionModel() : nullptr;
    }

} // namespace Ouquitoure
