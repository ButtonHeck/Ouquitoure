#include "OpenGLApps/ColoredTriangleWidget"

#include <QFile>

#include <utility>

namespace Ouquitoure
{

    ColoredTriangleWidget::ColoredTriangleWidget( const QString & name, QWidget * parent )
        : OpenGLWidgetBase( name, parent )
    {
    }

    void ColoredTriangleWidget::initializeGL()
    {
        OpenGLWidgetBase::initializeGL();
        QVector<QString>                   shaderSources;
        QVector<QOpenGLShader::ShaderType> shaderTypes{ QOpenGLShader::Vertex, QOpenGLShader::Fragment };
        QFile                              vertexShaderFile( ":/shaders/ColoredTriangle/main.vs" );
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

        addShaderProgram( std::forward<decltype( shaderTypes )>( shaderTypes ),
                          std::forward<decltype( shaderSources )>( shaderSources ) );
    }

    void ColoredTriangleWidget::paintGL()
    {
        makeCurrent();
        glClearColor( 1.0, 0.0, 1.0, 1.0 );
        glClear( GL_COLOR_BUFFER_BIT );
        QOpenGLShaderProgram * pr = shaderPrograms[ "main" ];
        pr->bind();
        GLfloat data[ 2 * 3 + 3 * 3 ]{ 0.5, 0.5, 1.0, 0.0, 0.0, -0.5, 0.5, 0.0, 1.0, 0.0, -0.5, -0.5, 0.0, 0.0, 1.0 };
        GLuint  vbo;
        glGenBuffers( 1, &vbo );
        glBindBuffer( GL_ARRAY_BUFFER, vbo );
        glBufferData( GL_ARRAY_BUFFER, sizeof( data ), data, GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof( GLfloat ), (void *)( 2 * sizeof( GLfloat ) ) );

        glDrawArrays( GL_TRIANGLES, 0, 3 );
    }

} // namespace Ouquitoure
