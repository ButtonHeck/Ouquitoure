#include "Apps/OpenGL/ImageProcessingWidget"

namespace Ouquitoure
{

    ImageProcessingWidget::ImageProcessingWidget( const QString & name, QWidget * parent )
        : OpenGLWidgetBase( name, parent )
        , buffers( this, 3 )
        , image( ":/otherImages/Alisa.png" )
    {
        points[ 0 ] = Point2p2t{ -0.95f, -0.95f, 0.0f, 0.0f };
        points[ 1 ] = Point2p2t{ 0.95f, -0.95f, 1.0f, 0.0f };
        points[ 2 ] = Point2p2t{ 0.95f, 0.95f, 1.0f, 1.0f };
        points[ 2 ] = Point2p2t{ -0.95f, 0.95f, 0.0f, 1.0f };
    }

    ImageProcessingWidget::~ImageProcessingWidget()
    {
        cleanup();
    }

    void ImageProcessingWidget::initializeGL()
    {
        OpenGLWidgetBase::initializeGL();
        buffers.create( VAO | VBO | EBO );
        glClearColor( 1.0f, 1.0f, 1.0f, 1.0f );
        initializeOpenGLObjects();
        initializeOpenGLShaders();
    }

    void ImageProcessingWidget::paintGL()
    {
    }

    void ImageProcessingWidget::initializeOpenGLObjects()
    {
        buffers.bind( VAO | VBO | EBO );
        glBufferData( GL_ARRAY_BUFFER, NUM_POINTS * sizeof( Point2p2t ), points.data(), GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, sizeof( Point2p2t ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, sizeof( Point2p2t ), (void *)( 2 * sizeof( GLfloat ) ) );
        const GLuint ELEMENTS[ NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0 };
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( ELEMENTS ), ELEMENTS, GL_STATIC_DRAW );
    }

    void ImageProcessingWidget::initializeOpenGLShaders()
    {
    }

    void ImageProcessingWidget::cleanup()
    {
        buffers.deleteBuffers();
        openGLShaderProgramsCleanup();
    }

} // namespace Ouquitoure
