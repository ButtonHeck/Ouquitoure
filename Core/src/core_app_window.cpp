#include "core_app_window.h"
#include "ui_core_app_window.h"
#include "app_collection_model.h"
#include "hello_app.h"
#include <QDebug>
#include <QToolBar>
#include "logger.h"

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
        ui->openGLApps->setModel(OpenGLAppsCollectionModel);
        ui->softwareApps->setModel(softwareAppsCollectionModel);

        connect(ui->openGLApps, SIGNAL(clicked(const QModelIndex &)), OpenGLAppsCollectionModel, SLOT(debugMouseClickSlot(const QModelIndex &)));
        connect(ui->openGLApps, SIGNAL(doubleClicked(const QModelIndex &)), OpenGLAppsCollectionModel, SLOT(debugDoubleMouseClickSlot(const QModelIndex &)));

        OpenGLAppsCollectionModel->addNewAppData("hello app", "tag1; tag2");
        OpenGLAppsCollectionModel->addNewAppData("fucking awesome app!", "holy shit this is amazing!!");

        connect(ui->launchAppButton, SIGNAL(clicked()), SLOT(launchApp()));
        connect(ui->openGLApps, SIGNAL(doubleClicked(const QModelIndex &)), SLOT(launchApp()));

        QToolBar * toolbar = new QToolBar{"Toolbar", this};
        addToolBar(toolbar);
        toolbar->setIconSize(QSize(32, 32));

        const QIcon LOG_ICON {":/icons/log_icon.png"};
        toolbar->addAction(LOG_ICON, "Log", this, SLOT(switchLogVisibility()));
        const QIcon LOG_SETTINGS_ICON{":/icons/settings.png"};
        toolbar->addAction(LOG_SETTINGS_ICON, "Log settings");

        addDockWidget(Qt::BottomDockWidgetArea, ui->logDockWidget);
        ui->logDockWidget->setWindowTitle("Log window");

        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(ui->logDockWidget->sizePolicy().hasHeightForWidth());
        ui->logDockWidget->setSizePolicy(sizePolicy2);

        Logger::instantiateCoreLogger(ui->logDockWidgetContents);
        QTextEdit & coreLogger = Logger::getCoreLogger();
        coreLogger.setObjectName(QString::fromUtf8("logWindow"));
        sizePolicy2.setHeightForWidth(coreLogger.sizePolicy().hasHeightForWidth());
        coreLogger.setSizePolicy(sizePolicy2);
        coreLogger.setReadOnly(true);
        QLayout * horizontalLayout_2 = ui->logDockWidgetContents->layout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_2->addWidget(&coreLogger);
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
