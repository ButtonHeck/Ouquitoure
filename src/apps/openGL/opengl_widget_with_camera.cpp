#include "Apps/OpenGL/OpenGLWidgetWithCamera"

#include <QMouseEvent>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Ouquitoure
{

    OpenGLWidgetWithCamera::OpenGLWidgetWithCamera( const QString & name, QWidget * parent )
        : OpenGLWidgetBase( name, parent )
        , camera( 0.0f, 0.0f, 5.0f )
    {
        connect( &camera, SIGNAL( viewChanged() ), this, SLOT( updateViewMatrixForMainProgram() ) );
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

    void OpenGLWidgetWithCamera::resizeGL( int width, int height )
    {
        glViewport( 0, 0, width, height );
        updateProjectionMatrixForMainProgram();
    }

    void OpenGLWidgetWithCamera::updateViewMatrixForMainProgram()
    {
        makeCurrent();

        QOpenGLShaderProgram * mainProgram = shaderPrograms[ "main" ];
        mainProgram->bind();
        const glm::mat4 VIEW_MATRIX = camera.getViewMatrix();
        glUniformMatrix4fv( mainProgram->uniformLocation( "u_view" ), 1, GL_FALSE, glm::value_ptr( VIEW_MATRIX ) );

        update();
    }

    void OpenGLWidgetWithCamera::updateProjectionMatrixForMainProgram()
    {
        makeCurrent();

        QOpenGLShaderProgram * mainProgram = shaderPrograms[ "main" ];
        mainProgram->bind();
        const glm::mat4 PROJECTION_MATRIX = glm::perspective( glm::radians( camera.getFov() ),
                                                              static_cast<float>( width() ) / static_cast<float>( height() ), 0.1f, 20.0f );
        glUniformMatrix4fv( mainProgram->uniformLocation( "u_projection" ), 1, GL_FALSE, glm::value_ptr( PROJECTION_MATRIX ) );

        update();
    }

} // namespace Ouquitoure
