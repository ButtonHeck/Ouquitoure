#pragma once

#include <QMainWindow>

#include <AppInfo>

namespace Ouquitoure
{
    class OpenGLAppBase : public QMainWindow
    {
        Q_OBJECT
    public:
        explicit OpenGLAppBase(QWidget * parent = nullptr);
        virtual ~OpenGLAppBase();

        void resizeEvent(QResizeEvent *event) override;
        const AppInfo & getInfo() const noexcept;

    protected:
        QDockWidget * viewDockWidget;
        AppInfo info;
    };
}
