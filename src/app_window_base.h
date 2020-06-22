#pragma once

#include <QMainWindow>

#include "AppInfo"

namespace Ouquitoure
{
    class AppWindowBase : public QMainWindow
    {
        Q_OBJECT
    public:
        explicit AppWindowBase( QWidget * parent = nullptr );
        virtual ~AppWindowBase() = default;

        const AppInfo & getInfo() const noexcept;

    protected:
        AppInfo info;
    };

} // namespace Ouquitoure
