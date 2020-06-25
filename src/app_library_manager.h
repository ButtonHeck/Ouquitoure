#pragma once

#include <QWidget>

#include "AppWindowBase"

namespace Ouquitoure
{
    class AppLibraryManager : public QObject
    {
        Q_OBJECT
    public:
        AppLibraryManager();
        void loadApplications();

    signals:
        void applicationAdded( AppWindowBase *, APP_TYPE );

    private:
        QWidget invisibleParentForApps;
    };
} // namespace Ouquitoure
