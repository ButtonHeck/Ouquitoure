#pragma once

#include <QWidget>

#include "AppWindowBase"

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
