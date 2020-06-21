#pragma once

#include <QMainWindow>

#include <AppInfo>

namespace Ouquitoure
{
    class SoftwareAppBase : public QMainWindow
    {
        Q_OBJECT
    public:
        explicit SoftwareAppBase(QWidget * parent = nullptr);
        virtual ~SoftwareAppBase();

        const AppInfo & getInfo() const noexcept;

    protected:
        AppInfo info;
    };
}
