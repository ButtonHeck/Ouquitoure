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

        // glDrawElementsBaseVertex
        , drawElementsBVVao( 0 )
        , drawElementsBVVbo( 0 )
        , drawElementsBVEbo( 0 )

        // glDrawElementsIndirect
        , drawElementsIndirectVao( 0 )
        , drawElementsIndirectVbo( 0 )
        , drawElementsIndirectEbo( 0 )
        , drawElementsIndirectDibo( 0 )

        // glDrawElementsInstanced + glDrawElementsInstancedBaseInstance
        , drawElementsInstancedVao( 0 )
        , drawElementsInstancedVbo( 0 )
        , drawElementsInstancedVboInstanced( 0 )
        , drawElementsInstancedEbo( 0 )

        // glDrawElementsInstancedBaseVertex + glDrawElementsInstancedBaseVertexBaseInstance
        , drawElementsInstancedBVVao( 0 )
        , drawElementsInstancedBVVbo( 0 )
        , drawElementsInstancedBVVboInstanced( 0 )
        , drawElementsInstancedBVEbo( 0 )
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
        glBindBuffer( GL_DRAW_INDIRECT_BUFFER, drawArraysIndirectDibo );
        glDrawArraysIndirect( GL_TRIANGLES, nullptr );
        glDrawArraysIndirect( GL_POINTS, nullptr );

        // glDrawElements
        glBindVertexArray( drawElementsVao );
        glDrawElements( GL_TRIANGLES, DRAW_ELEMENTS_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr );
        glDrawElements( GL_POINTS, DRAW_ELEMENTS_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr );

        // glDrawElementsBaseVertex
        glBindVertexArray( drawElementsBVVao );
        glDrawElementsBaseVertex( GL_TRIANGLES, DRAW_ELEMENTS_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr, 2 );
        glDrawElementsBaseVertex( GL_POINTS, DRAW_ELEMENTS_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr, 2 );

        // glDrawElementsIndirect
        glBindVertexArray( drawElementsIndirectVao );
        glBindBuffer( GL_DRAW_INDIRECT_BUFFER, drawElementsIndirectDibo );
        glDrawElementsIndirect( GL_TRIANGLES, GL_UNSIGNED_INT, nullptr );
        glDrawElementsIndirect( GL_POINTS, GL_UNSIGNED_INT, nullptr );

        // glDrawElementsInstanced + glDrawElementsInstancedBaseInstance
        glBindVertexArray( drawElementsInstancedVao );
        glDrawElementsInstanced( GL_TRIANGLES, DRAW_ELEMENTS_INSTANCED_NUM_ELEMENTS, GL_UNSIGNED_INT, 0,
                                 DRAW_ELEMENTS_INSTANCED_NUM_INSTANCES );
        glDrawElementsInstanced( GL_POINTS, DRAW_ELEMENTS_INSTANCED_NUM_ELEMENTS, GL_UNSIGNED_INT, 0,
                                 DRAW_ELEMENTS_INSTANCED_NUM_INSTANCES );
        glLineWidth( 3.0f );
        glDrawElementsInstancedBaseInstance( GL_TRIANGLES, DRAW_ELEMENTS_INSTANCED_NUM_ELEMENTS, GL_UNSIGNED_INT, 0,
                                             DRAW_ELEMENTS_INSTANCED_NUM_INSTANCES, 1 );
        glLineWidth( 1.0f );

        // glDrawElementsInstancedBaseVertex + glDrawElementsInstancedBaseVertexBaseInstance
        glBindVertexArray( drawElementsInstancedBVVao );
        glDrawElementsInstancedBaseVertex( GL_TRIANGLES, DRAW_ELEMENTS_INSTANCED_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, 0,
                                           DRAW_ELEMENTS_INSTANCED_BV_NUM_INSTANCES, 1 );
        glDrawElementsInstancedBaseVertex( GL_POINTS, DRAW_ELEMENTS_INSTANCED_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, 0,
                                           DRAW_ELEMENTS_INSTANCED_BV_NUM_INSTANCES, 1 );
        glLineWidth( 3.0f );
        glDrawElementsInstancedBaseVertexBaseInstance( GL_TRIANGLES, DRAW_ELEMENTS_INSTANCED_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, 0,
                                                       DRAW_ELEMENTS_INSTANCED_BV_NUM_INSTANCES, 1, 1 );
        glDrawElementsInstancedBaseVertexBaseInstance( GL_POINTS, DRAW_ELEMENTS_INSTANCED_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, 0,
                                                       DRAW_ELEMENTS_INSTANCED_BV_NUM_INSTANCES, 1, 1 );
        glLineWidth( 1.0f );
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
            Point3p3c{ 0.0f, -2.0f, 0.0f, 0.75f, 0.75f, 0.75f }, Point3p3c{ 1.0f, -2.0f, 0.0f, 0.75f, 0.75f, 0.75f },
            Point3p3c{ 1.0f, -1.0f, 0.0f, 0.75f, 0.75f, 0.75f }
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
        const Point3p3c DRAW_ARRAYS_INDIRECT_POINTS[ DRAW_ARRAYS_INDIRECT_NUM_POINTS ]{ Point3p3c{ 0.0f, -5.0f, 0.0f, 0.5f, 0.5f, 0.5f },
                                                                                        Point3p3c{ 1.0f, -5.0f, 0.0f, 0.5f, 0.5f, 0.5f },
                                                                                        Point3p3c{ 0.5f, -4.0f, 0.0f, 0.5f, 0.5f, 0.5f } };
        glBufferData( GL_ARRAY_BUFFER, sizeof( DRAW_ARRAYS_INDIRECT_POINTS ), DRAW_ARRAYS_INDIRECT_POINTS, GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), (void *)( 3 * sizeof( float ) ) );
        glBindBuffer( GL_DRAW_INDIRECT_BUFFER, drawArraysIndirectDibo );
        const DrawArraysIndirectCommand DRAW_INDIRECT_DATA{ 3, DRAW_ARRAYS_INDIRECT_NUM_INSTANCES, 0, 0 };
        glBufferData( GL_DRAW_INDIRECT_BUFFER, sizeof( DRAW_INDIRECT_DATA ), &DRAW_INDIRECT_DATA, GL_STATIC_DRAW );
        glBindBuffer( GL_ARRAY_BUFFER, drawArraysIndirectVboInstanced );
        const float DRAW_ARRAYS_INDIRECT_Z_OFFSETS[ DRAW_ARRAYS_INDIRECT_NUM_INSTANCES ]{ 0.0f, -0.5f };
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
        const std::array<Point3p3c, DRAW_ELEMENTS_NUM_POINTS> DRAW_ELEMENTS_POINTS{ Point3p3c{ 2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
                                                                                    Point3p3c{ 3.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
                                                                                    Point3p3c{ 3.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f },
                                                                                    Point3p3c{ 2.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f } };
        const GLuint                                          DRAW_ELEMENTS_ELEMENTS[ DRAW_ELEMENTS_NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0 };
        glBufferData( GL_ARRAY_BUFFER, DRAW_ELEMENTS_NUM_POINTS * sizeof( Point3p3c ), DRAW_ELEMENTS_POINTS.data(), GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), (void *)( 3 * sizeof( float ) ) );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( DRAW_ELEMENTS_ELEMENTS ), DRAW_ELEMENTS_ELEMENTS, GL_STATIC_DRAW );

        // glDrawElementsBaseVertex
        glCreateBuffers( 1, &drawElementsBVEbo );
        glCreateBuffers( 1, &drawElementsBVVbo );
        glCreateVertexArrays( 1, &drawElementsBVVao );
        glBindVertexArray( drawElementsBVVao );
        glBindBuffer( GL_ARRAY_BUFFER, drawElementsBVVbo );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, drawElementsBVEbo );
        const std::array<Point3p3c, DRAW_ELEMENTS_BV_NUM_POINTS> DRAW_ELEMENTS_BV_POINTS{
            Point3p3c{ 2.0f, -1.0f, 0.0f, 0.75f, 0.0f, 0.0f },  Point3p3c{ 3.0f, -1.0f, 0.0f, 0.8f, 0.0f, 0.0f },
            Point3p3c{ 3.0f, -2.0f, 0.0f, 0.75f, 0.0f, 0.0f },  Point3p3c{ 2.0f, -2.0f, 0.0f, 0.8f, 0.0f, 0.0f },
            Point3p3c{ 2.0f, -1.0f, -0.5f, 0.75f, 0.0f, 0.0f }, Point3p3c{ 3.0f, -1.0f, -0.5f, 0.8f, 0.0f, 0.0f },
            Point3p3c{ 3.0f, -2.0f, -0.5f, 0.75f, 0.0f, 0.0f }, Point3p3c{ 2.0f, -2.0f, -0.5f, 0.8f, 0.0f, 0.0f }
        };
        const GLuint DRAW_ELEMENTS_BV_ELEMENTS[ DRAW_ELEMENTS_BV_NUM_ELEMENTS ]{ 0, 1, 2, 3, 4, 5 };
        glBufferData( GL_ARRAY_BUFFER, DRAW_ELEMENTS_BV_NUM_POINTS * sizeof( Point3p3c ), DRAW_ELEMENTS_BV_POINTS.data(), GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), (void *)( 3 * sizeof( float ) ) );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( DRAW_ELEMENTS_BV_ELEMENTS ), DRAW_ELEMENTS_BV_ELEMENTS, GL_STATIC_DRAW );

        // glDrawElementsIndirect
        glCreateVertexArrays( 1, &drawElementsIndirectVao );
        glCreateBuffers( 1, &drawElementsIndirectVbo );
        glCreateBuffers( 1, &drawElementsIndirectEbo );
        glCreateBuffers( 1, &drawElementsIndirectDibo );
        glBindVertexArray( drawElementsIndirectVao );
        glBindBuffer( GL_ARRAY_BUFFER, drawElementsIndirectVbo );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, drawElementsIndirectEbo );
        glBindBuffer( GL_DRAW_INDIRECT_BUFFER, drawElementsIndirectDibo );
        const Point3p3c DRAW_ELEMENTS_INDIRECT_POINTS[]{ Point3p3c{ 2.0f, -4.0f, 0.0f, 0.6f, 0.0f, 0.0f },
                                                         Point3p3c{ 3.0f, -4.0f, 0.0f, 0.6f, 0.0f, 0.0f },
                                                         Point3p3c{ 3.0f, -3.0f, 0.0f, 0.6f, 0.0f, 0.0f },
                                                         Point3p3c{ 2.0f, -3.0f, 0.0f, 0.6f, 0.0f, 0.0f } };
        const GLuint    DRAW_ELEMENTS_INDIRECT_ELEMENTS[]{ 0, 1, 2, 2, 3, 0 };
        glBufferData( GL_ARRAY_BUFFER, sizeof( DRAW_ELEMENTS_INDIRECT_POINTS ), DRAW_ELEMENTS_INDIRECT_POINTS, GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), (void *)( 3 * sizeof( float ) ) );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( DRAW_ELEMENTS_INDIRECT_ELEMENTS ), DRAW_ELEMENTS_INDIRECT_ELEMENTS, GL_STATIC_DRAW );
        const DrawElementsIndirectCommand DRAW_ELEMENTS_INDIRECT_DATA[]{ DrawElementsIndirectCommand{ 6, 1, 0, 0, 0 } };
        glBufferData( GL_DRAW_INDIRECT_BUFFER, sizeof( DRAW_ELEMENTS_INDIRECT_DATA ), DRAW_ELEMENTS_INDIRECT_DATA, GL_STATIC_DRAW );

        // glDrawElementsInstanced + glDrawElementsInstancedBaseInstance
        glCreateVertexArrays( 1, &drawElementsInstancedVao );
        glCreateBuffers( 1, &drawElementsInstancedVbo );
        glCreateBuffers( 1, &drawElementsInstancedVboInstanced );
        glCreateBuffers( 1, &drawElementsInstancedEbo );
        glBindVertexArray( drawElementsInstancedVao );
        glBindBuffer( GL_ARRAY_BUFFER, drawElementsInstancedVbo );
        const Point3p3c DRAW_ELEMENTS_INSTANCED_POINTS[]{ Point3p3c{ 2.0f, -6.0f, 0.0f, 0.4f, 0.0f, 0.0f },
                                                          Point3p3c{ 3.0f, -6.0f, 0.0f, 0.4f, 0.0f, 0.0f },
                                                          Point3p3c{ 3.0f, -5.0f, 0.0f, 0.4f, 0.0f, 0.0f },
                                                          Point3p3c{ 2.0f, -5.0f, 0.0f, 0.4f, 0.0f, 0.0f } };
        const GLuint    DRAW_ELEMENTS_INSTANCED_ELEMENTS[ DRAW_ELEMENTS_NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0 };
        const float     DRAW_ELEMENTS_INSTANCED_Z_OFFSETS[ DRAW_ELEMENTS_INSTANCED_NUM_INSTANCES ]{ 0.0f, -0.5f, -1.0f, -1.5f };
        glBufferData( GL_ARRAY_BUFFER, sizeof( DRAW_ELEMENTS_INSTANCED_POINTS ), DRAW_ELEMENTS_INSTANCED_POINTS, GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), (void *)( 3 * sizeof( float ) ) );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, drawElementsInstancedEbo );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( DRAW_ELEMENTS_INSTANCED_ELEMENTS ), DRAW_ELEMENTS_INSTANCED_ELEMENTS,
                      GL_STATIC_DRAW );
        glBindBuffer( GL_ARRAY_BUFFER, drawElementsInstancedVboInstanced );
        glBufferData( GL_ARRAY_BUFFER, sizeof( DRAW_ELEMENTS_INSTANCED_Z_OFFSETS ), DRAW_ELEMENTS_INSTANCED_Z_OFFSETS, GL_STATIC_DRAW );
        glEnableVertexAttribArray( 2 );
        glVertexAttribPointer( 2, 1, GL_FLOAT, GL_FALSE, sizeof( GLfloat ), 0 );
        glVertexAttribDivisor( 2, 1 );

        // glDrawElementsInstancedBaseVertex + glDrawElementsInstancedBaseVertexBaseInstance
        glCreateVertexArrays( 1, &drawElementsInstancedBVVao );
        glCreateBuffers( 1, &drawElementsInstancedBVVbo );
        glCreateBuffers( 1, &drawElementsInstancedBVVboInstanced );
        glCreateBuffers( 1, &drawElementsInstancedBVEbo );
        glBindVertexArray( drawElementsInstancedBVVao );
        glBindBuffer( GL_ARRAY_BUFFER, drawElementsInstancedBVVbo );
        const Point3p3c DRAW_ELEMENTS_INSTANCED_BV_POINTS[]{
            Point3p3c{ 2.0f, -10.0f, 0.0f, 1.0f, 0.3f, 0.3f },   Point3p3c{ 3.0f, -10.0f, 0.0f, 1.0f, 0.3f, 0.3f },
            Point3p3c{ 3.0f, -9.0f, 0.0f, 1.0f, 0.3f, 0.3f },    Point3p3c{ 2.0f, -9.0f, 0.0f, 1.0f, 0.3f, 0.3f },
            Point3p3c{ 2.0f, -10.0f, -0.25f, 1.0f, 0.3f, 0.3f }, Point3p3c{ 3.0f, -10.0f, -0.25f, 1.0f, 0.3f, 0.3f }
        };
        const GLuint DRAW_ELEMENTS_INSTANCED_BV_ELEMENTS[ DRAW_ELEMENTS_INSTANCED_BV_NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0 };
        const float  DRAW_ELEMENTS_INSTANCED_BV_Z_OFFSETS[ DRAW_ELEMENTS_INSTANCED_BV_NUM_INSTANCES ]{ 0.0f, -0.5f, -1.0f };
        glBufferData( GL_ARRAY_BUFFER, sizeof( DRAW_ELEMENTS_INSTANCED_BV_POINTS ), DRAW_ELEMENTS_INSTANCED_BV_POINTS, GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), (void *)( 3 * sizeof( float ) ) );
        glBindBuffer( GL_ARRAY_BUFFER, drawElementsInstancedBVVboInstanced );
        glBufferData( GL_ARRAY_BUFFER, sizeof( DRAW_ELEMENTS_INSTANCED_BV_Z_OFFSETS ), DRAW_ELEMENTS_INSTANCED_BV_Z_OFFSETS,
                      GL_STATIC_DRAW );
        glEnableVertexAttribArray( 2 );
        glVertexAttribPointer( 2, 1, GL_FLOAT, GL_FALSE, sizeof( GLfloat ), 0 );
        glVertexAttribDivisor( 2, 1 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, drawElementsInstancedBVEbo );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( DRAW_ELEMENTS_INSTANCED_BV_ELEMENTS ), DRAW_ELEMENTS_INSTANCED_BV_ELEMENTS,
                      GL_STATIC_DRAW );
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

        // glDrawElementsBaseVertex
        if( drawElementsBVVao )
        {
            glDeleteVertexArrays( 1, &drawElementsBVVao );
        }
        if( drawElementsBVVbo )
        {
            glDeleteBuffers( 1, &drawElementsBVVbo );
        }
        if( drawElementsBVEbo )
        {
            glDeleteBuffers( 1, &drawElementsBVEbo );
        }

        // glDrawElementsIndirect
        if( drawElementsIndirectVao )
        {
            glDeleteVertexArrays( 1, &drawElementsIndirectVao );
        }
        if( drawElementsIndirectVbo )
        {
            glDeleteBuffers( 1, &drawElementsIndirectVbo );
        }
        if( drawElementsIndirectEbo )
        {
            glDeleteBuffers( 1, &drawElementsIndirectEbo );
        }
        if( drawElementsIndirectDibo )
        {
            glDeleteBuffers( 1, &drawElementsIndirectDibo );
        }

        // glDrawElementsInstanced + glDrawElementsInstancedBaseInstance
        if( drawElementsInstancedVao )
        {
            glDeleteVertexArrays( 1, &drawElementsInstancedVao );
        }
        if( drawElementsInstancedVbo )
        {
            glDeleteBuffers( 1, &drawElementsInstancedVbo );
        }
        if( drawElementsInstancedVboInstanced )
        {
            glDeleteBuffers( 1, &drawElementsInstancedVboInstanced );
        }
        if( drawElementsInstancedEbo )
        {
            glDeleteBuffers( 1, &drawElementsInstancedEbo );
        }

        // glDrawElementsInstancedBaseVertex + glDrawElementsInstancedBaseVertexBaseInstance
        if( drawElementsInstancedBVVao )
        {
            glDeleteVertexArrays( 1, &drawElementsInstancedBVVao );
        }
        if( drawElementsInstancedBVVbo )
        {
            glDeleteBuffers( 1, &drawElementsInstancedBVVbo );
        }
        if( drawElementsInstancedBVVboInstanced )
        {
            glDeleteBuffers( 1, &drawElementsInstancedBVVboInstanced );
        }
        if( drawElementsInstancedBVEbo )
        {
            glDeleteBuffers( 1, &drawElementsInstancedBVEbo );
        }

        // shader programs
        for( auto & shaderProgram: shaderPrograms.values() )
        {
            glDeleteProgram( shaderProgram->programId() );
        }
        shaderPrograms.clear();
    }

} // namespace Ouquitoure
