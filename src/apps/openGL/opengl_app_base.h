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
    public:
        /**
         * @brief setup generic ui and layout stuff
         */
        explicit OpenGLAppBase( const QString & name, QWidget * parent = nullptr );
        virtual ~OpenGLAppBase();

        void resizeEvent( QResizeEvent * event ) override;
        void closeEvent( QCloseEvent * event ) override;

    protected:
        /**
         * @brief sets given view widget as the dock widget contents
         * @param widget
         */
        void installOpenGLViewWidget( OpenGLWidgetBase & widget );

    protected:
        QString       appName;
        QDockWidget * viewDockWidget;
        QHBoxLayout * appLayout;
        QGroupBox *   controlsGroupBox;
    };

} // namespace Ouquitoure
