#include "Apps/OpenGL/OpenGLDrawFunctionsWidget"

#include <QFile>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <array>
#include <QMouseEvent>

#include "Math/Point3Pos3Color"
#include "Log"

namespace Ouquitoure
{

    OpenGLDrawFunctionsWidget::OpenGLDrawFunctionsWidget( const QString & name, QWidget * parent )
        : OpenGLWidgetBase( name, parent )
        , camera( 0.0f, 0.0f, 5.0f )

        // glDrawArrays
        , drawArraysVao( 0 )
        , drawArraysVbo( 0 )

        // glDrawElements
        , drawElementsVao( 0 )
        , drawElementsVbo( 0 )
        , drawElementsEbo( 0 )
    {
        connect( &camera, SIGNAL( viewChanged() ), SLOT( updateViewMatrix() ) );
    }

    OpenGLDrawFunctionsWidget::~OpenGLDrawFunctionsWidget()
    {
        cleanup();
    }

    Camera & OpenGLDrawFunctionsWidget::getCamera()
    {
        return camera;
    }

    void OpenGLDrawFunctionsWidget::initializeGL()
    {
        OpenGLWidgetBase::initializeGL();
        cleanup();

        glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
        glPointSize( 3.0f );
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

        initializeOpenGLObjects();
        initializeOpenGLShaders();

        QOpenGLShaderProgram * mainProgram = shaderPrograms[ "main" ];
        mainProgram->bind();

        const glm::mat4 PROJECTION_MATRIX = glm::perspective( glm::radians( camera.getFov() ),
                                                              static_cast<float>( width() ) / static_cast<float>( height() ), 0.1f, 20.0f );
        glUniformMatrix4fv( mainProgram->uniformLocation( "u_projection" ), 1, GL_FALSE, glm::value_ptr( PROJECTION_MATRIX ) );
        glm::mat4 viewMatrix = camera.getViewMatrix();
        glUniformMatrix4fv( mainProgram->uniformLocation( "u_view" ), 1, GL_FALSE, glm::value_ptr( viewMatrix ) );
    }

    void OpenGLDrawFunctionsWidget::paintGL()
    {
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        glm::mat4              model;
        QOpenGLShaderProgram * mainProgram = shaderPrograms[ "main" ];
        mainProgram->bind();
        glUniformMatrix4fv( mainProgram->uniformLocation( "u_model" ), 1, GL_FALSE, glm::value_ptr( model ) );

        // glDrawArrays
        glBindVertexArray( drawArraysVao );
        glDrawArrays( GL_TRIANGLES, 0, DRAW_ARRAYS_NUM_POINTS );
        glDrawArrays( GL_POINTS, 0, DRAW_ARRAYS_NUM_POINTS );

        // glDrawElements
        glBindVertexArray( drawElementsVao );
        glDrawElements( GL_TRIANGLES, DRAW_ELEMENTS_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr );
        glDrawElements( GL_POINTS, DRAW_ELEMENTS_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr );
    }

    void OpenGLDrawFunctionsWidget::mousePressEvent( QMouseEvent * event )
    {
        setCursor( Qt::BlankCursor );
        camera.updateLastPos( event->x(), event->y() );
    }

    void OpenGLDrawFunctionsWidget::mouseReleaseEvent( QMouseEvent * event )
    {
        Q_UNUSED( event );
        setCursor( Qt::ArrowCursor );
    }

    void OpenGLDrawFunctionsWidget::mouseMoveEvent( QMouseEvent * event )
    {
        camera.processMouseMove( event->x(), event->y() );
    }

    bool OpenGLDrawFunctionsWidget::eventFilter( QObject * watched, QEvent * event )
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
        return false;
    }

    void OpenGLDrawFunctionsWidget::keyPressEvent( QKeyEvent * event )
    {
        camera.processKeyboardInput( event->key(), 0.05f );
    }

    void OpenGLDrawFunctionsWidget::initializeOpenGLObjects()
    {
        // glDrawArrays
        glCreateBuffers( 1, &drawArraysVbo );
        glCreateVertexArrays( 1, &drawArraysVao );
        glBindVertexArray( drawArraysVao );
        glBindBuffer( GL_ARRAY_BUFFER, drawArraysVbo );
        const std::array<Point3p3c, DRAW_ARRAYS_NUM_POINTS> DRAW_ARRAYS_POINTS{ Point3p3c{ 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
                                                                                Point3p3c{ 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
                                                                                Point3p3c{ 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f } };
        glBufferData( GL_ARRAY_BUFFER, DRAW_ARRAYS_NUM_POINTS * sizeof( Point3p3c ), DRAW_ARRAYS_POINTS.data(), GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), (void *)( 3 * sizeof( float ) ) );

        // glDrawElements
        glCreateBuffers( 1, &drawElementsVbo );
        glCreateBuffers( 1, &drawElementsEbo );
        glCreateVertexArrays( 1, &drawElementsVao );
        glBindVertexArray( drawElementsVao );
        glBindBuffer( GL_ARRAY_BUFFER, drawElementsVbo );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, drawElementsEbo );
        const std::array<Point3p3c, DRAW_ELEMENTS_NUM_POINTS> DRAW_ELEMENTS_POINTS{ Point3p3c{ 2.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f },
                                                                                    Point3p3c{ 3.0f, 0.0f, 0.0f, 0.5f, 0.5f, 0.5f },
                                                                                    Point3p3c{ 3.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f },
                                                                                    Point3p3c{ 2.0f, 1.0f, 0.0f, 0.5f, 0.5f, 0.5f } };
        const GLuint                                          DRAW_ELEMENTS_ELEMENTS[ DRAW_ELEMENTS_NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0 };
        glBufferData( GL_ARRAY_BUFFER, DRAW_ELEMENTS_NUM_POINTS * sizeof( Point3p3c ), DRAW_ELEMENTS_POINTS.data(), GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), (void *)( 3 * sizeof( float ) ) );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( DRAW_ELEMENTS_ELEMENTS ), DRAW_ELEMENTS_ELEMENTS, GL_STATIC_DRAW );
    }

    void OpenGLDrawFunctionsWidget::initializeOpenGLShaders()
    {
        QVector<QString> shaderSources;
        QFile            vertexShaderFile( ":/shaders/OpenGLDrawFunctions/main.vs" );
        if( vertexShaderFile.open( QIODevice::ReadOnly ) )
        {
            shaderSources << vertexShaderFile.readAll();
        }
        vertexShaderFile.close();
        QFile fragmentShaderFile( ":/shaders/OpenGLDrawFunctions/main.fs" );
        if( fragmentShaderFile.open( QIODevice::ReadOnly ) )
        {
            shaderSources << fragmentShaderFile.readAll();
        }
        fragmentShaderFile.close();

        addShaderProgram( { QOpenGLShader::Vertex, QOpenGLShader::Fragment }, std::forward<decltype( shaderSources )>( shaderSources ) );
    }

    void OpenGLDrawFunctionsWidget::cleanup()
    {
        // glDrawArrays
        if( drawArraysVao )
        {
            glDeleteVertexArrays( 1, &drawArraysVao );
        }
        if( drawArraysVbo )
        {
            glDeleteBuffers( 1, &drawArraysVbo );
        }

        // glDrawElements
        if( drawElementsVao )
        {
            glDeleteVertexArrays( 1, &drawElementsVao );
        }
        if( drawElementsEbo )
        {
            glDeleteBuffers( 1, &drawElementsEbo );
        }
        if( drawElementsVbo )
        {
            glDeleteBuffers( 1, &drawElementsVbo );
        }

        // shader programs
        for( auto & shaderProgram: shaderPrograms.values() )
        {
            glDeleteProgram( shaderProgram->programId() );
        }
        shaderPrograms.clear();
    }

    void OpenGLDrawFunctionsWidget::updateViewMatrix()
    {
        makeCurrent();
        QOpenGLShaderProgram * mainProgram = shaderPrograms[ "main" ];
        mainProgram->bind();
        glm::mat4 viewMatrix = camera.getViewMatrix();
        glUniformMatrix4fv( mainProgram->uniformLocation( "u_view" ), 1, GL_FALSE, glm::value_ptr( viewMatrix ) );

        update();
    }

} // namespace Ouquitoure
