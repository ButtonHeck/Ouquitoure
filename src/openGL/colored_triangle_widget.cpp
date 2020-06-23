#include "OpenGLApps/ColoredTriangleWidget"

#include <QFile>
#include <utility>

namespace Ouquitoure
{

    ColoredTriangleWidget::ColoredTriangleWidget( const QString & name, QWidget * parent )
        : OpenGLWidgetBase( name, parent )
        , vao( 0 )
        , vbo( 0 )
    {
        points[ 0 ] = Point2p3c{ 0.5, 0.5, 1.0, 0.0, 0.0 };
        points[ 1 ] = Point2p3c{ -0.5, 0.5, 0.0, 1.0, 0.0 };
        points[ 2 ] = Point2p3c{ -0.5, -0.5, 0.0, 0.0, 1.0 };
    }

    ColoredTriangleWidget::~ColoredTriangleWidget()
    {
        cleanup();
    }

    void ColoredTriangleWidget::initializeGL()
    {
        OpenGLWidgetBase::initializeGL();
        /* QDockWidget (un)docking invokes reinitialization of a GL context,
         * thus every OpenGL related objects (shader programs, buffers etc.) should be deleted explicitly
         * (if any of them were created during previous context initialization)
         */
        cleanup();

        glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
        initializeOpenGLObjects();
        initializeOpenGLShaders();

        QOpenGLShaderProgram * mainProgram = shaderPrograms[ "main" ];
        mainProgram->bind();
    }

    void ColoredTriangleWidget::paintGL()
    {
        glClear( GL_COLOR_BUFFER_BIT );
        glDrawArrays( GL_TRIANGLES, 0, NUM_POINTS );
    }

    const std::array<Ouquitoure::Point2p3c, ColoredTriangleWidget::NUM_POINTS> &
    ColoredTriangleWidget::getPoints() const noexcept
    {
        return points;
    }

    void ColoredTriangleWidget::vertexPositionChanged( int value )
    {
        bool isX   = sender()->objectName().left( 1 ) == 'x';
        int  index = sender()->objectName().right( 1 ).toInt();
        if( isX )
        {
            points[ index ].point.posColor.x = value / 100.0;
        }
        else
        {
            points[ index ].point.posColor.y = value / 100.0;
        }
        updateData();
    }

    void ColoredTriangleWidget::vertexColorChanged( int value )
    {
        QChar color = sender()->objectName().left( 1 )[ 0 ];
        int   index = sender()->objectName().right( 1 ).toInt();
        if( color == 'R' )
        {
            points[ index ].point.posColor.r = value / 255.0;
        }
        else if( color == 'G' )
        {
            points[ index ].point.posColor.g = value / 255.0;
        }
        else
        {
            points[ index ].point.posColor.b = value / 255.0;
        }
        updateData();
    }

    void ColoredTriangleWidget::initializeOpenGLObjects()
    {
        glCreateBuffers( 1, &vbo );
        glCreateVertexArrays( 1, &vao );
        glBindVertexArray( vao );
        glBindBuffer( GL_ARRAY_BUFFER, vbo );
        glBufferData( GL_ARRAY_BUFFER, points.size() * sizeof( Point2p3c ), points.data(), GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, sizeof( Point2p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point2p3c ), (void *)( 2 * sizeof( GLfloat ) ) );
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

    void ColoredTriangleWidget::cleanup()
    {
        if( vao )
        {
            glDeleteVertexArrays( 1, &vao );
        }
        if( vbo )
        {
            glDeleteBuffers( 1, &vbo );
        }
        for( auto & shaderProgram: shaderPrograms.values() )
        {
            glDeleteProgram( shaderProgram->programId() );
        }
        shaderPrograms.clear();
    }

    void ColoredTriangleWidget::updateData()
    {
        makeCurrent();
        glBufferData( GL_ARRAY_BUFFER, points.size() * sizeof( Point2p3c ), points.data(), GL_STATIC_DRAW );
        update();
    }

} // namespace Ouquitoure
