#pragma once

#include <QHBoxLayout>
#include <QGroupBox>

#include "Apps/AppWindowBase"

namespace Ouquitoure
{
    class OpenGLWidgetBase;

    /**
     * @brief OpenGL application base class
     */
    class OpenGLAppBase : public AppWindowBase
    {
        Q_OBJECT
    public:
        explicit OpenGLAppBase( const QString & name, QWidget * parent = nullptr );
        virtual ~OpenGLAppBase();

        void resizeEvent( QResizeEvent * event ) override;
        void closeEvent( QCloseEvent * event ) override;

    protected:
        void installOpenGLViewWidget( OpenGLWidgetBase & widget );

    protected:
        QString       appName;
        QDockWidget * viewDockWidget;
        QHBoxLayout * appLayout;
        QGroupBox *   controlsGroupBox;
    };

} // namespace Ouquitoure
