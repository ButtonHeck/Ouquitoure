#pragma once

#include "Apps/AppWindowBase"

#include <QWidget>

namespace Ouquitoure
{
    class KeybindingsManager;

    /**
     * @brief Applications loader class
     */
    class AppLibraryManager final : public QObject
    {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE( AppLibraryManager )
    public:
        AppLibraryManager() = default;

        /// @brief instantiates all the applications and emits signals that one was created
        void loadApplications( const KeybindingsManager & keybindingsManager );

    signals:
        /// @brief notifies receiver that manager has added new application
        void applicationCreated( AppWindowBase * app );

    private:
        /// this widget is used as parent instead of the main window to prevent applications hide when the main window hides
        QWidget invisibleParentForApps;
    };

} // namespace Ouquitoure
