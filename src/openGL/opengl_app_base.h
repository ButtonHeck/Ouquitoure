#pragma once

#include "AppWindowBase"

namespace Ouquitoure
{
    class OpenGLAppBase : public AppWindowBase
    {
        Q_OBJECT
    public:
        explicit OpenGLAppBase( QWidget * parent = nullptr );
        virtual ~OpenGLAppBase() = default;

        void resizeEvent( QResizeEvent * event ) override;

    protected:
        QDockWidget * viewDockWidget;
    };
} // namespace Ouquitoure
