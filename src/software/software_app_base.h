#pragma once

#include <QMainWindow>

namespace Ouquitoure
{
    class SoftwareAppBase : public QMainWindow
    {
        Q_OBJECT
    public:
        explicit SoftwareAppBase(QWidget * parent = nullptr);
        virtual ~SoftwareAppBase();
    };
}
