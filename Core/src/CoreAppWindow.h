#pragma once

#include <QMainWindow>
#include <QSet>

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

    private:
        Ui::CoreAppWindow *ui;
        AppCollectionModel * OpenGLAppsCollectionModel;
        AppCollectionModel * softwareAppsCollectionModel;

        QSet<QPair<QString, QMainWindow*>> apps;
        QWidget invisibleParentForApps;
    };
}

