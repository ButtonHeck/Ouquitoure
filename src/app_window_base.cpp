#include "AppWindowBase"

namespace Ouquitoure
{

    AppWindowBase::AppWindowBase(QWidget * parent)
        : QMainWindow(parent)
    {}

    const AppInfo & AppWindowBase::getInfo() const noexcept
    {
        return info;
    }

}
