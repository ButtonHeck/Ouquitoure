#include "core_app_window.h"

#include <QToolBar>

#include "ui_core_app_window.h"
#include "app_collection_model.h"
#include "logger.h"
#include "hello_app.h"

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
        openGLAppsCollectionModel->addAppTableToken("hello app", "tag1; tag2");
        openGLAppsCollectionModel->addAppTableToken("fucking awesome app!", "holy shit this is amazing!!");

        //software stuff
        ui->softwareApps->setModel(softwareAppsCollectionModel);
        connect(ui->softwareApps, SIGNAL(clicked(const QModelIndex &)), softwareAppsCollectionModel, SLOT(tableTokenClick(const QModelIndex &)));
        connect(ui->softwareApps, SIGNAL(doubleClicked(const QModelIndex &)), SLOT(launchApp()));
        softwareAppsCollectionModel->addAppTableToken("SW test app", "tags");

        connect(ui->launchAppButton, SIGNAL(clicked()), SLOT(launchApp()));


        //toolbar setup
        QToolBar * toolbar = new QToolBar{"Toolbar", this};
        addToolBar(toolbar);
        toolbar->setIconSize(QSize(32, 32));
        //log on/off
        const QIcon LOG_ICON {":/icons/log_icon.png"};
        toolbar->addAction(LOG_ICON, "Log", this, SLOT(switchLogVisibility()));
        //log settings
        const QIcon LOG_SETTINGS_ICON{":/icons/settings.png"};
        toolbar->addAction(LOG_SETTINGS_ICON, "Log settings");

        //log dock widget
        addDockWidget(Qt::BottomDockWidgetArea, ui->logDockWidget);
        ui->logDockWidget->setWindowTitle("Log window");

        //log window setup
        Logger::instantiateCoreLogger(ui->logDockWidgetContents);
        QTextEdit & coreLogger = Logger::getCoreLogger();
        QSizePolicy logWindowSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
        logWindowSizePolicy.setHorizontalStretch(1);
        logWindowSizePolicy.setVerticalStretch(1);
        logWindowSizePolicy.setHeightForWidth(coreLogger.sizePolicy().hasHeightForWidth());
        coreLogger.setSizePolicy(logWindowSizePolicy);
        coreLogger.setObjectName(QString::fromUtf8("logWindow"));
        coreLogger.setReadOnly(true);
        //log widget layout
        QLayout * logDockWidgetLayout = ui->logDockWidgetContents->layout();
        logDockWidgetLayout->setSpacing(0);
        logDockWidgetLayout->setObjectName(QString::fromUtf8("logDockWidgetLayout"));
        logDockWidgetLayout->setContentsMargins(1, 1, 1, 1);
        logDockWidgetLayout->addWidget(&coreLogger);
    }

    CoreAppWindow::~CoreAppWindow()
    {
        delete ui;
    }

    bool CoreAppWindow::launchApp()
    {
        QString appNameFromModel = openGLAppsCollectionModel->getCurrentAppTableToken().first;
        qInfo() << appNameFromModel << "sender:(" << sender()->objectName() << ")";

        auto appEntry = std::find_if(apps.cbegin(), apps.cend(), [&](const AppEntry app)
        {
            qInfo() << appNameFromModel << app.first;
            return appNameFromModel == app.first;
        });
        if (appEntry == apps.cend())
        {
            HelloApp * newApp = new HelloApp{&invisibleParentForApps};
            apps << QPair{appNameFromModel, newApp};
            newApp->show();
        }
        else
        {
            QMainWindow * window = appEntry->second;
            window->isHidden() ? window->show() : window->activateWindow();
        }
        return true;
    }

    void CoreAppWindow::switchLogVisibility()
    {
        ui->logDockWidget->setVisible(!ui->logDockWidget->isVisible());
    }
}
