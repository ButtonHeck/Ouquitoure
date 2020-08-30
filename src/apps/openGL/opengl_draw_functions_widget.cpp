#include "Apps/OpenGL/OpenGLDrawFunctionsWidget"
#include "Math/Point3Pos3Color"
#include "Log"

#include <glm/gtc/type_ptr.hpp>
#include <array>

namespace Ouquitoure
{

    OpenGLDrawFunctionsWidget::OpenGLDrawFunctionsWidget( const QString & name, QWidget * parent )
        : OpenGLWidgetWithCamera( name, parent )

        // glDrawArrays
        , drawArrBuffers( this, 2 )

        // glDrawArraysInstanced + glDrawArraysInstancedBaseInstance
        , drawArrInstBuffers( this, 3 )

        // glDrawArraysIndirect
        , drawArrIndBuffers( this, 4 )

        // glDrawElements
        , drawElemBuffers( this, 3 )

        // glDrawElementsBaseVertex
        , drawElemBVBuffers( this, 3 )

        // glDrawElementsIndirect
        , drawElemIndBuffers( this, 4 )

        // glDrawElementsInstanced + glDrawElementsInstancedBaseInstance
        , drawElemInstBuffers( this, 4 )

        // glDrawElementsInstancedBaseVertex + glDrawElementsInstancedBaseVertexBaseInstance
        , drawElemInstBVBuffers( this, 4 )

        // glDrawRangeElements
        , drawRangeElemBuffers( this, 3 )

        // glDrawRangeElementsBaseVertex
        , drawRangeElemBVBuffers( this, 3 )

        // glMultiDrawArrays
        , mDrawArrBuffers( this, 2 )

        // glMultiDrawArraysIndirect
        , mDrawArrIndBuffers( this, 3 )

        // glMultiDrawElements
        , mDrawElemBuffers( this, 3 )

        // glMultiDrawElementsBaseVertex
        , mDrawElemBVBuffers( this, 3 )

        // glMultiDrawElementsIndirect
        , mDrawElemIndBuffers( this, 4 )
    {
        allDrawFunctions[ DRAW_ARRAYS ] =
            DrawFunctionData( true, &OpenGLDrawFunctionsWidget::drawArrays_init, &OpenGLDrawFunctionsWidget::drawArrays,
                              &OpenGLDrawFunctionsWidget::drawArrays_cleanup, "glDrawArrays" );
        allDrawFunctions[ DRAW_ARRAYS_INSTANCED ] =
            DrawFunctionData( true, &OpenGLDrawFunctionsWidget::drawArraysInstanced_init, &OpenGLDrawFunctionsWidget::drawArraysInstanced,
                              &OpenGLDrawFunctionsWidget::drawArraysInstanced_cleanup, "glDrawArraysInstanced" );
        allDrawFunctions[ DRAW_ARRAYS_INSTANCED_BASE_INSTANCE ] =
            DrawFunctionData( true, &OpenGLDrawFunctionsWidget::drawArraysInstanced_init, &OpenGLDrawFunctionsWidget::drawArraysInstanced,
                              &OpenGLDrawFunctionsWidget::drawArraysInstanced_cleanup, "glDrawArraysInstancedBaseInstance" );
        allDrawFunctions[ DRAW_ARRAYS_INDIRECT ] =
            DrawFunctionData( true, &OpenGLDrawFunctionsWidget::drawArraysIndirect_init, &OpenGLDrawFunctionsWidget::drawArraysIndirect,
                              &OpenGLDrawFunctionsWidget::drawArraysIndirect_cleanup, "glDrawArraysIndirect" );
        allDrawFunctions[ DRAW_ELEMENTS ] =
            DrawFunctionData( true, &OpenGLDrawFunctionsWidget::drawElements_init, &OpenGLDrawFunctionsWidget::drawElements,
                              &OpenGLDrawFunctionsWidget::drawElements_cleanup, "glDrawElements" );
        allDrawFunctions[ DRAW_ELEMENTS_BASE_VERTEX ] = DrawFunctionData(
            true, &OpenGLDrawFunctionsWidget::drawElementsBaseVertex_init, &OpenGLDrawFunctionsWidget::drawElementsBaseVertex,
            &OpenGLDrawFunctionsWidget::drawElementsBaseVertex_cleanup, "glDrawElementsBaseVertex" );
        allDrawFunctions[ DRAW_ELEMENTS_INDIRECT ] =
            DrawFunctionData( true, &OpenGLDrawFunctionsWidget::drawElementsIndirect_init, &OpenGLDrawFunctionsWidget::drawElementsIndirect,
                              &OpenGLDrawFunctionsWidget::drawElementsIndirect_cleanup, "glDrawElementsIndirect" );
        allDrawFunctions[ DRAW_ELEMENTS_INSTANCED ] = DrawFunctionData(
            true, &OpenGLDrawFunctionsWidget::drawElementsInstanced_init, &OpenGLDrawFunctionsWidget::drawElementsInstanced,
            &OpenGLDrawFunctionsWidget::drawElementsInstanced_cleanup, "glDrawElementsInstanced" );
        allDrawFunctions[ DRAW_ELEMENTS_INSTANCED_BASE_INSTANCE ] = DrawFunctionData(
            true, &OpenGLDrawFunctionsWidget::drawElementsInstanced_init, &OpenGLDrawFunctionsWidget::drawElementsInstanced,
            &OpenGLDrawFunctionsWidget::drawElementsInstanced_cleanup, "glDrawElementsInstancedBaseInstance" );
        allDrawFunctions[ DRAW_ELEMENTS_INSTANCED_BASE_VERTEX ] =
            DrawFunctionData( true, &OpenGLDrawFunctionsWidget::drawElementsInstancedBaseVertex_init,
                              &OpenGLDrawFunctionsWidget::drawElementsInstancedBaseVertex,
                              &OpenGLDrawFunctionsWidget::drawElementsInstancedBaseVertex_cleanup, "glDrawElementsInstancedBaseVertex" );
        allDrawFunctions[ DRAW_ELEMENTS_INSTANCED_BASE_VERTEX_BASE_INSTANCE ] = DrawFunctionData(
            true, &OpenGLDrawFunctionsWidget::drawElementsInstancedBaseVertex_init,
            &OpenGLDrawFunctionsWidget::drawElementsInstancedBaseVertex,
            &OpenGLDrawFunctionsWidget::drawElementsInstancedBaseVertex_cleanup, "glDrawElementsInstancedBaseVertexBaseInstance" );
        allDrawFunctions[ DRAW_RANGE_ELEMENTS ] =
            DrawFunctionData( true, &OpenGLDrawFunctionsWidget::drawRangeElements_init, &OpenGLDrawFunctionsWidget::drawRangeElements,
                              &OpenGLDrawFunctionsWidget::drawRangeElements_cleanup, "glDrawRangeElements" );
        allDrawFunctions[ DRAW_RANGE_ELEMENTS_BASE_VERTEX ] = DrawFunctionData(
            true, &OpenGLDrawFunctionsWidget::drawRangeElementsBaseVertex_init, &OpenGLDrawFunctionsWidget::drawRangeElementsBaseVertex,
            &OpenGLDrawFunctionsWidget::drawRangeElementsBaseVertex_cleanup, "glDrawRangeElementsBaseVertex" );
        allDrawFunctions[ MULTI_DRAW_ARRAYS ] =
            DrawFunctionData( true, &OpenGLDrawFunctionsWidget::multiDrawArrays_init, &OpenGLDrawFunctionsWidget::multiDrawArrays,
                              &OpenGLDrawFunctionsWidget::multiDrawArrays_cleanup, "glMultiDrawArrays" );
        allDrawFunctions[ MULTI_DRAW_ARRAYS_INDIRECT ] = DrawFunctionData(
            true, &OpenGLDrawFunctionsWidget::multiDrawArraysIndirect_init, &OpenGLDrawFunctionsWidget::multiDrawArraysIndirect,
            &OpenGLDrawFunctionsWidget::multiDrawArraysIndirect_cleanup, "glMultiDrawArraysIndirect" );
        allDrawFunctions[ MULTI_DRAW_ELEMENTS ] =
            DrawFunctionData( true, &OpenGLDrawFunctionsWidget::multiDrawElements_init, &OpenGLDrawFunctionsWidget::multiDrawElements,
                              &OpenGLDrawFunctionsWidget::multiDrawElements_cleanup, "glMultiDrawElements" );
        allDrawFunctions[ MULTI_DRAW_ELEMENTS_BASE_VERTEX ] = DrawFunctionData(
            true, &OpenGLDrawFunctionsWidget::multiDrawElementsBaseVertex_init, &OpenGLDrawFunctionsWidget::multiDrawElementsBaseVertex,
            &OpenGLDrawFunctionsWidget::multiDrawElementsBaseVertex_cleanup, "glMultiDrawElementsBaseVertex" );
        allDrawFunctions[ MULTI_DRAW_ELEMENTS_INDIRECT ] = DrawFunctionData(
            true, &OpenGLDrawFunctionsWidget::multiDrawElementsIndirect_init, &OpenGLDrawFunctionsWidget::multiDrawElementsIndirect,
            &OpenGLDrawFunctionsWidget::multiDrawElementsIndirect_cleanup, "glMultiDrawElementsIndirect" );
    }

    OpenGLDrawFunctionsWidget::~OpenGLDrawFunctionsWidget()
    {
        cleanup();
    }

    QString OpenGLDrawFunctionsWidget::getDrawFunctionName( OpenGLDrawFunctionsWidget::DRAW_FUNCTIONS functionCode )
    {
        return allDrawFunctions[ functionCode ].functionName;
    }

    void OpenGLDrawFunctionsWidget::initializeGL()
    {
        OpenGLWidgetBase::initializeGL();

        glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
        glPointSize( 5.0f );
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

        initializeOpenGLObjects();
        initializeOpenGLShaders();

        camera.setPosition( 3.0f, -4.0f, 10.0f );
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

        for( auto & functionContext: allDrawFunctions )
        {
            DrawFunctionData & drawFunctionData = functionContext.second;
            if( drawFunctionData.enabled )
            {
                void ( OpenGLDrawFunctionsWidget::*memberDrawFunction )() = drawFunctionData.drawFunction;
                auto drawFunction                                         = std::bind( memberDrawFunction, this );
                drawFunction();
            }
        }
    }

    void OpenGLDrawFunctionsWidget::setFunctionEnabled( bool enabled )
    {
        DRAW_FUNCTIONS function              = (DRAW_FUNCTIONS)sender()->objectName().toInt();
        allDrawFunctions[ function ].enabled = enabled;
        update();
    }

    void OpenGLDrawFunctionsWidget::initializeOpenGLObjects()
    {
        for( auto & functionContext: allDrawFunctions )
        {
            DrawFunctionData & drawFunctionData                       = functionContext.second;
            void ( OpenGLDrawFunctionsWidget::*memberInitFunction )() = drawFunctionData.initFunction;
            auto initFunction                                         = std::bind( memberInitFunction, this );
            initFunction();
        }
    }

    void OpenGLDrawFunctionsWidget::initializeOpenGLShaders()
    {
        OpenGLWidgetBase::initializeOpenGLMainShaderProgram( "OpenGLDrawFunctions" );
    }

    void OpenGLDrawFunctionsWidget::cleanup()
    {
        for( auto & functionContext: allDrawFunctions )
        {
            DrawFunctionData & drawFunctionData                          = functionContext.second;
            void ( OpenGLDrawFunctionsWidget::*memberCleanupFunction )() = drawFunctionData.cleanupFunction;
            auto cleanupFunction                                         = std::bind( memberCleanupFunction, this );
            cleanupFunction();
        }

        openGLShaderProgramsCleanup();
    }

    //-------- drawing -------------

    void OpenGLDrawFunctionsWidget::drawArrays()
    {
        drawArrBuffers.bind( VAO );
        glDrawArrays( GL_TRIANGLES, 0, DRAW_ARR_NUM_POINTS );
        glDrawArrays( GL_POINTS, 0, DRAW_ARR_NUM_POINTS );
    }

    void OpenGLDrawFunctionsWidget::drawArraysInstanced()
    {
        drawArrInstBuffers.bind( VAO );
        if( allDrawFunctions[ DRAW_ARRAYS_INSTANCED ].enabled )
        {
            glDrawArraysInstanced( GL_TRIANGLES, 0, DRAW_ARR_INST_NUM_POINTS, DRAW_ARR_INST_NUM_INSTANCES );
            glDrawArraysInstanced( GL_POINTS, 0, DRAW_ARR_INST_NUM_POINTS, DRAW_ARR_INST_NUM_INSTANCES );
        }
        if( allDrawFunctions[ DRAW_ARRAYS_INSTANCED_BASE_INSTANCE ].enabled )
        {
            glLineWidth( 3.0f );
            glDrawArraysInstancedBaseInstance( GL_TRIANGLES, 0, DRAW_ARR_INST_NUM_POINTS, DRAW_ARR_INST_NUM_INSTANCES, 1 );
            glLineWidth( 1.0f );
        }
    }

    void OpenGLDrawFunctionsWidget::drawArraysIndirect()
    {
        drawArrIndBuffers.bind( VAO | DIBO );
        glDrawArraysIndirect( GL_TRIANGLES, nullptr );
        glDrawArraysIndirect( GL_POINTS, nullptr );
    }

    void OpenGLDrawFunctionsWidget::drawElements()
    {
        drawElemBuffers.bind( VAO );
        glDrawElements( GL_TRIANGLES, DRAW_ELEM_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr );
        glDrawElements( GL_POINTS, DRAW_ELEM_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr );
    }

    void OpenGLDrawFunctionsWidget::drawElementsBaseVertex()
    {
        drawElemBVBuffers.bind( VAO );
        glDrawElementsBaseVertex( GL_TRIANGLES, DRAW_ELEM_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr, 2 );
        glDrawElementsBaseVertex( GL_POINTS, DRAW_ELEM_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr, 2 );
    }

    void OpenGLDrawFunctionsWidget::drawElementsIndirect()
    {
        drawElemIndBuffers.bind( VAO | DIBO );
        glDrawElementsIndirect( GL_TRIANGLES, GL_UNSIGNED_INT, nullptr );
        glDrawElementsIndirect( GL_POINTS, GL_UNSIGNED_INT, nullptr );
    }

    void OpenGLDrawFunctionsWidget::drawElementsInstanced()
    {
        drawElemInstBuffers.bind( VAO );
        if( allDrawFunctions[ DRAW_ELEMENTS_INSTANCED ].enabled )
        {
            glDrawElementsInstanced( GL_TRIANGLES, DRAW_ELEM_INST_NUM_ELEMENTS, GL_UNSIGNED_INT, 0, DRAW_ELEM_INST_NUM_INSTANCES );
            glDrawElementsInstanced( GL_POINTS, DRAW_ELEM_INST_NUM_ELEMENTS, GL_UNSIGNED_INT, 0, DRAW_ELEM_INST_NUM_INSTANCES );
        }
        if( allDrawFunctions[ DRAW_ELEMENTS_INSTANCED_BASE_INSTANCE ].enabled )
        {
            glLineWidth( 3.0f );
            glDrawElementsInstancedBaseInstance( GL_TRIANGLES, DRAW_ELEM_INST_NUM_ELEMENTS, GL_UNSIGNED_INT, 0,
                                                 DRAW_ELEM_INST_NUM_INSTANCES, 1 );
            glLineWidth( 1.0f );
        }
    }

    void OpenGLDrawFunctionsWidget::drawElementsInstancedBaseVertex()
    {
        drawElemInstBVBuffers.bind( VAO );
        if( allDrawFunctions[ DRAW_ELEMENTS_INSTANCED_BASE_VERTEX ].enabled )
        {
            glDrawElementsInstancedBaseVertex( GL_TRIANGLES, DRAW_ELEM_INST_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, 0,
                                               DRAW_ELEM_INST_BV_NUM_INSTANCES, 1 );
            glDrawElementsInstancedBaseVertex( GL_POINTS, DRAW_ELEM_INST_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, 0,
                                               DRAW_ELEM_INST_BV_NUM_INSTANCES, 1 );
        }
        if( allDrawFunctions[ DRAW_ELEMENTS_INSTANCED_BASE_VERTEX_BASE_INSTANCE ].enabled )
        {
            glLineWidth( 3.0f );
            glDrawElementsInstancedBaseVertexBaseInstance( GL_TRIANGLES, DRAW_ELEM_INST_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, 0,
                                                           DRAW_ELEM_INST_BV_NUM_INSTANCES, 1, 1 );
            glLineWidth( 1.0f );
        }
    }

    void OpenGLDrawFunctionsWidget::drawRangeElements()
    {
        drawRangeElemBuffers.bind( VAO );
        glDrawRangeElements( GL_TRIANGLES, 3, 6, DRAW_RANGE_ELEM_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr );
        glDrawRangeElements( GL_POINTS, 0, 3, DRAW_RANGE_ELEM_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr );
    }

    void OpenGLDrawFunctionsWidget::drawRangeElementsBaseVertex()
    {
        drawRangeElemBVBuffers.bind( VAO );
        glDrawRangeElementsBaseVertex( GL_TRIANGLES, 0, 6, DRAW_RANGE_ELEM_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr, 1 );
        glDrawRangeElementsBaseVertex( GL_POINTS, 0, 6, DRAW_RANGE_ELEM_BV_NUM_ELEMENTS, GL_UNSIGNED_INT, nullptr, 1 );
    }

    void OpenGLDrawFunctionsWidget::multiDrawArrays()
    {
        mDrawArrBuffers.bind( VAO );
        const GLint   FIRSTS[]{ 0, 3 };
        const GLsizei COUNTS[]{ 3, 3 };
        glMultiDrawArrays( GL_TRIANGLES, FIRSTS, COUNTS, 2 );
        glMultiDrawArrays( GL_POINTS, FIRSTS, COUNTS, 2 );
    }

    void OpenGLDrawFunctionsWidget::multiDrawArraysIndirect()
    {
        mDrawArrIndBuffers.bind( VAO | DIBO );
        glMultiDrawArraysIndirect( GL_TRIANGLES, nullptr, M_DRAW_ARR_IND_NUM_COMMANDS, sizeof( DrawArraysIndirectCommand ) );
        glMultiDrawArraysIndirect( GL_POINTS, nullptr, M_DRAW_ARR_IND_NUM_COMMANDS, sizeof( DrawArraysIndirectCommand ) );
    }

    void OpenGLDrawFunctionsWidget::multiDrawElements()
    {
        mDrawElemBuffers.bind( VAO );
        const GLsizei COUNTS[]{ 6, 3 };
        const GLuint  INDICES[][ 2 ]{ { 0 }, { 6 * sizeof( GLuint ) } };
        glMultiDrawElements( GL_TRIANGLES, COUNTS, GL_UNSIGNED_INT, (const GLvoid **)INDICES, 2 );
        glMultiDrawElements( GL_POINTS, COUNTS, GL_UNSIGNED_INT, (const GLvoid **)INDICES, 2 );
    }

    void OpenGLDrawFunctionsWidget::multiDrawElementsBaseVertex()
    {
        mDrawElemBVBuffers.bind( VAO );
        const GLsizei COUNTS[]{ 6, 3 };
        const GLuint  INDICES[][ 2 ]{ { 0 }, { 6 * sizeof( GLuint ) } };
        const GLint   BASE_VERTICES[]{ 2, 1 };
        glMultiDrawElementsBaseVertex( GL_TRIANGLES, COUNTS, GL_UNSIGNED_INT, (const GLvoid **)INDICES, 2, BASE_VERTICES );
        glMultiDrawElementsBaseVertex( GL_POINTS, COUNTS, GL_UNSIGNED_INT, (const GLvoid **)INDICES, 2, BASE_VERTICES );
    }

    void OpenGLDrawFunctionsWidget::multiDrawElementsIndirect()
    {
        mDrawElemIndBuffers.bind( VAO | DIBO );
        glMultiDrawElementsIndirect( GL_TRIANGLES, GL_UNSIGNED_INT, nullptr, 2, 0 );
        glMultiDrawElementsIndirect( GL_POINTS, GL_UNSIGNED_INT, nullptr, 2, 0 );
    }

    //------- initialization --------------

    void OpenGLDrawFunctionsWidget::drawArrays_init()
    {
        drawArrBuffers.create( VAO | VBO );
        drawArrBuffers.bind( VAO | VBO );
        const Point3p3c POINTS[]{ Point3p3c{ 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f }, Point3p3c{ 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
                                  Point3p3c{ 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f } };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
    }

    void OpenGLDrawFunctionsWidget::drawArraysInstanced_init()
    {
        drawArrInstBuffers.create( VAO | VBO | INSTANCE_VBO );
        drawArrInstBuffers.bind( VAO | VBO );
        const Point3p3c POINTS[]{ Point3p3c{ 0.0f, -2.0f, 0.0f, 0.75f, 0.75f, 0.75f }, Point3p3c{ 1.0f, -2.0f, 0.0f, 0.75f, 0.75f, 0.75f },
                                  Point3p3c{ 1.0f, -1.0f, 0.0f, 0.75f, 0.75f, 0.75f } };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        drawArrInstBuffers.bind( INSTANCE_VBO );
        const float Z_OFFSETS[ DRAW_ARR_INST_NUM_INSTANCES ]{ 0.0f, -0.5f, -1.0f, -1.5f };
        glBufferData( GL_ARRAY_BUFFER, sizeof( Z_OFFSETS ), Z_OFFSETS, GL_STATIC_DRAW );
        setupVertexArrayInstancedAttribs();
    }

    void OpenGLDrawFunctionsWidget::drawArraysIndirect_init()
    {
        drawArrIndBuffers.create( VAO | VBO | DIBO | INSTANCE_VBO );
        drawArrIndBuffers.bind( VAO | VBO );
        const Point3p3c POINTS[ DRAW_ARR_IND_NUM_POINTS ]{ Point3p3c{ 0.0f, -5.0f, 0.0f, 0.5f, 0.5f, 0.5f },
                                                           Point3p3c{ 1.0f, -5.0f, 0.0f, 0.5f, 0.5f, 0.5f },
                                                           Point3p3c{ 0.5f, -4.0f, 0.0f, 0.5f, 0.5f, 0.5f } };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        drawArrIndBuffers.bind( DIBO | INSTANCE_VBO );
        const DrawArraysIndirectCommand DRAW_INDIRECT_DATA{ 3, DRAW_ARR_IND_NUM_INSTANCES, 0, 0 };
        glBufferData( GL_DRAW_INDIRECT_BUFFER, sizeof( DRAW_INDIRECT_DATA ), &DRAW_INDIRECT_DATA, GL_STATIC_DRAW );
        const float Z_OFFSETS[ DRAW_ARR_IND_NUM_INSTANCES ]{ 0.0f, -0.5f };
        glBufferData( GL_ARRAY_BUFFER, sizeof( Z_OFFSETS ), Z_OFFSETS, GL_STATIC_DRAW );
        setupVertexArrayInstancedAttribs();
    }

    void OpenGLDrawFunctionsWidget::drawElements_init()
    {
        drawElemBuffers.create( VAO | VBO | EBO );
        drawElemBuffers.bind( VAO | VBO | EBO );
        const Point3p3c POINTS[]{ Point3p3c{ 2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f }, Point3p3c{ 3.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f },
                                  Point3p3c{ 3.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f }, Point3p3c{ 2.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f } };
        const GLuint    ELEMENTS[ DRAW_ELEM_NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0 };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( ELEMENTS ), ELEMENTS, GL_STATIC_DRAW );
    }

    void OpenGLDrawFunctionsWidget::drawElementsBaseVertex_init()
    {
        drawElemBVBuffers.create( VAO | VBO | EBO );
        drawElemBVBuffers.bind( VAO | VBO | EBO );
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
        drawElemIndBuffers.create( VAO | VBO | EBO | DIBO );
        drawElemIndBuffers.bind( VAO | VBO | EBO | DIBO );
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
        drawElemInstBuffers.create( VAO | VBO | INSTANCE_VBO | EBO );
        drawElemInstBuffers.bind( VAO | VBO );
        const Point3p3c POINTS[]{ Point3p3c{ 2.0f, -6.0f, 0.0f, 0.4f, 0.0f, 0.0f }, Point3p3c{ 3.0f, -6.0f, 0.0f, 0.4f, 0.0f, 0.0f },
                                  Point3p3c{ 3.0f, -5.0f, 0.0f, 0.4f, 0.0f, 0.0f }, Point3p3c{ 2.0f, -5.0f, 0.0f, 0.4f, 0.0f, 0.0f } };
        const GLuint    ELEMENTS[ DRAW_ELEM_NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0 };
        const float     Z_OFFSETS[ DRAW_ELEM_INST_NUM_INSTANCES ]{ 0.0f, -0.5f, -1.0f, -1.5f };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        drawElemInstBuffers.bind( EBO | INSTANCE_VBO );
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( ELEMENTS ), ELEMENTS, GL_STATIC_DRAW );
        glBufferData( GL_ARRAY_BUFFER, sizeof( Z_OFFSETS ), Z_OFFSETS, GL_STATIC_DRAW );
        setupVertexArrayInstancedAttribs();
    }

    void OpenGLDrawFunctionsWidget::drawElementsInstancedBaseVertex_init()
    {
        drawElemInstBVBuffers.create( VAO | VBO | INSTANCE_VBO | EBO );
        drawElemInstBVBuffers.bind( VAO | VBO | EBO );
        const Point3p3c POINTS[]{
            Point3p3c{ 2.0f, -10.0f, 0.0f, 1.0f, 0.3f, 0.3f },   Point3p3c{ 3.0f, -10.0f, 0.0f, 1.0f, 0.3f, 0.3f },
            Point3p3c{ 3.0f, -9.0f, 0.0f, 1.0f, 0.3f, 0.3f },    Point3p3c{ 2.0f, -9.0f, 0.0f, 1.0f, 0.3f, 0.3f },
            Point3p3c{ 2.0f, -10.0f, -0.25f, 1.0f, 0.3f, 0.3f }, Point3p3c{ 3.0f, -10.0f, -0.25f, 1.0f, 0.3f, 0.3f }
        };
        const GLuint ELEMENTS[ DRAW_ELEM_INST_BV_NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0 };
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( ELEMENTS ), ELEMENTS, GL_STATIC_DRAW );
        const float Z_OFFSETS[ DRAW_ELEM_INST_BV_NUM_INSTANCES ]{ 0.0f, -0.5f, -1.0f };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        drawElemInstBVBuffers.bind( INSTANCE_VBO );
        glBufferData( GL_ARRAY_BUFFER, sizeof( Z_OFFSETS ), Z_OFFSETS, GL_STATIC_DRAW );
        setupVertexArrayInstancedAttribs();
    }

    void OpenGLDrawFunctionsWidget::drawRangeElements_init()
    {
        drawRangeElemBuffers.create( VAO | VBO | EBO );
        drawRangeElemBuffers.bind( VAO | VBO | EBO );
        const Point3p3c POINTS[]{ Point3p3c{ 4.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f }, Point3p3c{ 5.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
                                  Point3p3c{ 5.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f }, Point3p3c{ 4.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f } };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        const GLuint ELEMENTS[]{ 0, 1, 2, 2, 3, 0 };
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( ELEMENTS ), ELEMENTS, GL_STATIC_DRAW );
    }

    void OpenGLDrawFunctionsWidget::drawRangeElementsBaseVertex_init()
    {
        drawRangeElemBVBuffers.create( VAO | VBO | EBO );
        drawRangeElemBVBuffers.bind( VAO | VBO | EBO );
        const Point3p3c POINTS[]{ Point3p3c{ 4.0f, -2.0f, 0.0f, 0.0f, 0.5f, 0.0f },  Point3p3c{ 5.0f, -2.0f, 0.0f, 0.0f, 0.5f, 0.0f },
                                  Point3p3c{ 5.0f, -1.0f, 0.0f, 0.0f, 0.5f, 0.0f },  Point3p3c{ 4.0f, -1.0f, 0.0f, 0.0f, 0.5f, 0.0f },
                                  Point3p3c{ 4.0f, -2.0f, -1.0f, 0.0f, 0.5f, 0.0f }, Point3p3c{ 5.0f, -2.0f, -1.0f, 0.0f, 0.5f, 0.0f },
                                  Point3p3c{ 5.0f, -1.0f, -1.0f, 0.0f, 0.5f, 0.0f }, Point3p3c{ 4.0f, -1.0f, -1.0f, 0.0f, 0.5f, 0.0f } };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        const GLuint ELEMENTS[ DRAW_RANGE_ELEM_BV_NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0 };
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( ELEMENTS ), ELEMENTS, GL_STATIC_DRAW );
    }

    void OpenGLDrawFunctionsWidget::multiDrawArrays_init()
    {
        mDrawArrBuffers.create( VAO | VBO );
        mDrawArrBuffers.bind( VAO | VBO );
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
        mDrawArrIndBuffers.create( VAO | VBO | DIBO );
        mDrawArrIndBuffers.bind( VAO | VBO | DIBO );
        const Point3p3c POINTS[ M_DRAW_ARR_NUM_POINTS ]{
            Point3p3c{ 6.0f, -2.0f, 0.0f, 0.0f, 0.0f, 0.8f },  Point3p3c{ 7.0f, -2.0f, 0.0f, 0.0f, 0.0f, 0.8f },
            Point3p3c{ 7.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.8f },  Point3p3c{ 6.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.8f },
            Point3p3c{ 6.0f, -2.0f, -1.0f, 0.0f, 0.0f, 0.8f }, Point3p3c{ 7.0f, -2.0f, -1.0f, 0.0f, 0.0f, 0.8f }
        };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        const DrawArraysIndirectCommand COMMANDS[ M_DRAW_ARR_IND_NUM_COMMANDS ]{ DrawArraysIndirectCommand{ 3, 1, 0, 0 },
                                                                                 DrawArraysIndirectCommand{ 3, 1, 3, 0 } };
        glBufferData( GL_DRAW_INDIRECT_BUFFER, sizeof( COMMANDS ), COMMANDS, GL_STATIC_DRAW );
    }

    void OpenGLDrawFunctionsWidget::multiDrawElements_init()
    {
        mDrawElemBuffers.create( VAO | VBO | EBO );
        mDrawElemBuffers.bind( VAO | VBO | EBO );
        const Point3p3c POINTS[]{ Point3p3c{ 6.0f, -4.0f, 0.0f, 0.0f, 0.0f, 0.6f },  Point3p3c{ 7.0f, -4.0f, 0.0f, 0.0f, 0.0f, 0.6f },
                                  Point3p3c{ 7.0f, -3.0f, 0.0f, 0.0f, 0.0f, 0.6f },  Point3p3c{ 6.0f, -3.0f, 0.0f, 0.0f, 0.0f, 0.6f },
                                  Point3p3c{ 6.0f, -4.0f, -1.0f, 0.0f, 0.0f, 0.6f }, Point3p3c{ 7.0f, -4.0f, -1.0f, 0.0f, 0.0f, 0.6f },
                                  Point3p3c{ 7.0f, -3.0f, -1.0f, 0.0f, 0.0f, 0.6f }, Point3p3c{ 6.0f, -3.0f, -1.0f, 0.0f, 0.0f, 0.6f } };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        const GLuint ELEMENTS[ M_DRAW_ELEM_NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 };
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( ELEMENTS ), ELEMENTS, GL_STATIC_DRAW );
    }

    void OpenGLDrawFunctionsWidget::multiDrawElementsBaseVertex_init()
    {
        mDrawElemBVBuffers.create( VAO | VBO | EBO );
        mDrawElemBVBuffers.bind( VAO | VBO | EBO );
        const Point3p3c POINTS[]{ Point3p3c{ 6.0f, -6.0f, 0.0f, 0.0f, 0.0f, 0.4f },  Point3p3c{ 7.0f, -6.0f, 0.0f, 0.0f, 0.0f, 0.4f },
                                  Point3p3c{ 7.0f, -5.0f, 0.0f, 0.0f, 0.0f, 0.4f },  Point3p3c{ 6.0f, -5.0f, 0.0f, 0.0f, 0.0f, 0.4f },
                                  Point3p3c{ 6.0f, -6.0f, -1.0f, 0.0f, 0.0f, 0.4f }, Point3p3c{ 7.0f, -6.0f, -1.0f, 0.0f, 0.0f, 0.4f },
                                  Point3p3c{ 7.0f, -5.0f, -1.0f, 0.0f, 0.0f, 0.4f }, Point3p3c{ 6.0f, -5.0f, -1.0f, 0.0f, 0.0f, 0.4f } };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        const GLuint ELEMENTS[ M_DRAW_ELEM_BV_NUM_ELEMENTS ]{ 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 };
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( ELEMENTS ), ELEMENTS, GL_STATIC_DRAW );
    }

    void OpenGLDrawFunctionsWidget::multiDrawElementsIndirect_init()
    {
        mDrawElemIndBuffers.create( VAO | VBO | EBO | DIBO );
        mDrawElemIndBuffers.bind( VAO | VBO | EBO | DIBO );
        const Point3p3c POINTS[]{ Point3p3c{ 6.0f, -8.0f, 0.0f, 0.0f, 0.0f, 0.25f },  Point3p3c{ 7.0f, -8.0f, 0.0f, 0.0f, 0.0f, 0.25f },
                                  Point3p3c{ 7.0f, -7.0f, 0.0f, 0.0f, 0.0f, 0.25f },  Point3p3c{ 6.0f, -7.0f, 0.0f, 0.0f, 0.0f, 0.25f },
                                  Point3p3c{ 6.0f, -8.0f, -1.0f, 0.0f, 0.0f, 0.25f }, Point3p3c{ 7.0f, -8.0f, -1.0f, 0.0f, 0.0f, 0.25f },
                                  Point3p3c{ 7.0f, -7.0f, -1.0f, 0.0f, 0.0f, 0.25f }, Point3p3c{ 6.0f, -7.0f, -1.0f, 0.0f, 0.0f, 0.25f } };
        glBufferData( GL_ARRAY_BUFFER, sizeof( POINTS ), POINTS, GL_STATIC_DRAW );
        setupVertexArrayAttribs();
        const GLuint ELEMENTS[]{ 0, 1, 2, 2, 3, 0, 4, 5, 6, 6, 7, 4 };
        glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof( ELEMENTS ), ELEMENTS, GL_STATIC_DRAW );
        const DrawElementsIndirectCommand DRAW_COMMANDS[]{ DrawElementsIndirectCommand{ 6, 1, 0, 0, 0 },
                                                           DrawElementsIndirectCommand{ 6, 1, 6, 0, 0 } };
        glBufferData( GL_DRAW_INDIRECT_BUFFER, sizeof( DRAW_COMMANDS ), DRAW_COMMANDS, GL_STATIC_DRAW );
    }

    //--------- cleanup ----------

    void OpenGLDrawFunctionsWidget::drawArrays_cleanup()
    {
        drawArrBuffers.deleteBuffers();
    }

    void OpenGLDrawFunctionsWidget::drawArraysInstanced_cleanup()
    {
        drawArrInstBuffers.deleteBuffers();
    }

    void OpenGLDrawFunctionsWidget::drawArraysIndirect_cleanup()
    {
        drawArrIndBuffers.deleteBuffers();
    }

    void OpenGLDrawFunctionsWidget::drawElements_cleanup()
    {
        drawElemBuffers.deleteBuffers();
    }

    void OpenGLDrawFunctionsWidget::drawElementsBaseVertex_cleanup()
    {
        drawElemBVBuffers.deleteBuffers();
    }

    void OpenGLDrawFunctionsWidget::drawElementsIndirect_cleanup()
    {
        drawElemIndBuffers.deleteBuffers();
    }

    void OpenGLDrawFunctionsWidget::drawElementsInstanced_cleanup()
    {
        drawElemInstBuffers.deleteBuffers();
    }

    void OpenGLDrawFunctionsWidget::drawElementsInstancedBaseVertex_cleanup()
    {
        drawElemInstBVBuffers.deleteBuffers();
    }

    void OpenGLDrawFunctionsWidget::drawRangeElements_cleanup()
    {
        drawRangeElemBuffers.deleteBuffers();
    }

    void OpenGLDrawFunctionsWidget::drawRangeElementsBaseVertex_cleanup()
    {
        drawRangeElemBVBuffers.deleteBuffers();
    }

    void OpenGLDrawFunctionsWidget::multiDrawArrays_cleanup()
    {
        mDrawArrBuffers.deleteBuffers();
    }

    void OpenGLDrawFunctionsWidget::multiDrawArraysIndirect_cleanup()
    {
        mDrawArrIndBuffers.deleteBuffers();
    }

    void OpenGLDrawFunctionsWidget::multiDrawElements_cleanup()
    {
        mDrawElemBuffers.deleteBuffers();
    }

    void OpenGLDrawFunctionsWidget::multiDrawElementsBaseVertex_cleanup()
    {
        mDrawElemBVBuffers.deleteBuffers();
    }

    void OpenGLDrawFunctionsWidget::multiDrawElementsIndirect_cleanup()
    {
        mDrawElemIndBuffers.deleteBuffers();
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

    OpenGLDrawFunctionsWidget::DrawFunctionData::DrawFunctionData( bool enabled,
                                                                   void ( OpenGLDrawFunctionsWidget::*initFunction )(),
                                                                   void ( OpenGLDrawFunctionsWidget::*drawFunction )(),
                                                                   void ( OpenGLDrawFunctionsWidget::*cleanupFunction )(),
                                                                   const QString & functionName )
        : enabled( enabled )
        , initFunction( initFunction )
        , drawFunction( drawFunction )
        , cleanupFunction( cleanupFunction )
        , functionName( functionName )
    {
    }

    OpenGLDrawFunctionsWidget::DrawFunctionData::DrawFunctionData()
        : enabled( false )
        , initFunction( nullptr )
        , drawFunction( nullptr )
        , cleanupFunction( nullptr )
        , functionName( "Unknown" )
    {
    }

} // namespace Ouquitoure
