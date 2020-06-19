#pragma once

#include <QMainWindow>
#include <QVector>

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
        explicit CoreAppWindow( QWidget *parent = nullptr );
        ~CoreAppWindow();

    private slots:
        bool launchApp();
        void switchLogVisibility();

    private:
        Ui::CoreAppWindow *ui;
        AppCollectionModel * openGLAppsCollectionModel;
        AppCollectionModel * softwareAppsCollectionModel;

        using AppEntry = QPair<QString, QMainWindow*>;
        QVector<AppEntry> apps;

        QWidget invisibleParentForApps;
    };
}

