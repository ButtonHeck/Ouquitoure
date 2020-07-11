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
        , drawArr_Vao( 0 )
        , drawArr_Vbo( 0 )

        // glDrawArraysInstanced + glDrawArraysInstancedBaseInstance
        , drawArrInst_Vao( 0 )
        , drawArrInst_Vbo( 0 )
        , drawArrInst_VboInst( 0 )

        // glDrawArraysIndirect
        , drawArrInd_Vao( 0 )
        , drawArrInd_Vbo( 0 )
        , drawArrInd_VboInst( 0 )
        , drawArrInd_Dibo( 0 )

        // glDrawElements
        , drawElem_Vao( 0 )
        , drawElem_Vbo( 0 )
        , drawElem_Ebo( 0 )

        // glDrawElementsBaseVertex
        , drawElemBV_Vao( 0 )
        , drawElemBV_Vbo( 0 )
        , drawElemBV_Ebo( 0 )

        // glDrawElementsIndirect
        , drawElemInd_Vao( 0 )
        , drawElemInd_Vbo( 0 )
        , drawElemInd_Ebo( 0 )
        , drawElemInd_Dibo( 0 )

        // glDrawElementsInstanced + glDrawElementsInstancedBaseInstance
        , drawElemInst_Vao( 0 )
        , drawElemInst_Vbo( 0 )
        , drawElemInst_VboInst( 0 )
        , drawElemInst_Ebo( 0 )

        // glDrawElementsInstancedBaseVertex + glDrawElementsInstancedBaseVertexBaseInstance
        , drawElemInstBV_Vao( 0 )
        , drawElemInstBV_Vbo( 0 )
        , drawElemInstBV_VboInst( 0 )
        , drawElemInstBV_Ebo( 0 )
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
        glBindVertexArray( drawArr_Vao );
        glDrawArrays( GL_TRIANGLES, 0, DRAW_ARR_NUM_POINTS );
        glDrawArrays( GL_POINTS, 0, DRAW_ARR_NUM_POINTS );

        // glDrawArraysInstanced + glDrawArraysInstancedBaseInstance
        glBindVertexArray( drawArrInst_Vao );
        glDrawArraysInstanced( GL_TRIANGLES, 0, DRAW_ARR_INST_NUM_POINTS, DRAW_ARR_INST_NUM_INSTANCES );
        glDrawArraysInstanced( GL_POINTS, 0, DRAW_ARR_INST_NUM_POINTS, DRAW_ARR_INST_NUM_INSTANCES );
        glLineWidth( 3.0f );
        glDrawArraysInstancedBaseInstance( GL_TRIANGLES, 0, DRAW_ARR_INST_NUM_POINTS, DRAW_ARR_INST_NUM_INSTANCES, 1 );
        glLineWidth( 1.0f );

        // glDrawArraysIndirect
        glBindVertexArray( drawArrInd_Vao );
        glBindBuffer( GL_DRAW_INDIRECT_BUFFER, drawArrInd_Dibo );
        glDrawArraysIndirect( GL_TRIANGLES, nullptr );
        glDrawArraysIndirect( GL_POINTS, nullptr );

        // glDrawElements
        glBindVertexArray( drawElem_Vao );
        glDrawElements( GL_TRIANGLES, DRAW_ELEM_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr );
        glDrawElements( GL_POINTS, DRAW_ELEM_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr );

        // glDrawElementsBaseVertex
        glBindVertexArray( drawElemBV_Vao );
        glDrawElementsBaseVertex( GL_TRIANGLES, DRAW_ELEM_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr, 2 );
        glDrawElementsBaseVertex( GL_POINTS, DRAW_ELEM_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr, 2 );

        // glDrawElementsIndirect
        glBindVertexArray( drawElemInd_Vao );
        glBindBuffer( GL_DRAW_INDIRECT_BUFFER, drawElemInd_Dibo );
        glDrawElementsIndirect( GL_TRIANGLES, GL_UNSIGNED_INT, nullptr );
        glDrawElementsIndirect( GL_POINTS, GL_UNSIGNED_INT, nullptr );

        // glDrawElementsInstanced + glDrawElementsInstancedBaseInstance
        glBindVertexArray( drawElemInst_Vao );
        glDrawElementsInstanced( GL_TRIANGLES, DRAW_ELEM_INST_NUM_ELEMENTS, GL_UNSIGNED_INT, 0, DRAW_ELEM_INST_NUM_INSTANCES );
        glDrawElementsInstanced( GL_POINTS, DRAW_ELEM_INST_NUM_ELEMENTS, GL_UNSIGNED_INT, 0, DRAW_ELEM_INST_NUM_INSTANCES );
        glLineWidth( 3.0f );
        glDrawElementsInstancedBaseInstance( GL_TRIANGLES, DRAW_ELEM_INST_NUM_ELEMENTS, GL_UNSIGNED_INT, 0, DRAW_ELEM_INST_NUM_INSTANCES,
                                             1 );
        glLineWidth( 1.0f );

        // glDrawElementsInstancedBaseVertex + glDrawElementsInstancedBaseVertexBaseInstance
        glBindVertexArray( drawElemInstBV_Vao );
        glDrawElementsInstancedBaseVertex( GL_TRIANGLES, DRAW_ELEM_INST_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, 0,
                                           DRAW_ELEM_INST_BV_NUM_INSTANCES, 1 );
        glDrawElementsInstancedBaseVertex( GL_POINTS, DRAW_ELEM_INST_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, 0, DRAW_ELEM_INST_BV_NUM_INSTANCES,
                                           1 );
        glLineWidth( 3.0f );
        glDrawElementsInstancedBaseVertexBaseInstance( GL_TRIANGLES, DRAW_ELEM_INST_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, 0,
                                                       DRAW_ELEM_INST_BV_NUM_INSTANCES, 1, 1 );
        glDrawElementsInstancedBaseVertexBaseInstance( GL_POINTS, DRAW_ELEM_INST_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, 0,
                                                       DRAW_ELEM_INST_BV_NUM_INSTANCES, 1, 1 );
        glLineWidth( 1.0f );
    }

    void OpenGLDrawFunctionsWidget::initializeOpenGLObjects()
    {
        // glDrawArrays
        glCreateBuffers( 1, &drawArr_Vbo );
        glCreateVertexArrays( 1, &drawArr_Vao );
        glBindVertexArray( drawArr_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, drawArr_Vbo );
        const std::array<Point3p3c, DRAW_ARR_NUM_POINTS> DRAW_ARRAYS_POINTS{ Point3p3c{ 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
                                                                             Point3p3c{ 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
                                                                             Point3p3c{ 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f } };
        glBufferData( GL_ARRAY_BUFFER, DRAW_ARR_NUM_POINTS * sizeof( Point3p3c ), DRAW_ARRAYS_POINTS.data(), GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), (void *)( 3 * sizeof( float ) ) );

        // glDrawArraysInstanced
        glCreateBuffers( 1, &drawArrInst_Vbo );
        glCreateBuffers( 1, &drawArrInst_VboInst );
        glCreateVertexArrays( 1, &drawArrInst_Vao );
        glBindVertexArray( drawArrInst_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, drawArrInst_Vbo );
        const std::array<Point3p3c, DRAW_ARR_INST_NUM_POINTS> DRAW_ARRAYS_INSTANCED_POINTS{
            Point3p3c{ 0.0f, -2.0f, 0.0f, 0.75f, 0.75f, 0.75f }, Point3p3c{ 1.0f, -2.0f, 0.0f, 0.75f, 0.75f, 0.75f },
            Point3p3c{ 1.0f, -1.0f, 0.0f, 0.75f, 0.75f, 0.75f }
        };
        glBufferData( GL_ARRAY_BUFFER, sizeof( DRAW_ARRAYS_INSTANCED_POINTS ), DRAW_ARRAYS_INSTANCED_POINTS.data(), GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), (void *)( 3 * sizeof( float ) ) );
        glBindBuffer( GL_ARRAY_BUFFER, drawArrInst_VboInst );
        const float DRAW_ARRAYS_INSTANCED_Z_OFFSETS[ DRAW_ARR_INST_NUM_INSTANCES ]{ 0.0f, -0.5f, -1.0f, -1.5f };
        glBufferData( GL_ARRAY_BUFFER, sizeof( DRAW_ARRAYS_INSTANCED_Z_OFFSETS ), DRAW_ARRAYS_INSTANCED_Z_OFFSETS, GL_STATIC_DRAW );
        glEnableVertexAttribArray( 2 );
        glVertexAttribPointer( 2, 1, GL_FLOAT, GL_FALSE, sizeof( GLfloat ), 0 );
        glVertexAttribDivisor( 2, 1 );

        // glDrawArraysIndirect
        glCreateBuffers( 1, &drawArrInd_Vbo );
        glCreateBuffers( 1, &drawArrInd_Dibo );
        glCreateBuffers( 1, &drawArrInd_VboInst );
        glCreateVertexArrays( 1, &drawArrInd_Vao );
        glBindVertexArray( drawArrInd_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, drawArrInd_Vbo );
        const Point3p3c DRAW_ARRAYS_INDIRECT_POINTS[ DRAW_ARR_IND_NUM_POINTS ]{ Point3p3c{ 0.0f, -5.0f, 0.0f, 0.5f, 0.5f, 0.5f },
                                                                                Point3p3c{ 1.0f, -5.0f, 0.0f, 0.5f, 0.5f, 0.5f },
                                                                                Point3p3c{ 0.5f, -4.0f, 0.0f, 0.5f, 0.5f, 0.5f } };
        glBufferData( GL_ARRAY_BUFFER, sizeof( DRAW_ARRAYS_INDIRECT_POINTS ), DRAW_ARRAYS_INDIRECT_POINTS, GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), (void *)( 3 * sizeof( float ) ) );
        glBindBuffer( GL_DRAW_INDIRECT_BUFFER, drawArrInd_Dibo );
        const DrawArraysIndirectCommand DRAW_INDIRECT_DATA{ 3, DRAW_ARR_IND_NUM_INSTANCES, 0, 0 };
        glBufferData( GL_DRAW_INDIRECT_BUFFER, sizeof( DRAW_INDIRECT_DATA ), &DRAW_INDIRECT_DATA, GL_STATIC_DRAW );
        glBindBuffer( GL_ARRAY_BUFFER, drawArrInd_VboInst );
        const float DRAW_ARRAYS_INDIRECT_Z_OFFSETS[ DRAW_ARR_IND_NUM_INSTANCES ]{ 0.0f, -0.5f };
        glBufferData( GL_ARRAY_BUFFER, sizeof( DRAW_ARRAYS_INDIRECT_Z_OFFSETS ), DRAW_ARRAYS_INDIRECT_Z_OFFSETS, GL_STATIC_DRAW );
        glEnableVertexAttribArray( 2 );
        glVertexAttribPointer( 2, 1, GL_FLOAT, GL_FALSE, sizeof( GLfloat ), 0 );
        glVertexAttribDivisor( 2, 1 );

        // glDrawElements
        glCreateBuffers( 1, &drawElem_Vbo );
        glCreateBuffers( 1, &drawElem_Ebo );
        glCreateVertexArrays( 1, &drawElem_Vao );
        glBindVertexArray( drawElem_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, drawElem_Vbo );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, drawElem_Ebo );
        const std::array<Point3p3c, DRAW_ELEM_NUM_POINTS> DRAW_ELEMENTS_POINTS{ Point3p3c{ 2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
                                                                                Point3p3c{ 3.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
                                                                                Point3p3c{ 3.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f },
                                                                                Point3p3c{ 2.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f } };
        const GLuint                                      DRAW_ELEMENTS_ELEMENTS[ DRAW_ELEM_NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0 };
        glBufferData( GL_ARRAY_BUFFER, DRAW_ELEM_NUM_POINTS * sizeof( Point3p3c ), DRAW_ELEMENTS_POINTS.data(), GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), (void *)( 3 * sizeof( float ) ) );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( DRAW_ELEMENTS_ELEMENTS ), DRAW_ELEMENTS_ELEMENTS, GL_STATIC_DRAW );

        // glDrawElementsBaseVertex
        glCreateBuffers( 1, &drawElemBV_Ebo );
        glCreateBuffers( 1, &drawElemBV_Vbo );
        glCreateVertexArrays( 1, &drawElemBV_Vao );
        glBindVertexArray( drawElemBV_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, drawElemBV_Vbo );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, drawElemBV_Ebo );
        const std::array<Point3p3c, DRAW_ELEM_BV_NUM_POINTS> DRAW_ELEMENTS_BV_POINTS{
            Point3p3c{ 2.0f, -1.0f, 0.0f, 0.75f, 0.0f, 0.0f },  Point3p3c{ 3.0f, -1.0f, 0.0f, 0.8f, 0.0f, 0.0f },
            Point3p3c{ 3.0f, -2.0f, 0.0f, 0.75f, 0.0f, 0.0f },  Point3p3c{ 2.0f, -2.0f, 0.0f, 0.8f, 0.0f, 0.0f },
            Point3p3c{ 2.0f, -1.0f, -0.5f, 0.75f, 0.0f, 0.0f }, Point3p3c{ 3.0f, -1.0f, -0.5f, 0.8f, 0.0f, 0.0f },
            Point3p3c{ 3.0f, -2.0f, -0.5f, 0.75f, 0.0f, 0.0f }, Point3p3c{ 2.0f, -2.0f, -0.5f, 0.8f, 0.0f, 0.0f }
        };
        const GLuint DRAW_ELEMENTS_BV_ELEMENTS[ DRAW_ELEM_BV_NUM_ELEMENTS ]{ 0, 1, 2, 3, 4, 5 };
        glBufferData( GL_ARRAY_BUFFER, DRAW_ELEM_BV_NUM_POINTS * sizeof( Point3p3c ), DRAW_ELEMENTS_BV_POINTS.data(), GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), (void *)( 3 * sizeof( float ) ) );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( DRAW_ELEMENTS_BV_ELEMENTS ), DRAW_ELEMENTS_BV_ELEMENTS, GL_STATIC_DRAW );

        // glDrawElementsIndirect
        glCreateVertexArrays( 1, &drawElemInd_Vao );
        glCreateBuffers( 1, &drawElemInd_Vbo );
        glCreateBuffers( 1, &drawElemInd_Ebo );
        glCreateBuffers( 1, &drawElemInd_Dibo );
        glBindVertexArray( drawElemInd_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, drawElemInd_Vbo );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, drawElemInd_Ebo );
        glBindBuffer( GL_DRAW_INDIRECT_BUFFER, drawElemInd_Dibo );
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
        glCreateVertexArrays( 1, &drawElemInst_Vao );
        glCreateBuffers( 1, &drawElemInst_Vbo );
        glCreateBuffers( 1, &drawElemInst_VboInst );
        glCreateBuffers( 1, &drawElemInst_Ebo );
        glBindVertexArray( drawElemInst_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, drawElemInst_Vbo );
        const Point3p3c DRAW_ELEMENTS_INSTANCED_POINTS[]{ Point3p3c{ 2.0f, -6.0f, 0.0f, 0.4f, 0.0f, 0.0f },
                                                          Point3p3c{ 3.0f, -6.0f, 0.0f, 0.4f, 0.0f, 0.0f },
                                                          Point3p3c{ 3.0f, -5.0f, 0.0f, 0.4f, 0.0f, 0.0f },
                                                          Point3p3c{ 2.0f, -5.0f, 0.0f, 0.4f, 0.0f, 0.0f } };
        const GLuint    DRAW_ELEMENTS_INSTANCED_ELEMENTS[ DRAW_ELEM_NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0 };
        const float     DRAW_ELEMENTS_INSTANCED_Z_OFFSETS[ DRAW_ELEM_INST_NUM_INSTANCES ]{ 0.0f, -0.5f, -1.0f, -1.5f };
        glBufferData( GL_ARRAY_BUFFER, sizeof( DRAW_ELEMENTS_INSTANCED_POINTS ), DRAW_ELEMENTS_INSTANCED_POINTS, GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), (void *)( 3 * sizeof( float ) ) );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, drawElemInst_Ebo );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( DRAW_ELEMENTS_INSTANCED_ELEMENTS ), DRAW_ELEMENTS_INSTANCED_ELEMENTS,
                      GL_STATIC_DRAW );
        glBindBuffer( GL_ARRAY_BUFFER, drawElemInst_VboInst );
        glBufferData( GL_ARRAY_BUFFER, sizeof( DRAW_ELEMENTS_INSTANCED_Z_OFFSETS ), DRAW_ELEMENTS_INSTANCED_Z_OFFSETS, GL_STATIC_DRAW );
        glEnableVertexAttribArray( 2 );
        glVertexAttribPointer( 2, 1, GL_FLOAT, GL_FALSE, sizeof( GLfloat ), 0 );
        glVertexAttribDivisor( 2, 1 );

        // glDrawElementsInstancedBaseVertex + glDrawElementsInstancedBaseVertexBaseInstance
        glCreateVertexArrays( 1, &drawElemInstBV_Vao );
        glCreateBuffers( 1, &drawElemInstBV_Vbo );
        glCreateBuffers( 1, &drawElemInstBV_VboInst );
        glCreateBuffers( 1, &drawElemInstBV_Ebo );
        glBindVertexArray( drawElemInstBV_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, drawElemInstBV_Vbo );
        const Point3p3c DRAW_ELEMENTS_INSTANCED_BV_POINTS[]{
            Point3p3c{ 2.0f, -10.0f, 0.0f, 1.0f, 0.3f, 0.3f },   Point3p3c{ 3.0f, -10.0f, 0.0f, 1.0f, 0.3f, 0.3f },
            Point3p3c{ 3.0f, -9.0f, 0.0f, 1.0f, 0.3f, 0.3f },    Point3p3c{ 2.0f, -9.0f, 0.0f, 1.0f, 0.3f, 0.3f },
            Point3p3c{ 2.0f, -10.0f, -0.25f, 1.0f, 0.3f, 0.3f }, Point3p3c{ 3.0f, -10.0f, -0.25f, 1.0f, 0.3f, 0.3f }
        };
        const GLuint DRAW_ELEMENTS_INSTANCED_BV_ELEMENTS[ DRAW_ELEM_INST_BV_NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0 };
        const float  DRAW_ELEMENTS_INSTANCED_BV_Z_OFFSETS[ DRAW_ELEM_INST_BV_NUM_INSTANCES ]{ 0.0f, -0.5f, -1.0f };
        glBufferData( GL_ARRAY_BUFFER, sizeof( DRAW_ELEMENTS_INSTANCED_BV_POINTS ), DRAW_ELEMENTS_INSTANCED_BV_POINTS, GL_STATIC_DRAW );
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), (void *)( 3 * sizeof( float ) ) );
        glBindBuffer( GL_ARRAY_BUFFER, drawElemInstBV_VboInst );
        glBufferData( GL_ARRAY_BUFFER, sizeof( DRAW_ELEMENTS_INSTANCED_BV_Z_OFFSETS ), DRAW_ELEMENTS_INSTANCED_BV_Z_OFFSETS,
                      GL_STATIC_DRAW );
        glEnableVertexAttribArray( 2 );
        glVertexAttribPointer( 2, 1, GL_FLOAT, GL_FALSE, sizeof( GLfloat ), 0 );
        glVertexAttribDivisor( 2, 1 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, drawElemInstBV_Ebo );
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
        if( drawArr_Vao )
        {
            glDeleteVertexArrays( 1, &drawArr_Vao );
        }
        if( drawArr_Vbo )
        {
            glDeleteBuffers( 1, &drawArr_Vbo );
        }

        // glDrawArraysInstanced
        if( drawArrInst_Vao )
        {
            glDeleteVertexArrays( 1, &drawArrInst_Vao );
        }
        if( drawArrInst_Vbo )
        {
            glDeleteBuffers( 1, &drawArrInst_Vbo );
        }
        if( drawArrInst_VboInst )
        {
            glDeleteBuffers( 1, &drawArrInst_VboInst );
        }

        // glDrawArraysIndirect
        if( drawArrInd_Vao )
        {
            glDeleteVertexArrays( 1, &drawArrInd_Vao );
        }
        if( drawArrInd_Vbo )
        {
            glDeleteBuffers( 1, &drawArrInd_Vbo );
        }
        if( drawArrInd_VboInst )
        {
            glDeleteBuffers( 1, &drawArrInd_VboInst );
        }
        if( drawArrInd_Dibo )
        {
            glDeleteBuffers( 1, &drawArrInd_Dibo );
        }

        // glDrawElements
        if( drawElem_Vao )
        {
            glDeleteVertexArrays( 1, &drawElem_Vao );
        }
        if( drawElem_Ebo )
        {
            glDeleteBuffers( 1, &drawElem_Ebo );
        }
        if( drawElem_Vbo )
        {
            glDeleteBuffers( 1, &drawElem_Vbo );
        }

        // glDrawElementsBaseVertex
        if( drawElemBV_Vao )
        {
            glDeleteVertexArrays( 1, &drawElemBV_Vao );
        }
        if( drawElemBV_Vbo )
        {
            glDeleteBuffers( 1, &drawElemBV_Vbo );
        }
        if( drawElemBV_Ebo )
        {
            glDeleteBuffers( 1, &drawElemBV_Ebo );
        }

        // glDrawElementsIndirect
        if( drawElemInd_Vao )
        {
            glDeleteVertexArrays( 1, &drawElemInd_Vao );
        }
        if( drawElemInd_Vbo )
        {
            glDeleteBuffers( 1, &drawElemInd_Vbo );
        }
        if( drawElemInd_Ebo )
        {
            glDeleteBuffers( 1, &drawElemInd_Ebo );
        }
        if( drawElemInd_Dibo )
        {
            glDeleteBuffers( 1, &drawElemInd_Dibo );
        }

        // glDrawElementsInstanced + glDrawElementsInstancedBaseInstance
        if( drawElemInst_Vao )
        {
            glDeleteVertexArrays( 1, &drawElemInst_Vao );
        }
        if( drawElemInst_Vbo )
        {
            glDeleteBuffers( 1, &drawElemInst_Vbo );
        }
        if( drawElemInst_VboInst )
        {
            glDeleteBuffers( 1, &drawElemInst_VboInst );
        }
        if( drawElemInst_Ebo )
        {
            glDeleteBuffers( 1, &drawElemInst_Ebo );
        }

        // glDrawElementsInstancedBaseVertex + glDrawElementsInstancedBaseVertexBaseInstance
        if( drawElemInstBV_Vao )
        {
            glDeleteVertexArrays( 1, &drawElemInstBV_Vao );
        }
        if( drawElemInstBV_Vbo )
        {
            glDeleteBuffers( 1, &drawElemInstBV_Vbo );
        }
        if( drawElemInstBV_VboInst )
        {
            glDeleteBuffers( 1, &drawElemInstBV_VboInst );
        }
        if( drawElemInstBV_Ebo )
        {
            glDeleteBuffers( 1, &drawElemInstBV_Ebo );
        }

        // shader programs
        for( auto & shaderProgram: shaderPrograms.values() )
        {
            glDeleteProgram( shaderProgram->programId() );
        }
        shaderPrograms.clear();
    }

} // namespace Ouquitoure
