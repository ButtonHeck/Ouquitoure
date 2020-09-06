#include "Apps/OpenGL/BlendModesWidget"
#include "Log"

namespace Ouquitoure
{

    BlendModesWidget::BlendModesWidget( const QString & name, QWidget * parent )
        : OpenGLWidgetBase( name, parent )
        , buffers( this, 3 )
        , srcBlendFunc( GL_SRC_ALPHA )
        , dstBlendFunc( GL_ONE_MINUS_SRC_ALPHA )
        , blendColorRGBA{ 0.0f, 0.0f, 0.0f, 1.0f }
    {
        // first quad points
        points[ 0 ] = Point2p4c{ -0.9f, -0.4f, 1.0f, 0.0f, 0.0f, 1.0f };
        points[ 1 ] = Point2p4c{ 0.4f, -0.4f, 1.0f, 0.0f, 0.0f, 1.0f };
        points[ 2 ] = Point2p4c{ 0.4f, 0.9f, 1.0f, 0.0f, 0.0f, 1.0f };
        points[ 3 ] = Point2p4c{ -0.9f, 0.9f, 1.0f, 0.0f, 0.0f, 1.0f };
        // second quad points
        points[ 4 ] = Point2p4c{ -0.4f, -0.9f, 0.25f, 0.5f, 1.0f, 0.5f };
        points[ 5 ] = Point2p4c{ 0.9f, -0.9f, 0.25f, 0.5f, 1.0f, 0.5f };
        points[ 6 ] = Point2p4c{ 0.9f, 0.4f, 0.25f, 0.5f, 1.0f, 0.5f };
        points[ 7 ] = Point2p4c{ -0.4f, 0.4f, 0.25f, 0.5f, 1.0f, 0.5f };
    }

    BlendModesWidget::~BlendModesWidget()
    {
        cleanup();
    }

    void BlendModesWidget::initializeGL()
    {
        OpenGLWidgetBase::initializeGL();
        buffers.create( VAO | VBO | EBO );

        glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
        glEnable( GL_BLEND );
        glBlendFunc( srcBlendFunc, dstBlendFunc );
        initializeOpenGLObjects();
        initializeOpenGLShaders();

        QOpenGLShaderProgram * mainProgram = shaderPrograms[ "main" ];
        mainProgram->bind();
    }

    void BlendModesWidget::paintGL()
    {
        buffers.bind( VAO );
        glDrawElements( GL_TRIANGLES, NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr );
    }

    const std::array<Point2p4c, BlendModesWidget::NUM_POINTS> & BlendModesWidget::getPoints() const noexcept
    {
        return points;
    }

    void BlendModesWidget::quadColorChanged( int value )
    {
        QChar       color            = sender()->objectName().left( 1 )[ 0 ];
        int         index            = sender()->objectName().right( 1 ).toInt();
        const float NORMALIZED_VALUE = value / 255.0;
        for( int pointIndex = index * 4; pointIndex < index * 4 + 4; ++pointIndex )
        {
            if( color == 'R' )
            {
                points[ pointIndex ].r() = NORMALIZED_VALUE;
            }
            else if( color == 'G' )
            {
                points[ pointIndex ].g() = NORMALIZED_VALUE;
            }
            else
            {
                points[ pointIndex ].b() = NORMALIZED_VALUE;
            }
        }
        updateData();
    }

    void BlendModesWidget::blendFuncModeChanged()
    {
        makeCurrent();
        QString name  = sender()->objectName();
        int     index = name.left( 1 ).toInt();
        GLenum  code  = name.mid( 1 ).toInt();
        if( index == 0 )
        {
            srcBlendFunc = code;
        }
        else
        {
            dstBlendFunc = code;
        }
        glBlendFunc( srcBlendFunc, dstBlendFunc );
        update();
    }

    void BlendModesWidget::blendColorChanged( int value )
    {
        makeCurrent();
        const GLclampf NORMALIZED_COLOR = value / 255.0f;
        QChar          colorCode        = sender()->objectName()[ 0 ];
        if( colorCode == 'R' )
        {
            blendColorRGBA[ 0 ] = NORMALIZED_COLOR;
        }
        else if( colorCode == 'G' )
        {
            blendColorRGBA[ 1 ] = NORMALIZED_COLOR;
        }
        else if( colorCode == 'B' )
        {
            blendColorRGBA[ 2 ] = NORMALIZED_COLOR;
        }
        glBlendColor( blendColorRGBA[ 0 ], blendColorRGBA[ 1 ], blendColorRGBA[ 2 ], blendColorRGBA[ 3 ] );
        update();
    }

    void BlendModesWidget::blendFuncEquationChanged()
    {
        makeCurrent();
        GLenum equationCode = sender()->objectName().toInt();
        glBlendEquation( equationCode );
        update();
    }

    void BlendModesWidget::initializeOpenGLObjects()
    {
        buffers.bind( VAO | VBO | EBO );
        glBufferData( GL_ARRAY_BUFFER, NUM_POINTS * sizeof( Point2p4c ), points.data(), GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, sizeof( Point2p4c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, sizeof( Point2p4c ), (void *)( 2 * sizeof( GLfloat ) ) );

        const GLuint indices[ NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 };
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, NUM_ELEMENTS * sizeof( GLuint ), indices, GL_STATIC_DRAW );
    }

    void BlendModesWidget::initializeOpenGLShaders()
    {
        OpenGLWidgetBase::initializeOpenGLMainShaderProgram( "BlendModes" );
    }

    void BlendModesWidget::cleanup()
    {
        buffers.deleteBuffers();
        openGLShaderProgramsCleanup();
    }

    void BlendModesWidget::updateData()
    {
        makeCurrent();
        glBufferData( GL_ARRAY_BUFFER, NUM_POINTS * sizeof( Point2p4c ), points.data(), GL_STATIC_DRAW );
        update();
    }

} // namespace Ouquitoure
