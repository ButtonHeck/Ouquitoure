#include "SoftwareApps/SoftwareAppBase"

#include <QLabel>

#include "Log"

namespace Ouquitoure
{

    SoftwareAppBase::SoftwareAppBase(QWidget * parent)
        : QMainWindow(parent)
    {
        OQ_LOG_DEBUG << "Software ctor";

        setWindowTitle("Software Application");
        QLabel * label = new QLabel(this);
        label->setText("Software");
    }

    SoftwareAppBase::~SoftwareAppBase()
    {
        OQ_LOG_DEBUG << "Software dtor";
    }

    const AppInfo & SoftwareAppBase::getInfo() const noexcept
    {
        return info;
    }

}
