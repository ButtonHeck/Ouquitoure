#include "Apps/OpenGL/ImageProcessingWidget"

#include <QGLWidget>

namespace Ouquitoure
{

    ImageProcessingWidget::ImageProcessingWidget( const QString & name, QWidget * parent )
        : OpenGLWidgetBase( name, parent )
        , buffers( this, 3 )
        , image( ":/otherImages/Alisa.png" )
        , textureID( 0 )
    {
        points[ 0 ] = Point2p2t{ -0.95f, -0.95f, 0.0f, 0.0f };
        points[ 1 ] = Point2p2t{ 0.95f, -0.95f, 1.0f, 0.0f };
        points[ 2 ] = Point2p2t{ 0.95f, 0.95f, 1.0f, 1.0f };
        points[ 3 ] = Point2p2t{ -0.95f, 0.95f, 0.0f, 1.0f };
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
        initializeOpenGLShaders();
        initializeOpenGLObjects();

        QOpenGLShaderProgram * mainProgram = shaderPrograms[ "main" ];
        mainProgram->bind();
    }

    void ImageProcessingWidget::paintGL()
    {
        buffers.bind( VAO );
        glClear( GL_COLOR_BUFFER_BIT );
        glBindTexture( GL_TEXTURE_2D, textureID );
        glDrawElements( GL_TRIANGLES, NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr );
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

        // load texture image to OpenGL
        glCreateTextures( GL_TEXTURE_2D, 1, &textureID );
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, textureID );
        QImage convertedImage = QGLWidget::convertToGLFormat( image );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA32F, convertedImage.width(), convertedImage.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                      convertedImage.constBits() );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        shaderPrograms[ "main" ]->bind();
        glUniform1i( glGetUniformLocation( shaderPrograms[ "main" ]->programId(), "u_image" ), 0 );
    }

    void ImageProcessingWidget::initializeOpenGLShaders()
    {
        OpenGLWidgetBase::initializeOpenGLMainShaderProgram( "ImageProcessing" );
    }

    void ImageProcessingWidget::cleanup()
    {
        buffers.deleteBuffers();
        openGLShaderProgramsCleanup();
    }

} // namespace Ouquitoure
