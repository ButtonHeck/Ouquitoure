#pragma once

#include "Apps/AppWindowBase"

#include <QWidget>

namespace Ouquitoure
{

    /**
     * @brief Applications loader class
     */
    class AppLibraryManager : public QObject
    {
        Q_OBJECT
    public:
        AppLibraryManager();
        void loadApplications();

    signals:
        void applicationCreated( AppWindowBase *, APP_TYPE );

    private:
        QWidget invisibleParentForApps;
    };

} // namespace Ouquitoure
