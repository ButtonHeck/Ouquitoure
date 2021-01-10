#pragma once

#include "Apps/AppInfo"

#include <QMainWindow>

namespace Ouquitoure
{

    /**
     * @brief Base class of all application windows
     */
    class AppWindowBase : public QMainWindow
    {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE( AppWindowBase )
    public:
        explicit AppWindowBase( QWidget * parent = nullptr );
        virtual ~AppWindowBase() = default;

        /// @return application info object
        [[nodiscard]] const AppInfo & getInfo() const noexcept;

    protected:
        /// @brief initializes description object (name, author, brief etc.)
        virtual void initializeDescription() = 0;

    protected:
        AppInfo info;
    };

} // namespace Ouquitoure
