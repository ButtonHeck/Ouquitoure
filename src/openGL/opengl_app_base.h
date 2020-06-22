#pragma once

#include "AppWindowBase"

namespace Ouquitoure
{
    class OpenGLAppBase : public AppWindowBase
    {
        Q_OBJECT
    public:
        explicit OpenGLAppBase( const QString & name, QWidget * parent = nullptr );
        virtual ~OpenGLAppBase();

        void resizeEvent( QResizeEvent * event ) override;

    protected:
        QString       appName;
        QDockWidget * viewDockWidget;
    };

} // namespace Ouquitoure
