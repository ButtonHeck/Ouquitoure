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

        /// @brief instantiates all the applications and emits signals that one was created
        void loadApplications();

    signals:
        /// @brief notifies receiver that manager has added new application
        void applicationCreated( AppWindowBase * app );

    private:
        /// this widget is used as parent instead of the main window to prevent applications hide when the main window hides
        QWidget invisibleParentForApps;
    };

} // namespace Ouquitoure
