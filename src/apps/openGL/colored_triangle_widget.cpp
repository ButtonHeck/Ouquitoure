#include "Apps/OpenGL/ColoredTriangleWidget"

namespace Ouquitoure
{

    ColoredTriangleWidget::ColoredTriangleWidget( const QString & name, QWidget * parent )
        : OpenGLWidgetBase( name, parent )
        , buffers( this, 2 )
    {
        points[ 0 ] = Point2p3c{ 0.5f, 0.5f, 1.0f, 0.0f, 0.0f };
        points[ 1 ] = Point2p3c{ -0.5f, 0.5f, 0.0f, 1.0f, 0.0f };
        points[ 2 ] = Point2p3c{ -0.5f, -0.5f, 0.0f, 0.0f, 1.0f };
    }

    ColoredTriangleWidget::~ColoredTriangleWidget()
    {
        cleanup();
    }

    void ColoredTriangleWidget::initializeGL()
    {
        OpenGLWidgetBase::initializeGL();
        buffers.create( VAO | VBO );

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

    const std::array<Ouquitoure::Point2p3c, ColoredTriangleWidget::NUM_POINTS> & ColoredTriangleWidget::getPoints() const noexcept
    {
        return points;
    }

    void ColoredTriangleWidget::vertexPositionChanged( int value )
    {
        bool        isX               = sender()->objectName().left( 1 ) == 'x';
        int         index             = sender()->objectName().right( 1 ).toInt();
        const float NORMALIZED_VALUE  = value / 100.0;
        float &     positionComponent = isX ? points[ index ].x() : points[ index ].y();
        positionComponent             = NORMALIZED_VALUE;
        updateData();
    }

    void ColoredTriangleWidget::vertexColorChanged( int value )
    {
        QChar       color            = sender()->objectName().left( 1 )[ 0 ];
        int         index            = sender()->objectName().right( 1 ).toInt();
        const float NORMALIZED_VALUE = value / 255.0;
        if( color == 'R' )
        {
            points[ index ].r() = NORMALIZED_VALUE;
        }
        else if( color == 'G' )
        {
            points[ index ].g() = NORMALIZED_VALUE;
        }
        else
        {
            points[ index ].b() = NORMALIZED_VALUE;
        }
        updateData();
    }

    void ColoredTriangleWidget::initializeOpenGLObjects()
    {
        buffers.bind( VAO | VBO );
        glBufferData( GL_ARRAY_BUFFER, NUM_POINTS * sizeof( Point2p3c ), points.data(), GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, sizeof( Point2p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point2p3c ), (void *)( 2 * sizeof( GLfloat ) ) );
    }

    void ColoredTriangleWidget::initializeOpenGLShaders()
    {
        OpenGLWidgetBase::initializeOpenGLMainShaderProgram( "ColoredTriangle" );
    }

    void ColoredTriangleWidget::cleanup()
    {
        buffers.deleteBuffers();
        openGLShaderProgramsCleanup();
    }

    void ColoredTriangleWidget::updateData()
    {
        makeCurrent();
        glBufferData( GL_ARRAY_BUFFER, NUM_POINTS * sizeof( Point2p3c ), points.data(), GL_STATIC_DRAW );
        update();
    }

} // namespace Ouquitoure
