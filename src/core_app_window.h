#pragma once

#include <QMainWindow>
#include <QVector>

#include "AppLibraryManager"

namespace Ui
{
    class CoreAppWindow;
}

namespace Ouquitoure
{
    class AppCollectionModel;

    class CoreAppWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        explicit CoreAppWindow( QWidget * parent = nullptr );
        ~CoreAppWindow();

    private slots:
        bool launchApp();
        void updateDescriptionWindowInfo();
        void switchDescriptionWindowVisible();

    private:
        APP_TYPE getAppType();
        QString  getAppName( APP_TYPE type );

    private:
        Ui::CoreAppWindow *  ui;
        AppCollectionModel * openGLAppsCollectionModel;
        AppCollectionModel * softwareAppsCollectionModel;
        AppLibraryManager    appLibraryManager;
    };
} // namespace Ouquitoure
