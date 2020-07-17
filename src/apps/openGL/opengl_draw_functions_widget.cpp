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

        // glDrawRangeElements
        , drawRangeElem_Vao( 0 )
        , drawRangeElem_Vbo( 0 )
        , drawRangeElem_Ebo( 0 )

        // glDrawRangeElementsBaseVertex
        , drawRangeElemBV_Vao( 0 )
        , drawRangeElemBV_Vbo( 0 )
        , drawRangeElemBV_Ebo( 0 )

        // glMultiDrawArrays
        , mDrawArr_Vao( 0 )
        , mDrawArr_Vbo( 0 )

        // glMultiDrawArraysIndirect
        , mDrawArrInd_Vao( 0 )
        , mDrawArrInd_Vbo( 0 )
        , mDrawArrInd_Dibo( 0 )

        // glMultiDrawElements
        , mDrawElem_Vao( 0 )
        , mDrawElem_Vbo( 0 )
        , mDrawElem_Ebo( 0 )

        // glMultiDrawElementsBaseVertex
        , mDrawElemBV_Vao( 0 )
        , mDrawElemBV_Vbo( 0 )
        , mDrawElemBV_Ebo( 0 )

        // glMultiDrawElementsIndirect
        , mDrawElemInd_Vao( 0 )
        , mDrawElemInd_Vbo( 0 )
        , mDrawElemInd_Ebo( 0 )
        , mDrawElemInd_Dibo( 0 )
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
        drawArrays();

        // glDrawArraysInstanced + glDrawArraysInstancedBaseInstance
        drawArraysInstanced();

        // glDrawArraysIndirect
        drawArraysIndirect();

        // glDrawElements
        drawElements();

        // glDrawElementsBaseVertex
        drawElementsBaseVertex();

        // glDrawElementsIndirect
        drawElementsIndirect();

        // glDrawElementsInstanced + glDrawElementsInstancedBaseInstance
        drawElementsInstanced();

        // glDrawElementsInstancedBaseVertex + glDrawElementsInstancedBaseVertexBaseInstance
        drawElementsInstancedBaseVertex();

        // glDrawRangeElements
        drawRangeElements();

        // glDrawRangeElementsBaseVertex
        drawRangeElementsBaseVertex();

        // glMultiDrawArrays
        multiDrawArrays();

        // glMultiDrawArraysIndirect
        multiDrawArraysIndirect();

        // glMultiDrawElements
        multiDrawElements();

        // glMultiDrawElementsBaseVertex
        multiDrawElementsBaseVertex();

        // glMultiDrawElementsIndirect
        multiDrawElementsIndirect();
    }

    void OpenGLDrawFunctionsWidget::initializeOpenGLObjects()
    {
        // glDrawArrays
        drawArrays_init();

        // glDrawArraysInstanced + glDrawArraysInstancedBaseInstance
        drawArraysInstanced_init();

        // glDrawArraysIndirect
        drawArraysIndirect_init();

        // glDrawElements
        drawElements_init();

        // glDrawElementsBaseVertex
        drawElementsBaseVertex_init();

        // glDrawElementsIndirect
        drawElementsIndirect_init();

        // glDrawElementsInstanced + glDrawElementsInstancedBaseInstance
        drawElementsInstanced_init();

        // glDrawElementsInstancedBaseVertex + glDrawElementsInstancedBaseVertexBaseInstance
        drawElementsInstancedBaseVertex_init();

        // glDrawRangeElements
        drawRangeElements_init();

        // glDrawRangeElementsBaseVertex
        drawRangeElementsBaseVertex_init();

        // glMultiDrawArrays
        multiDrawArrays_init();

        // glMultiDrawArraysIndirect
        multiDrawArraysIndirect_init();

        // glMultiDrawElements
        multiDrawElements_init();

        // glMultiDrawElementsBaseVertex
        multiDrawElementsBaseVertex_init();

        // glMultiDrawElementsIndirect
        multiDrawElementsIndirect_init();
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
        drawArrays_cleanup();

        // glDrawArraysInstanced + glDrawArraysInstancedBaseInstance
        drawArraysInstanced_cleanup();

        // glDrawArraysIndirect
        drawArraysIndirect_cleanup();

        // glDrawElements
        drawElements_cleanup();

        // glDrawElementsBaseVertex
        drawElementsBaseVertex_cleanup();

        // glDrawElementsIndirect
        drawElementsIndirect_cleanup();

        // glDrawElementsInstanced + glDrawElementsInstancedBaseInstance
        drawElementsInstanced_cleanup();

        // glDrawElementsInstancedBaseVertex + glDrawElementsInstancedBaseVertexBaseInstance
        drawElementsInstancedBaseVertex_cleanup();

        // glDrawRangeElements
        drawRangeElements_cleanup();

        // glDrawRangeElementsBaseVertex
        drawRangeElementsBaseVertex_cleanup();

        // glMultiDrawArrays
        multiDrawArrays_cleanup();

        // glMultiDrawArraysIndirect
        multiDrawArraysIndirect_cleanup();

        // glMultiDrawElements
        multiDrawElements_cleanup();

        // glMultiDrawElementsBaseVertex
        multiDrawElementsBaseVertex_cleanup();

        // glMultiDrawElementsIndirect
        multiDrawElementsIndirect_cleanup();

        // shader programs
        for( auto & shaderProgram: shaderPrograms.values() )
        {
            glDeleteProgram( shaderProgram->programId() );
        }
        shaderPrograms.clear();
    }

    //-------- drawing -------------

    void OpenGLDrawFunctionsWidget::drawArrays()
    {
        glBindVertexArray( drawArr_Vao );
        glDrawArrays( GL_TRIANGLES, 0, DRAW_ARR_NUM_POINTS );
        glDrawArrays( GL_POINTS, 0, DRAW_ARR_NUM_POINTS );
    }

    void OpenGLDrawFunctionsWidget::drawArraysInstanced()
    {
        glBindVertexArray( drawArrInst_Vao );
        glDrawArraysInstanced( GL_TRIANGLES, 0, DRAW_ARR_INST_NUM_POINTS, DRAW_ARR_INST_NUM_INSTANCES );
        glDrawArraysInstanced( GL_POINTS, 0, DRAW_ARR_INST_NUM_POINTS, DRAW_ARR_INST_NUM_INSTANCES );
        glLineWidth( 3.0f );
        glDrawArraysInstancedBaseInstance( GL_TRIANGLES, 0, DRAW_ARR_INST_NUM_POINTS, DRAW_ARR_INST_NUM_INSTANCES, 1 );
        glLineWidth( 1.0f );
    }

    void OpenGLDrawFunctionsWidget::drawArraysIndirect()
    {
        glBindVertexArray( drawArrInd_Vao );
        glBindBuffer( GL_DRAW_INDIRECT_BUFFER, drawArrInd_Dibo );
        glDrawArraysIndirect( GL_TRIANGLES, nullptr );
        glDrawArraysIndirect( GL_POINTS, nullptr );
    }

    void OpenGLDrawFunctionsWidget::drawElements()
    {
        glBindVertexArray( drawElem_Vao );
        glDrawElements( GL_TRIANGLES, DRAW_ELEM_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr );
        glDrawElements( GL_POINTS, DRAW_ELEM_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr );
    }

    void OpenGLDrawFunctionsWidget::drawElementsBaseVertex()
    {
        glBindVertexArray( drawElemBV_Vao );
        glDrawElementsBaseVertex( GL_TRIANGLES, DRAW_ELEM_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr, 2 );
        glDrawElementsBaseVertex( GL_POINTS, DRAW_ELEM_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr, 2 );
    }

    void OpenGLDrawFunctionsWidget::drawElementsIndirect()
    {
        glBindVertexArray( drawElemInd_Vao );
        glBindBuffer( GL_DRAW_INDIRECT_BUFFER, drawElemInd_Dibo );
        glDrawElementsIndirect( GL_TRIANGLES, GL_UNSIGNED_INT, nullptr );
        glDrawElementsIndirect( GL_POINTS, GL_UNSIGNED_INT, nullptr );
    }

    void OpenGLDrawFunctionsWidget::drawElementsInstanced()
    {
        glBindVertexArray( drawElemInst_Vao );
        glDrawElementsInstanced( GL_TRIANGLES, DRAW_ELEM_INST_NUM_ELEMENTS, GL_UNSIGNED_INT, 0, DRAW_ELEM_INST_NUM_INSTANCES );
        glDrawElementsInstanced( GL_POINTS, DRAW_ELEM_INST_NUM_ELEMENTS, GL_UNSIGNED_INT, 0, DRAW_ELEM_INST_NUM_INSTANCES );
        glLineWidth( 3.0f );
        glDrawElementsInstancedBaseInstance( GL_TRIANGLES, DRAW_ELEM_INST_NUM_ELEMENTS, GL_UNSIGNED_INT, 0, DRAW_ELEM_INST_NUM_INSTANCES,
                                             1 );
        glLineWidth( 1.0f );
    }

    void OpenGLDrawFunctionsWidget::drawElementsInstancedBaseVertex()
    {
        glBindVertexArray( drawElemInstBV_Vao );
        glDrawElementsInstancedBaseVertex( GL_TRIANGLES, DRAW_ELEM_INST_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, 0,
                                           DRAW_ELEM_INST_BV_NUM_INSTANCES, 1 );
        glDrawElementsInstancedBaseVertex( GL_POINTS, DRAW_ELEM_INST_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, 0, DRAW_ELEM_INST_BV_NUM_INSTANCES,
                                           1 );
        glLineWidth( 3.0f );
        glDrawElementsInstancedBaseVertexBaseInstance( GL_TRIANGLES, DRAW_ELEM_INST_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, 0,
                                                       DRAW_ELEM_INST_BV_NUM_INSTANCES, 1, 1 );
        glLineWidth( 1.0f );
    }

    void OpenGLDrawFunctionsWidget::drawRangeElements()
    {
        glBindVertexArray( drawRangeElem_Vao );
        glDrawRangeElements( GL_TRIANGLES, 3, 6, DRAW_RANGE_ELEM_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr );
        glDrawRangeElements( GL_POINTS, 0, 3, DRAW_RANGE_ELEM_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr );
    }

    void OpenGLDrawFunctionsWidget::drawRangeElementsBaseVertex()
    {
        glBindVertexArray( drawRangeElemBV_Vao );
        glDrawRangeElementsBaseVertex( GL_TRIANGLES, 0, 6, DRAW_RANGE_ELEM_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr, 1 );
        glDrawRangeElementsBaseVertex( GL_POINTS, 0, 6, DRAW_RANGE_ELEM_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr, 1 );
    }

    void OpenGLDrawFunctionsWidget::multiDrawArrays()
    {
        glBindVertexArray( mDrawArr_Vao );
        const GLint   FIRSTS[]{ 0, 3 };
        const GLsizei COUNTS[]{ 3, 3 };
        glMultiDrawArrays( GL_TRIANGLES, FIRSTS, COUNTS, 2 );
        glMultiDrawArrays( GL_POINTS, FIRSTS, COUNTS, 2 );
    }

    void OpenGLDrawFunctionsWidget::multiDrawArraysIndirect()
    {
        glBindVertexArray( mDrawArrInd_Vao );
        glBindBuffer( GL_DRAW_INDIRECT_BUFFER, mDrawArrInd_Dibo );
        glMultiDrawArraysIndirect( GL_TRIANGLES, nullptr, M_DRAW_ARR_IND_NUM_COMMANDS, sizeof( DrawArraysIndirectCommand ) );
        glMultiDrawArraysIndirect( GL_POINTS, nullptr, M_DRAW_ARR_IND_NUM_COMMANDS, sizeof( DrawArraysIndirectCommand ) );
    }

    void OpenGLDrawFunctionsWidget::multiDrawElements()
    {
        glBindVertexArray( mDrawElem_Vao );
        const GLsizei COUNTS[]{ 6, 3 };
        const GLuint  INDICES[][ 2 ]{ { 0 }, { 6 * sizeof( GLuint ) } };
        glMultiDrawElements( GL_TRIANGLES, COUNTS, GL_UNSIGNED_INT, (const GLvoid **)INDICES, 2 );
        glMultiDrawElements( GL_POINTS, COUNTS, GL_UNSIGNED_INT, (const GLvoid **)INDICES, 2 );
    }

    void OpenGLDrawFunctionsWidget::multiDrawElementsBaseVertex()
    {
        glBindVertexArray( mDrawElemBV_Vao );
        const GLsizei COUNTS[]{ 6, 3 };
        const GLuint  INDICES[][ 2 ]{ { 0 }, { 6 * sizeof( GLuint ) } };
        const GLint   BASE_VERTICES[]{ 2, 1 };
        glMultiDrawElementsBaseVertex( GL_TRIANGLES, COUNTS, GL_UNSIGNED_INT, (const GLvoid **)INDICES, 2, BASE_VERTICES );
        glMultiDrawElementsBaseVertex( GL_POINTS, COUNTS, GL_UNSIGNED_INT, (const GLvoid **)INDICES, 2, BASE_VERTICES );
    }

    void OpenGLDrawFunctionsWidget::multiDrawElementsIndirect()
    {
        glBindVertexArray( mDrawElemInd_Vao );
        glBindBuffer( GL_DRAW_INDIRECT_BUFFER, mDrawElemInd_Dibo );
        glMultiDrawElementsIndirect( GL_TRIANGLES, GL_UNSIGNED_INT, nullptr, 2, 0 );
        glMultiDrawElementsIndirect( GL_POINTS, GL_UNSIGNED_INT, nullptr, 2, 0 );
    }

    //------- initialization --------------

    void OpenGLDrawFunctionsWidget::drawArrays_init()
    {
        glCreateVertexArrays( 1, &drawArr_Vao );
        glCreateBuffers( 1, &drawArr_Vbo );
        glBindVertexArray( drawArr_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, drawArr_Vbo );
        const Point3p3c POINTS[]{ Point3p3c{ 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f }, Point3p3c{ 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
                                  Point3p3c{ 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f } };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
    }

    void OpenGLDrawFunctionsWidget::drawArraysInstanced_init()
    {
        glCreateVertexArrays( 1, &drawArrInst_Vao );
        glCreateBuffers( 1, &drawArrInst_Vbo );
        glCreateBuffers( 1, &drawArrInst_VboInst );
        glBindVertexArray( drawArrInst_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, drawArrInst_Vbo );
        const Point3p3c POINTS[]{ Point3p3c{ 0.0f, -2.0f, 0.0f, 0.75f, 0.75f, 0.75f }, Point3p3c{ 1.0f, -2.0f, 0.0f, 0.75f, 0.75f, 0.75f },
                                  Point3p3c{ 1.0f, -1.0f, 0.0f, 0.75f, 0.75f, 0.75f } };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        glBindBuffer( GL_ARRAY_BUFFER, drawArrInst_VboInst );
        const float Z_OFFSETS[ DRAW_ARR_INST_NUM_INSTANCES ]{ 0.0f, -0.5f, -1.0f, -1.5f };
        glBufferData( GL_ARRAY_BUFFER, sizeof( Z_OFFSETS ), Z_OFFSETS, GL_STATIC_DRAW );
        setupVertexArrayInstancedAttribs();
    }

    void OpenGLDrawFunctionsWidget::drawArraysIndirect_init()
    {
        glCreateVertexArrays( 1, &drawArrInd_Vao );
        glCreateBuffers( 1, &drawArrInd_Vbo );
        glCreateBuffers( 1, &drawArrInd_Dibo );
        glCreateBuffers( 1, &drawArrInd_VboInst );
        glBindVertexArray( drawArrInd_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, drawArrInd_Vbo );
        const Point3p3c POINTS[ DRAW_ARR_IND_NUM_POINTS ]{ Point3p3c{ 0.0f, -5.0f, 0.0f, 0.5f, 0.5f, 0.5f },
                                                           Point3p3c{ 1.0f, -5.0f, 0.0f, 0.5f, 0.5f, 0.5f },
                                                           Point3p3c{ 0.5f, -4.0f, 0.0f, 0.5f, 0.5f, 0.5f } };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        glBindBuffer( GL_DRAW_INDIRECT_BUFFER, drawArrInd_Dibo );
        const DrawArraysIndirectCommand DRAW_INDIRECT_DATA{ 3, DRAW_ARR_IND_NUM_INSTANCES, 0, 0 };
        glBufferData( GL_DRAW_INDIRECT_BUFFER, sizeof( DRAW_INDIRECT_DATA ), &DRAW_INDIRECT_DATA, GL_STATIC_DRAW );
        glBindBuffer( GL_ARRAY_BUFFER, drawArrInd_VboInst );
        const float Z_OFFSETS[ DRAW_ARR_IND_NUM_INSTANCES ]{ 0.0f, -0.5f };
        glBufferData( GL_ARRAY_BUFFER, sizeof( Z_OFFSETS ), Z_OFFSETS, GL_STATIC_DRAW );
        setupVertexArrayInstancedAttribs();
    }

    void OpenGLDrawFunctionsWidget::drawElements_init()
    {
        glCreateVertexArrays( 1, &drawElem_Vao );
        glCreateBuffers( 1, &drawElem_Vbo );
        glCreateBuffers( 1, &drawElem_Ebo );
        glBindVertexArray( drawElem_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, drawElem_Vbo );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, drawElem_Ebo );
        const Point3p3c POINTS[]{ Point3p3c{ 2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f }, Point3p3c{ 3.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
                                  Point3p3c{ 3.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f }, Point3p3c{ 2.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f } };
        const GLuint    ELEMENTS[ DRAW_ELEM_NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0 };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( ELEMENTS ), ELEMENTS, GL_STATIC_DRAW );
    }

    void OpenGLDrawFunctionsWidget::drawElementsBaseVertex_init()
    {
        glCreateVertexArrays( 1, &drawElemBV_Vao );
        glCreateBuffers( 1, &drawElemBV_Ebo );
        glCreateBuffers( 1, &drawElemBV_Vbo );
        glBindVertexArray( drawElemBV_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, drawElemBV_Vbo );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, drawElemBV_Ebo );
        const Point3p3c POINTS[]{ Point3p3c{ 2.0f, -1.0f, 0.0f, 0.75f, 0.0f, 0.0f },  Point3p3c{ 3.0f, -1.0f, 0.0f, 0.8f, 0.0f, 0.0f },
                                  Point3p3c{ 3.0f, -2.0f, 0.0f, 0.75f, 0.0f, 0.0f },  Point3p3c{ 2.0f, -2.0f, 0.0f, 0.8f, 0.0f, 0.0f },
                                  Point3p3c{ 2.0f, -1.0f, -0.5f, 0.75f, 0.0f, 0.0f }, Point3p3c{ 3.0f, -1.0f, -0.5f, 0.8f, 0.0f, 0.0f },
                                  Point3p3c{ 3.0f, -2.0f, -0.5f, 0.75f, 0.0f, 0.0f }, Point3p3c{ 2.0f, -2.0f, -0.5f, 0.8f, 0.0f, 0.0f } };
        const GLuint    ELEMENTS[ DRAW_ELEM_BV_NUM_ELEMENTS ]{ 0, 1, 2, 3, 4, 5 };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( ELEMENTS ), ELEMENTS, GL_STATIC_DRAW );
    }

    void OpenGLDrawFunctionsWidget::drawElementsIndirect_init()
    {
        glCreateVertexArrays( 1, &drawElemInd_Vao );
        glCreateBuffers( 1, &drawElemInd_Vbo );
        glCreateBuffers( 1, &drawElemInd_Ebo );
        glCreateBuffers( 1, &drawElemInd_Dibo );
        glBindVertexArray( drawElemInd_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, drawElemInd_Vbo );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, drawElemInd_Ebo );
        glBindBuffer( GL_DRAW_INDIRECT_BUFFER, drawElemInd_Dibo );
        const Point3p3c POINTS[]{ Point3p3c{ 2.0f, -4.0f, 0.0f, 0.6f, 0.0f, 0.0f }, Point3p3c{ 3.0f, -4.0f, 0.0f, 0.6f, 0.0f, 0.0f },
                                  Point3p3c{ 3.0f, -3.0f, 0.0f, 0.6f, 0.0f, 0.0f }, Point3p3c{ 2.0f, -3.0f, 0.0f, 0.6f, 0.0f, 0.0f } };
        const GLuint    ELEMENTS[]{ 0, 1, 2, 2, 3, 0 };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( ELEMENTS ), ELEMENTS, GL_STATIC_DRAW );
        const DrawElementsIndirectCommand DRAW_ELEMENTS_INDIRECT_DATA[]{ DrawElementsIndirectCommand{ 6, 1, 0, 0, 0 } };
        glBufferData( GL_DRAW_INDIRECT_BUFFER, sizeof( DRAW_ELEMENTS_INDIRECT_DATA ), DRAW_ELEMENTS_INDIRECT_DATA, GL_STATIC_DRAW );
    }

    void OpenGLDrawFunctionsWidget::drawElementsInstanced_init()
    {
        glCreateVertexArrays( 1, &drawElemInst_Vao );
        glCreateBuffers( 1, &drawElemInst_Vbo );
        glCreateBuffers( 1, &drawElemInst_VboInst );
        glCreateBuffers( 1, &drawElemInst_Ebo );
        glBindVertexArray( drawElemInst_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, drawElemInst_Vbo );
        const Point3p3c POINTS[]{ Point3p3c{ 2.0f, -6.0f, 0.0f, 0.4f, 0.0f, 0.0f }, Point3p3c{ 3.0f, -6.0f, 0.0f, 0.4f, 0.0f, 0.0f },
                                  Point3p3c{ 3.0f, -5.0f, 0.0f, 0.4f, 0.0f, 0.0f }, Point3p3c{ 2.0f, -5.0f, 0.0f, 0.4f, 0.0f, 0.0f } };
        const GLuint    ELEMENTS[ DRAW_ELEM_NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0 };
        const float     Z_OFFSETS[ DRAW_ELEM_INST_NUM_INSTANCES ]{ 0.0f, -0.5f, -1.0f, -1.5f };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, drawElemInst_Ebo );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( ELEMENTS ), ELEMENTS, GL_STATIC_DRAW );
        glBindBuffer( GL_ARRAY_BUFFER, drawElemInst_VboInst );
        glBufferData( GL_ARRAY_BUFFER, sizeof( Z_OFFSETS ), Z_OFFSETS, GL_STATIC_DRAW );
        setupVertexArrayInstancedAttribs();
    }

    void OpenGLDrawFunctionsWidget::drawElementsInstancedBaseVertex_init()
    {
        glCreateVertexArrays( 1, &drawElemInstBV_Vao );
        glCreateBuffers( 1, &drawElemInstBV_Vbo );
        glCreateBuffers( 1, &drawElemInstBV_VboInst );
        glCreateBuffers( 1, &drawElemInstBV_Ebo );
        glBindVertexArray( drawElemInstBV_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, drawElemInstBV_Vbo );
        const Point3p3c POINTS[]{
            Point3p3c{ 2.0f, -10.0f, 0.0f, 1.0f, 0.3f, 0.3f },   Point3p3c{ 3.0f, -10.0f, 0.0f, 1.0f, 0.3f, 0.3f },
            Point3p3c{ 3.0f, -9.0f, 0.0f, 1.0f, 0.3f, 0.3f },    Point3p3c{ 2.0f, -9.0f, 0.0f, 1.0f, 0.3f, 0.3f },
            Point3p3c{ 2.0f, -10.0f, -0.25f, 1.0f, 0.3f, 0.3f }, Point3p3c{ 3.0f, -10.0f, -0.25f, 1.0f, 0.3f, 0.3f }
        };
        const GLuint ELEMENTS[ DRAW_ELEM_INST_BV_NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0 };
        const float  Z_OFFSETS[ DRAW_ELEM_INST_BV_NUM_INSTANCES ]{ 0.0f, -0.5f, -1.0f };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        glBindBuffer( GL_ARRAY_BUFFER, drawElemInstBV_VboInst );
        glBufferData( GL_ARRAY_BUFFER, sizeof( Z_OFFSETS ), Z_OFFSETS, GL_STATIC_DRAW );
        setupVertexArrayInstancedAttribs();
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, drawElemInstBV_Ebo );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( ELEMENTS ), ELEMENTS, GL_STATIC_DRAW );
    }

    void OpenGLDrawFunctionsWidget::drawRangeElements_init()
    {
        glCreateVertexArrays( 1, &drawRangeElem_Vao );
        glCreateBuffers( 1, &drawRangeElem_Vbo );
        glCreateBuffers( 1, &drawRangeElem_Ebo );
        glBindVertexArray( drawRangeElem_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, drawRangeElem_Vbo );
        const Point3p3c POINTS[]{ Point3p3c{ 4.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f }, Point3p3c{ 5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
                                  Point3p3c{ 5.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f }, Point3p3c{ 4.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f } };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        const GLuint ELEMENTS[]{ 0, 1, 2, 2, 3, 0 };
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, drawRangeElem_Ebo );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( ELEMENTS ), ELEMENTS, GL_STATIC_DRAW );
    }

    void OpenGLDrawFunctionsWidget::drawRangeElementsBaseVertex_init()
    {
        glCreateVertexArrays( 1, &drawRangeElemBV_Vao );
        glCreateBuffers( 1, &drawRangeElemBV_Vbo );
        glCreateBuffers( 1, &drawRangeElemBV_Ebo );
        glBindVertexArray( drawRangeElemBV_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, drawRangeElemBV_Vbo );
        const Point3p3c POINTS[]{ Point3p3c{ 4.0f, -2.0f, 0.0f, 0.0f, 0.5f, 0.0f },  Point3p3c{ 5.0f, -2.0f, 0.0f, 0.0f, 0.5f, 0.0f },
                                  Point3p3c{ 5.0f, -1.0f, 0.0f, 0.0f, 0.5f, 0.0f },  Point3p3c{ 4.0f, -1.0f, 0.0f, 0.0f, 0.5f, 0.0f },
                                  Point3p3c{ 4.0f, -2.0f, -1.0f, 0.0f, 0.5f, 0.0f }, Point3p3c{ 5.0f, -2.0f, -1.0f, 0.0f, 0.5f, 0.0f },
                                  Point3p3c{ 5.0f, -1.0f, -1.0f, 0.0f, 0.5f, 0.0f }, Point3p3c{ 4.0f, -1.0f, -1.0f, 0.0f, 0.5f, 0.0f } };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, drawRangeElemBV_Ebo );
        const GLuint ELEMENTS[ DRAW_RANGE_ELEM_BV_NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0 };
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( ELEMENTS ), ELEMENTS, GL_STATIC_DRAW );
    }

    void OpenGLDrawFunctionsWidget::multiDrawArrays_init()
    {
        glCreateVertexArrays( 1, &mDrawArr_Vao );
        glCreateBuffers( 1, &mDrawArr_Vbo );
        glBindVertexArray( mDrawArr_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, mDrawArr_Vbo );
        const Point3p3c POINTS[ M_DRAW_ARR_NUM_POINTS ]{
            Point3p3c{ 6.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },  Point3p3c{ 7.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
            Point3p3c{ 7.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f },  Point3p3c{ 6.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f },
            Point3p3c{ 7.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f }, Point3p3c{ 7.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f }
        };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
    }

    void OpenGLDrawFunctionsWidget::multiDrawArraysIndirect_init()
    {
        glCreateVertexArrays( 1, &mDrawArrInd_Vao );
        glCreateBuffers( 1, &mDrawArrInd_Vbo );
        glCreateBuffers( 1, &mDrawArrInd_Dibo );
        glBindVertexArray( mDrawArrInd_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, mDrawArrInd_Vbo );
        const Point3p3c POINTS[ M_DRAW_ARR_NUM_POINTS ]{
            Point3p3c{ 6.0f, -2.0f, 0.0f, 0.0f, 0.0f, 0.8f },  Point3p3c{ 7.0f, -2.0f, 0.0f, 0.0f, 0.0f, 0.8f },
            Point3p3c{ 7.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.8f },  Point3p3c{ 6.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.8f },
            Point3p3c{ 6.0f, -2.0f, -1.0f, 0.0f, 0.0f, 0.8f }, Point3p3c{ 7.0f, -2.0f, -1.0f, 0.0f, 0.0f, 0.8f }
        };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        const DrawArraysIndirectCommand COMMANDS[ M_DRAW_ARR_IND_NUM_COMMANDS ]{ DrawArraysIndirectCommand{ 3, 1, 0, 0 },
                                                                                 DrawArraysIndirectCommand{ 3, 1, 3, 0 } };
        glBindBuffer( GL_DRAW_INDIRECT_BUFFER, mDrawArrInd_Dibo );
        glBufferData( GL_DRAW_INDIRECT_BUFFER, sizeof( COMMANDS ), COMMANDS, GL_STATIC_DRAW );
    }

    void OpenGLDrawFunctionsWidget::multiDrawElements_init()
    {
        glCreateVertexArrays( 1, &mDrawElem_Vao );
        glCreateBuffers( 1, &mDrawElem_Vbo );
        glCreateBuffers( 1, &mDrawElem_Ebo );
        glBindVertexArray( mDrawElem_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, mDrawElem_Vbo );
        const Point3p3c POINTS[]{ Point3p3c{ 6.0f, -4.0f, 0.0f, 0.0f, 0.0f, 0.6f },  Point3p3c{ 7.0f, -4.0f, 0.0f, 0.0f, 0.0f, 0.6f },
                                  Point3p3c{ 7.0f, -3.0f, 0.0f, 0.0f, 0.0f, 0.6f },  Point3p3c{ 6.0f, -3.0f, 0.0f, 0.0f, 0.0f, 0.6f },
                                  Point3p3c{ 6.0f, -4.0f, -1.0f, 0.0f, 0.0f, 0.6f }, Point3p3c{ 7.0f, -4.0f, -1.0f, 0.0f, 0.0f, 0.6f },
                                  Point3p3c{ 7.0f, -3.0f, -1.0f, 0.0f, 0.0f, 0.6f }, Point3p3c{ 6.0f, -3.0f, -1.0f, 0.0f, 0.0f, 0.6f } };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        const GLuint ELEMENTS[ M_DRAW_ELEM_NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 };
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mDrawElem_Ebo );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( ELEMENTS ), ELEMENTS, GL_STATIC_DRAW );
    }

    void OpenGLDrawFunctionsWidget::multiDrawElementsBaseVertex_init()
    {
        glCreateVertexArrays( 1, &mDrawElemBV_Vao );
        glCreateBuffers( 1, &mDrawElemBV_Vbo );
        glCreateBuffers( 1, &mDrawElemBV_Ebo );
        glBindVertexArray( mDrawElemBV_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, mDrawElemBV_Vbo );
        const Point3p3c POINTS[]{ Point3p3c{ 6.0f, -6.0f, 0.0f, 0.0f, 0.0f, 0.4f },  Point3p3c{ 7.0f, -6.0f, 0.0f, 0.0f, 0.0f, 0.4f },
                                  Point3p3c{ 7.0f, -5.0f, 0.0f, 0.0f, 0.0f, 0.4f },  Point3p3c{ 6.0f, -5.0f, 0.0f, 0.0f, 0.0f, 0.4f },
                                  Point3p3c{ 6.0f, -6.0f, -1.0f, 0.0f, 0.0f, 0.4f }, Point3p3c{ 7.0f, -6.0f, -1.0f, 0.0f, 0.0f, 0.4f },
                                  Point3p3c{ 7.0f, -5.0f, -1.0f, 0.0f, 0.0f, 0.4f }, Point3p3c{ 6.0f, -5.0f, -1.0f, 0.0f, 0.0f, 0.4f } };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        const GLuint ELEMENTS[ M_DRAW_ELEM_BV_NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 };
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mDrawElemBV_Ebo );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( ELEMENTS ), ELEMENTS, GL_STATIC_DRAW );
    }

    void OpenGLDrawFunctionsWidget::multiDrawElementsIndirect_init()
    {
        glCreateVertexArrays( 1, &mDrawElemInd_Vao );
        glCreateBuffers( 1, &mDrawElemInd_Vbo );
        glCreateBuffers( 1, &mDrawElemInd_Ebo );
        glCreateBuffers( 1, &mDrawElemInd_Dibo );
        glBindVertexArray( mDrawElemInd_Vao );
        glBindBuffer( GL_ARRAY_BUFFER, mDrawElemInd_Vbo );
        const Point3p3c POINTS[]{ Point3p3c{ 6.0f, -8.0f, 0.0f, 0.0f, 0.0f, 0.25f },  Point3p3c{ 7.0f, -8.0f, 0.0f, 0.0f, 0.0f, 0.25f },
                                  Point3p3c{ 7.0f, -7.0f, 0.0f, 0.0f, 0.0f, 0.25f },  Point3p3c{ 6.0f, -7.0f, 0.0f, 0.0f, 0.0f, 0.25f },
                                  Point3p3c{ 6.0f, -8.0f, -1.0f, 0.0f, 0.0f, 0.25f }, Point3p3c{ 7.0f, -8.0f, -1.0f, 0.0f, 0.0f, 0.25f },
                                  Point3p3c{ 7.0f, -7.0f, -1.0f, 0.0f, 0.0f, 0.25f }, Point3p3c{ 6.0f, -7.0f, -1.0f, 0.0f, 0.0f, 0.25f } };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mDrawElemInd_Ebo );
        const GLuint ELEMENTS[]{ 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 };
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( ELEMENTS ), ELEMENTS, GL_STATIC_DRAW );
        glBindBuffer( GL_DRAW_INDIRECT_BUFFER, mDrawElemInd_Dibo );
        const DrawElementsIndirectCommand DRAW_COMMANDS[]{ DrawElementsIndirectCommand{ 6, 1, 0, 0, 0 },
                                                           DrawElementsIndirectCommand{ 6, 1, 6, 0, 0 } };
        glBufferData( GL_DRAW_INDIRECT_BUFFER, sizeof( DRAW_COMMANDS ), DRAW_COMMANDS, GL_STATIC_DRAW );
    }

    //--------- cleanup ----------

    void OpenGLDrawFunctionsWidget::drawArrays_cleanup()
    {
        openGLVertexArrayCleanup( drawArr_Vao );
        openGLBufferCleanup( drawArr_Vbo );
    }

    void OpenGLDrawFunctionsWidget::drawArraysInstanced_cleanup()
    {
        openGLVertexArrayCleanup( drawArrInst_Vao );
        openGLBufferCleanup( drawArrInst_Vbo );
        openGLBufferCleanup( drawArrInst_VboInst );
    }

    void OpenGLDrawFunctionsWidget::drawArraysIndirect_cleanup()
    {
        openGLVertexArrayCleanup( drawArrInd_Vao );
        openGLBufferCleanup( drawArrInd_Vbo );
        openGLBufferCleanup( drawArrInd_VboInst );
        openGLBufferCleanup( drawArrInd_Dibo );
    }

    void OpenGLDrawFunctionsWidget::drawElements_cleanup()
    {
        openGLVertexArrayCleanup( drawElem_Vao );
        openGLBufferCleanup( drawElem_Ebo );
        openGLBufferCleanup( drawElem_Vbo );
    }

    void OpenGLDrawFunctionsWidget::drawElementsBaseVertex_cleanup()
    {
        openGLVertexArrayCleanup( drawElemBV_Vao );
        openGLBufferCleanup( drawElemBV_Vbo );
        openGLBufferCleanup( drawElemBV_Ebo );
    }

    void OpenGLDrawFunctionsWidget::drawElementsIndirect_cleanup()
    {
        openGLVertexArrayCleanup( drawElemInd_Vao );
        openGLBufferCleanup( drawElemInd_Vbo );
        openGLBufferCleanup( drawElemInd_Ebo );
        openGLBufferCleanup( drawElemInd_Dibo );
    }

    void OpenGLDrawFunctionsWidget::drawElementsInstanced_cleanup()
    {
        openGLVertexArrayCleanup( drawElemInst_Vao );
        openGLBufferCleanup( drawElemInst_Vbo );
        openGLBufferCleanup( drawElemInst_VboInst );
        openGLBufferCleanup( drawElemInst_Ebo );
    }

    void OpenGLDrawFunctionsWidget::drawElementsInstancedBaseVertex_cleanup()
    {
        openGLVertexArrayCleanup( drawElemInstBV_Vao );
        openGLBufferCleanup( drawElemInstBV_Vbo );
        openGLBufferCleanup( drawElemInstBV_VboInst );
        openGLBufferCleanup( drawElemInstBV_Ebo );
    }

    void OpenGLDrawFunctionsWidget::drawRangeElements_cleanup()
    {
        openGLVertexArrayCleanup( drawRangeElem_Vao );
        openGLBufferCleanup( drawRangeElem_Vbo );
        openGLBufferCleanup( drawRangeElem_Ebo );
    }

    void OpenGLDrawFunctionsWidget::drawRangeElementsBaseVertex_cleanup()
    {
        openGLVertexArrayCleanup( drawRangeElemBV_Vao );
        openGLBufferCleanup( drawRangeElemBV_Vbo );
        openGLBufferCleanup( drawRangeElemBV_Ebo );
    }

    void OpenGLDrawFunctionsWidget::multiDrawArrays_cleanup()
    {
        openGLVertexArrayCleanup( mDrawArr_Vao );
        openGLBufferCleanup( mDrawArr_Vbo );
    }

    void OpenGLDrawFunctionsWidget::multiDrawArraysIndirect_cleanup()
    {
        openGLVertexArrayCleanup( mDrawArrInd_Vao );
        openGLBufferCleanup( mDrawArrInd_Vbo );
        openGLBufferCleanup( mDrawArrInd_Dibo );
    }

    void OpenGLDrawFunctionsWidget::multiDrawElements_cleanup()
    {
        openGLVertexArrayCleanup( mDrawElem_Vao );
        openGLBufferCleanup( mDrawElem_Vbo );
        openGLBufferCleanup( mDrawElem_Ebo );
    }

    void OpenGLDrawFunctionsWidget::multiDrawElementsBaseVertex_cleanup()
    {
        openGLVertexArrayCleanup( mDrawElemBV_Vao );
        openGLBufferCleanup( mDrawElemBV_Vbo );
        openGLBufferCleanup( mDrawElemBV_Ebo );
    }

    void OpenGLDrawFunctionsWidget::multiDrawElementsIndirect_cleanup()
    {
        openGLVertexArrayCleanup( mDrawElemInd_Vao );
        openGLBufferCleanup( mDrawElemInd_Vbo );
        openGLBufferCleanup( mDrawElemInd_Ebo );
        openGLBufferCleanup( mDrawElemInd_Dibo );
    }

    //--------- utility ---------------

    void OpenGLDrawFunctionsWidget::setupVertexArrayAttribs()
    {
        glEnableVertexAttribArray( 0 );
        glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), 0 );
        glEnableVertexAttribArray( 1 );
        glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, sizeof( Point3p3c ), (void *)( 3 * sizeof( float ) ) );
    }

    void OpenGLDrawFunctionsWidget::setupVertexArrayInstancedAttribs()
    {
        glEnableVertexAttribArray( 2 );
        glVertexAttribPointer( 2, 1, GL_FLOAT, GL_FALSE, sizeof( GLfloat ), 0 );
        glVertexAttribDivisor( 2, 1 );
    }

    void OpenGLDrawFunctionsWidget::openGLBufferCleanup( GLuint & bufferObject )
    {
        if( bufferObject )
        {
            glDeleteBuffers( 1, &bufferObject );
        }
    }

    void OpenGLDrawFunctionsWidget::openGLVertexArrayCleanup( GLuint & vertexArray )
    {
        if( vertexArray )
        {
            glDeleteVertexArrays( 1, &vertexArray );
        }
    }

} // namespace Ouquitoure
