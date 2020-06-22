#include "OpenGLApps/ColoredTriangleWidget"

#include <QFile>

#include <utility>

namespace Ouquitoure
{

    ColoredTriangleWidget::ColoredTriangleWidget( const QString & name, QWidget * parent )
        : OpenGLWidgetBase( name, parent )
    {
    }

    ColoredTriangleWidget::~ColoredTriangleWidget()
    {
        if( glInitialized )
        {
            glDeleteBuffers( 1, &vbo );
            glDeleteVertexArrays( 1, &vao );
        }
    }

    void ColoredTriangleWidget::initializeGL()
    {
        OpenGLWidgetBase::initializeGL();
        glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
        initializeOpenGLObjects();
        initializeOpenGLShaders();

        QOpenGLShaderProgram * mainProgram = shaderPrograms[ "main" ];
        mainProgram->bind();
    }

    void ColoredTriangleWidget::paintGL()
    {
        glClear( GL_COLOR_BUFFER_BIT );
        GLfloat data[ 2 * 3 + 3 * 3 ]{ 0.5, 0.5, 1.0, 0.0, 0.0, -0.5, 0.5, 0.0, 1.0, 0.0, -0.5, -0.5, 0.0, 0.0, 1.0 };
        glBindBuffer( GL_ARRAY_BUFFER, vbo );
        glBufferData( GL_ARRAY_BUFFER, sizeof( data ), data, GL_STATIC_DRAW );

        glDrawArrays( GL_TRIANGLES, 0, 3 );
    }

    void ColoredTriangleWidget::initializeOpenGLObjects()
    {
        glCreateBuffers( 1, &vbo );
        glCreateVertexArrays( 1, &vao );
        glBindVertexArray( vao );
        glBindBuffer( GL_ARRAY_BUFFER, vbo );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), (void *)( 2 * sizeof( GLfloat ) ) );
    }

    void ColoredTriangleWidget::initializeOpenGLShaders()
    {
        QVector<QString> shaderSources;
        QFile            vertexShaderFile( ":/shaders/ColoredTriangle/main.vs" );
        if( vertexShaderFile.open( QIODevice::ReadOnly ) )
        {
            shaderSources << vertexShaderFile.readAll();
        }
        vertexShaderFile.close();
        QFile fragmentShaderFile( ":/shaders/ColoredTriangle/main.fs" );
        if( fragmentShaderFile.open( QIODevice::ReadOnly ) )
        {
            shaderSources << fragmentShaderFile.readAll();
        }
        fragmentShaderFile.close();

        addShaderProgram( { QOpenGLShader::Vertex, QOpenGLShader::Fragment },
                          std::forward<decltype( shaderSources )>( shaderSources ) );
    }

} // namespace Ouquitoure
