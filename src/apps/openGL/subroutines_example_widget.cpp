#include "Apps/OpenGL/SubroutinesExampleWidget"

#include <algorithm>

namespace Ouquitoure
{

    SubroutinesExampleWidget::SubroutinesExampleWidget( const QString & name, QWidget * parent )
        : OpenGLWidgetBase( name, parent )
        , buffers( this )
        , subroutineUniformLocation( 0 )
    {
        points[ 0 ] = Point2p3c{ -0.8, -0.8, 1.0, 0.33, 0.1 };
        points[ 1 ] = Point2p3c{ -0.0, 0.8, 0.2, 1.0, 0.5 };
        points[ 2 ] = Point2p3c{ 0.8, -0.8, 0.5, 0.2, 1.0 };
    }

    SubroutinesExampleWidget::~SubroutinesExampleWidget()
    {
        cleanup();
    }

    void SubroutinesExampleWidget::initializeGL()
    {
        OpenGLWidgetBase::initializeGL();

        glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
        initializeOpenGLObjects();
        initializeOpenGLShaders();

        QOpenGLShaderProgram * mainProgram = shaderPrograms[ "main" ];
        mainProgram->bind();

        // subroutine uniforms are not part of the program object state, thus each time shader program is activated this should be updated
        subroutineUniformLocation = glGetSubroutineUniformLocation( mainProgram->programId(), GL_FRAGMENT_SHADER, "colorFunc" );
        for( int subroutineIndex = 0; subroutineIndex < NUM_SUBROUTINES; ++subroutineIndex )
        {
            subroutineIndices[ QString( SUBROUTINE_NAMES[ subroutineIndex ].data() ) ] =
                glGetSubroutineIndex( mainProgram->programId(), GL_FRAGMENT_SHADER, SUBROUTINE_NAMES[ subroutineIndex ].data() );
        }
    }

    void SubroutinesExampleWidget::paintGL()
    {
        glClear( GL_COLOR_BUFFER_BIT );
        glDrawArrays( GL_TRIANGLES, 0, NUM_POINTS );
    }

    void SubroutinesExampleWidget::switchSubroutine()
    {
        // technically there should be created array with the size of max uniform locations and be updated at one exact uniform location
        // (which represents colorFunc), but in glsl code I've hardcoded location of that uniform to be 0.
        makeCurrent();
        QString name = sender()->objectName();
        if( subroutineIndices.contains( name ) )
        {
            GLuint subroutineIndex = subroutineIndices[ name ];
            glUniformSubroutinesuiv( GL_FRAGMENT_SHADER, 1, &subroutineIndex );
        }
        update();
    }

    void SubroutinesExampleWidget::initializeOpenGLObjects()
    {
        buffers.create( VAO | VBO );
        buffers.bind( VAO | VBO );
        glBufferData( GL_ARRAY_BUFFER, NUM_POINTS * sizeof( Point2p3c ), points.data(), GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, sizeof( Point2p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point2p3c ), (void *)( 2 * sizeof( GLfloat ) ) );
    }

    void SubroutinesExampleWidget::initializeOpenGLShaders()
    {
        OpenGLWidgetBase::initializeOpenGLMainShaderProgram( "SubroutinesExample" );
    }

    void SubroutinesExampleWidget::cleanup()
    {
        buffers.deleteBuffers();
        openGLShaderProgramsCleanup();
    }

} // namespace Ouquitoure
