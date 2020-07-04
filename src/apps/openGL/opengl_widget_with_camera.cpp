#include "Apps/OpenGL/OpenGLWidgetWithCamera"

#include <QMouseEvent>

namespace Ouquitoure
{

    OpenGLWidgetWithCamera::OpenGLWidgetWithCamera( const QString & name, QWidget * parent )
        : OpenGLWidgetBase( name, parent )
        , camera( 0.0f, 0.0f, 5.0f )
    {
    }

    Camera & OpenGLWidgetWithCamera::getCamera()
    {
        return camera;
    }

    void OpenGLWidgetWithCamera::mousePressEvent( QMouseEvent * event )
    {
        setCursor( Qt::BlankCursor );
        camera.updateLastPos( event->x(), event->y() );
    }

    void OpenGLWidgetWithCamera::mouseReleaseEvent( QMouseEvent * event )
    {
        Q_UNUSED( event );
        setCursor( Qt::ArrowCursor );
    }

    void OpenGLWidgetWithCamera::mouseMoveEvent( QMouseEvent * event )
    {
        camera.processMouseMove( event->x(), event->y() );
    }

    void OpenGLWidgetWithCamera::keyPressEvent( QKeyEvent * event )
    {
        camera.processKeyboardInput( event->key(), true );
    }

    void OpenGLWidgetWithCamera::keyReleaseEvent( QKeyEvent * event )
    {
        camera.processKeyboardInput( event->key(), false );
    }

    bool OpenGLWidgetWithCamera::eventFilter( QObject * watched, QEvent * event )
    {
        Q_UNUSED( watched );
        if( event->type() == QEvent::KeyPress )
        {
            QKeyEvent * keyEvent = static_cast<QKeyEvent *>( event );
            if( keyEvent )
            {
                keyPressEvent( keyEvent );
                return true;
            }
        }
        else if( event->type() == QEvent::KeyRelease )
        {
            QKeyEvent * keyEvent = static_cast<QKeyEvent *>( event );
            if( keyEvent )
            {
                keyReleaseEvent( keyEvent );
                return true;
            }
        }
        return false;
    }

} // namespace Ouquitoure
