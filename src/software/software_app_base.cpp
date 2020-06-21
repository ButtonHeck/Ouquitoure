#include "SoftwareApps/SoftwareAppBase"

#include <QLabel>

#include "Log"

namespace Ouquitoure
{

    SoftwareAppBase::SoftwareAppBase(QWidget * parent)
        : AppWindowBase(parent)
    {
        setWindowTitle("Software Application");
        QLabel * label = new QLabel(this);
        label->setText("Software");
    }

}
