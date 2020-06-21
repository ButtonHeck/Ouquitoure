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

    private:
        Ui::CoreAppWindow *ui;
        AppCollectionModel * openGLAppsCollectionModel;
        AppCollectionModel * softwareAppsCollectionModel;

        using AppTableEntry = QPair<QString, QMainWindow*>;
        QVector<AppTableEntry> openGLAppCollection;
        QVector<AppTableEntry> softwareAppCollection;

        QWidget invisibleParentForApps;
    };
}

