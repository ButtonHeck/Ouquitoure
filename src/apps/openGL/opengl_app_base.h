#pragma once

#include "Apps/AppWindowBase"

#include <QHBoxLayout>
#include <QGroupBox>

namespace Ouquitoure
{
    class OpenGLWidgetBase;

    /**
     * @brief OpenGL application base class
     */
    class OpenGLAppBase : public AppWindowBase
    {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE( OpenGLAppBase )
    public:
        /// @brief setup generic ui and layout stuff
        explicit OpenGLAppBase( const QString & name, QWidget * parent = nullptr );

#ifdef QT_DEBUG
        virtual ~OpenGLAppBase();
#else
        virtual ~OpenGLAppBase() = default;
#endif

        void resizeEvent( QResizeEvent * event ) override;
        void closeEvent( QCloseEvent * event ) override;

        /// @brief get view widget used in this application
        OpenGLWidgetBase & getViewWidget();

    protected:
        /// @brief sets given view widget as the dock widget contents
        void installOpenGLViewWidget( OpenGLWidgetBase & widget );

    protected:
        QString       appName;
        QDockWidget * viewDockWidget;
        QHBoxLayout * appLayout;
        QGroupBox *   controlsGroupBox;
    };

} // namespace Ouquitoure
