#include "Apps/OpenGL/OpenGLDrawFunctionsWidget"

#include <QFile>
#include <glm/gtc/type_ptr.hpp>
#include <array>

#include "Math/Point3Pos3Color"
#include "Log"

namespace Ouquitoure
{

    OpenGLDrawFunctionsWidget::OpenGLDrawFunctionsWidget( const QString & name, QWidget * parent )
        : OpenGLWidgetWithCamera( name, parent )

        // glDrawArrays
        , drawArraysVao( 0 )
        , drawArraysVbo( 0 )

        // glDrawArraysInstanced + glDrawArraysInstancedBaseInstance
        , drawArraysInstancedVao( 0 )
        , drawArraysInstancedVbo( 0 )
        , drawArraysInstancedVboInstanced( 0 )

        // glDrawArraysIndirect
        , drawArraysIndirectVao( 0 )
        , drawArraysIndirectVbo( 0 )
        , drawArraysIndirectVboInstanced( 0 )
        , drawArraysIndirectDibo( 0 )

        // glDrawElements
        , drawElementsVao( 0 )
        , drawElementsVbo( 0 )
        , drawElementsEbo( 0 )
    {
    }

    OpenGLDrawFunctionsWidget::~OpenGLDrawFunctionsWidget()
    {
        cleanup();
    }

    void OpenGLDrawFunctionsWidget::initializeGL()
    {
        OpenGLWidgetBase::initializeGL();
        cleanup();

        glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
        glPointSize( 5.0f );
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

        initializeOpenGLObjects();
        initializeOpenGLShaders();

        updateViewMatrixForMainProgram();
        updateProjectionMatrixForMainProgram();
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

        // glDrawArraysInstanced + glDrawArraysInstancedBaseInstance
        glBindVertexArray( drawArraysInstancedVao );
        glDrawArraysInstanced( GL_TRIANGLES, 0, DRAW_ARRAYS_INSTANCED_NUM_POINTS, DRAW_ARRAYS_INSTANCED_NUM_INSTANCES );
        glDrawArraysInstanced( GL_POINTS, 0, DRAW_ARRAYS_INSTANCED_NUM_POINTS, DRAW_ARRAYS_INSTANCED_NUM_INSTANCES );
        glLineWidth( 3.0f );
        glDrawArraysInstancedBaseInstance( GL_TRIANGLES, 0, DRAW_ARRAYS_INSTANCED_NUM_POINTS, DRAW_ARRAYS_INSTANCED_NUM_INSTANCES, 1 );
        glLineWidth( 1.0f );

        // glDrawArraysIndirect
        glBindVertexArray( drawArraysIndirectVao );
        glDrawArraysIndirect( GL_TRIANGLES, nullptr );
        glDrawArraysIndirect( GL_POINTS, nullptr );

        // glDrawElements
        glBindVertexArray( drawElementsVao );
        glDrawElements( GL_TRIANGLES, DRAW_ELEMENTS_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr );
        glDrawElements( GL_POINTS, DRAW_ELEMENTS_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr );
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

        // glDrawArraysInstanced
        glCreateBuffers( 1, &drawArraysInstancedVbo );
        glCreateBuffers( 1, &drawArraysInstancedVboInstanced );
        glCreateVertexArrays( 1, &drawArraysInstancedVao );
        glBindVertexArray( drawArraysInstancedVao );
        glBindBuffer( GL_ARRAY_BUFFER, drawArraysInstancedVbo );
        const std::array<Point3p3c, DRAW_ARRAYS_INSTANCED_NUM_POINTS> DRAW_ARRAYS_INSTANCED_POINTS{
            Point3p3c{ 0.0f, -2.0f, 0.0f, 0.8f, 0.8f, 0.8f }, Point3p3c{ 1.0f, -2.0f, 0.0f, 0.8f, 0.8f, 0.8f },
            Point3p3c{ 1.0f, -1.0f, 0.0f, 0.8f, 0.8f, 0.8f }
        };
        glBufferData( GL_ARRAY_BUFFER, sizeof( DRAW_ARRAYS_INSTANCED_POINTS ), DRAW_ARRAYS_INSTANCED_POINTS.data(), GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), (void *)( 3 * sizeof( float ) ) );
        glBindBuffer( GL_ARRAY_BUFFER, drawArraysInstancedVboInstanced );
        const float DRAW_ARRAYS_INSTANCED_Z_OFFSETS[ DRAW_ARRAYS_INSTANCED_NUM_INSTANCES ]{ 0.0f, -0.5f, -1.0f, -1.5f };
        glBufferData( GL_ARRAY_BUFFER, sizeof( DRAW_ARRAYS_INSTANCED_Z_OFFSETS ), DRAW_ARRAYS_INSTANCED_Z_OFFSETS, GL_STATIC_DRAW );
        glEnableVertexAttribArray( 2 );
        glVertexAttribPointer( 2, 1, GL_FLOAT, GL_FALSE, sizeof( GLfloat ), 0 );
        glVertexAttribDivisor( 2, 1 );

        // glDrawArraysIndirect
        glCreateBuffers( 1, &drawArraysIndirectVbo );
        glCreateBuffers( 1, &drawArraysIndirectDibo );
        glCreateBuffers( 1, &drawArraysIndirectVboInstanced );
        glCreateVertexArrays( 1, &drawArraysIndirectVao );
        glBindVertexArray( drawArraysIndirectVao );
        glBindBuffer( GL_ARRAY_BUFFER, drawArraysIndirectVbo );
        const Point3p3c DRAW_ARRAYS_INDIRECT_POINTS[ DRAW_ARRAYS_INDIRECT_NUM_POINTS ]{ Point3p3c{ 0.0f, -5.0f, 0.0f, 0.6f, 0.6f, 0.6f },
                                                                                        Point3p3c{ 1.0f, -5.0f, 0.0f, 0.6f, 0.6f, 0.6f },
                                                                                        Point3p3c{ 0.5f, -4.0f, 0.0f, 0.6f, 0.6f, 0.6f } };
        glBufferData( GL_ARRAY_BUFFER, sizeof( DRAW_ARRAYS_INDIRECT_POINTS ), DRAW_ARRAYS_INDIRECT_POINTS, GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), (void *)( 3 * sizeof( float ) ) );
        glBindBuffer( GL_DRAW_INDIRECT_BUFFER, drawArraysIndirectDibo );
        const DrawArraysIndirectCommand DRAW_INDIRECT_DATA{ 3, DRAW_ARRAYS_INDIRECT_NUM_INSTANCES, 0, 0 };
        glBufferData( GL_DRAW_INDIRECT_BUFFER, sizeof( DRAW_INDIRECT_DATA ), &DRAW_INDIRECT_DATA, GL_STATIC_DRAW );
        glBindBuffer( GL_ARRAY_BUFFER, drawArraysIndirectVboInstanced );
        const float DRAW_ARRAYS_INDIRECT_Z_OFFSETS[ DRAW_ARRAYS_INDIRECT_NUM_INSTANCES ]{ 0.0f, 0.5f };
        glBufferData( GL_ARRAY_BUFFER, sizeof( DRAW_ARRAYS_INDIRECT_Z_OFFSETS ), DRAW_ARRAYS_INDIRECT_Z_OFFSETS, GL_STATIC_DRAW );
        glEnableVertexAttribArray( 2 );
        glVertexAttribPointer( 2, 1, GL_FLOAT, GL_FALSE, sizeof( GLfloat ), 0 );
        glVertexAttribDivisor( 2, 1 );

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

        // glDrawArraysInstanced
        if( drawArraysInstancedVao )
        {
            glDeleteVertexArrays( 1, &drawArraysInstancedVao );
        }
        if( drawArraysInstancedVbo )
        {
            glDeleteBuffers( 1, &drawArraysInstancedVbo );
        }
        if( drawArraysInstancedVboInstanced )
        {
            glDeleteBuffers( 1, &drawArraysInstancedVboInstanced );
        }

        // glDrawArraysIndirect
        if( drawArraysIndirectVao )
        {
            glDeleteVertexArrays( 1, &drawArraysIndirectVao );
        }
        if( drawArraysIndirectVbo )
        {
            glDeleteBuffers( 1, &drawArraysIndirectVbo );
        }
        if( drawArraysIndirectVboInstanced )
        {
            glDeleteBuffers( 1, &drawArraysIndirectVboInstanced );
        }
        if( drawArraysIndirectDibo )
        {
            glDeleteBuffers( 1, &drawArraysIndirectDibo );
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

} // namespace Ouquitoure
