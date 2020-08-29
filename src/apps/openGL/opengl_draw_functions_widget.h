#pragma once

#include "Apps/OpenGL/OpenGLWidgetWithCamera"
#include "Utils/BufferCollection"

#include <unordered_map>

namespace Ouquitoure
{

    /**
     * @brief OpenGL draw functions view widget class
     */
    class OpenGLDrawFunctionsWidget : public OpenGLWidgetWithCamera
    {
        Q_OBJECT
    public:
        enum DRAW_FUNCTIONS
        {
            DRAW_ARRAYS = 0,
            DRAW_ARRAYS_INSTANCED,
            DRAW_ARRAYS_INSTANCED_BASE_INSTANCE,
            DRAW_ARRAYS_INDIRECT,
            DRAW_ELEMENTS,
            DRAW_ELEMENTS_BASE_VERTEX,
            DRAW_ELEMENTS_INDIRECT,
            DRAW_ELEMENTS_INSTANCED,
            DRAW_ELEMENTS_INSTANCED_BASE_INSTANCE,
            DRAW_ELEMENTS_INSTANCED_BASE_VERTEX,
            DRAW_ELEMENTS_INSTANCED_BASE_VERTEX_BASE_INSTANCE,
            DRAW_RANGE_ELEMENTS,
            DRAW_RANGE_ELEMENTS_BASE_VERTEX,
            MULTI_DRAW_ARRAYS,
            MULTI_DRAW_ARRAYS_INDIRECT,
            MULTI_DRAW_ELEMENTS,
            MULTI_DRAW_ELEMENTS_BASE_VERTEX,
            MULTI_DRAW_ELEMENTS_INDIRECT,
            NUM_FUNCTIONS
        };

    public:
        explicit OpenGLDrawFunctionsWidget( const QString & name, QWidget * parent = nullptr );
        ~OpenGLDrawFunctionsWidget();

        QString getDrawFunctionName( DRAW_FUNCTIONS functionCode );
        void    initializeGL() override;
        void    paintGL() override;

    public slots:
        void setFunctionEnabled( bool enabled );

    protected:
        void initializeOpenGLObjects() override;
        void initializeOpenGLShaders() override;
        void cleanup() override;

    private:
        // for paintGL
        void drawArrays();
        void drawArraysInstanced();
        void drawArraysIndirect();
        void drawElements();
        void drawElementsBaseVertex();
        void drawElementsIndirect();
        void drawElementsInstanced();
        void drawElementsInstancedBaseVertex();
        void drawRangeElements();
        void drawRangeElementsBaseVertex();
        void multiDrawArrays();
        void multiDrawArraysIndirect();
        void multiDrawElements();
        void multiDrawElementsBaseVertex();
        void multiDrawElementsIndirect();

        // initialization
        void drawArrays_init();
        void drawArraysInstanced_init();
        void drawArraysIndirect_init();
        void drawElements_init();
        void drawElementsBaseVertex_init();
        void drawElementsIndirect_init();
        void drawElementsInstanced_init();
        void drawElementsInstancedBaseVertex_init();
        void drawRangeElements_init();
        void drawRangeElementsBaseVertex_init();
        void multiDrawArrays_init();
        void multiDrawArraysIndirect_init();
        void multiDrawElements_init();
        void multiDrawElementsBaseVertex_init();
        void multiDrawElementsIndirect_init();

        // cleanup
        void drawArrays_cleanup();
        void drawArraysInstanced_cleanup();
        void drawArraysIndirect_cleanup();
        void drawElements_cleanup();
        void drawElementsBaseVertex_cleanup();
        void drawElementsIndirect_cleanup();
        void drawElementsInstanced_cleanup();
        void drawElementsInstancedBaseVertex_cleanup();
        void drawRangeElements_cleanup();
        void drawRangeElementsBaseVertex_cleanup();
        void multiDrawArrays_cleanup();
        void multiDrawArraysIndirect_cleanup();
        void multiDrawElements_cleanup();
        void multiDrawElementsBaseVertex_cleanup();
        void multiDrawElementsIndirect_cleanup();

        // utility functions
        void setupVertexArrayAttribs();
        void setupVertexArrayInstancedAttribs();

    private:
        // glDrawArrays
        BufferCollection     drawArrBuffers;
        constexpr static int DRAW_ARR_NUM_POINTS = 3;

        // glDrawArraysInstanced + glDrawArraysInstancedBaseInstance
        BufferCollection     drawArrInstBuffers;
        constexpr static int DRAW_ARR_INST_NUM_POINTS    = 3;
        constexpr static int DRAW_ARR_INST_NUM_INSTANCES = 4;

        // glDrawArraysIndirect
        BufferCollection     drawArrIndBuffers;
        constexpr static int DRAW_ARR_IND_NUM_POINTS    = 3;
        constexpr static int DRAW_ARR_IND_NUM_INSTANCES = 2;
        typedef struct
        {
            GLuint count;
            GLuint primCount;
            GLuint first;
            GLuint baseInstance;
        } DrawArraysIndirectCommand;

        // glDrawElements
        BufferCollection     drawElemBuffers;
        constexpr static int DRAW_ELEM_NUM_ELEMENTS = 6;

        // glDrawElementsBaseVertex
        BufferCollection     drawElemBVBuffers;
        constexpr static int DRAW_ELEM_BV_NUM_POINTS   = 8;
        constexpr static int DRAW_ELEM_BV_NUM_ELEMENTS = 6;

        // glDrawElementsIndirect
        BufferCollection drawElemIndBuffers;
        typedef struct
        {
            GLuint count;
            GLuint primCount;
            GLuint firstIndex;
            GLuint baseVertex;
            GLuint baseInstance;
        } DrawElementsIndirectCommand;

        // glDrawElementsInstanced + glDrawElementsInstancedBaseInstance
        BufferCollection     drawElemInstBuffers;
        constexpr static int DRAW_ELEM_INST_NUM_ELEMENTS  = 6;
        constexpr static int DRAW_ELEM_INST_NUM_INSTANCES = 4;

        // glDrawElementsInstancedBaseVertex + glDrawElementsInstancedBaseVertexBaseInstance
        BufferCollection     drawElemInstBVBuffers;
        constexpr static int DRAW_ELEM_INST_BV_NUM_ELEMENTS  = 6;
        constexpr static int DRAW_ELEM_INST_BV_NUM_INSTANCES = 3;

        // glDrawRangeElements
        BufferCollection     drawRangeElemBuffers;
        constexpr static int DRAW_RANGE_ELEM_NUM_ELEMENTS = 6;

        // glDrawRangeElementsBaseVertex
        BufferCollection     drawRangeElemBVBuffers;
        constexpr static int DRAW_RANGE_ELEM_BV_NUM_ELEMENTS = 6;

        // glMultiDrawArrays
        BufferCollection     mDrawArrBuffers;
        constexpr static int M_DRAW_ARR_NUM_POINTS = 6;

        // glMultiDrawArraysIndirect
        BufferCollection     mDrawArrIndBuffers;
        constexpr static int M_DRAW_ARR_IND_NUM_COMMANDS = 2;

        // glMultiDrawElements
        BufferCollection     mDrawElemBuffers;
        constexpr static int M_DRAW_ELEM_NUM_ELEMENTS = 12;

        // glMultiDrawElementsBaseVertex
        BufferCollection     mDrawElemBVBuffers;
        constexpr static int M_DRAW_ELEM_BV_NUM_ELEMENTS = 12;

        // glMultiDrawElementsIndirect
        BufferCollection mDrawElemIndBuffers;

        /**
         * @brief utility struct containing init, draw and cleanup function pointers, name and enabled state of the draw function
         */
        struct DrawFunctionData
        {
            DrawFunctionData( bool enabled,
                              void ( OpenGLDrawFunctionsWidget::*initFunction )(),
                              void ( OpenGLDrawFunctionsWidget::*drawFunction )(),
                              void ( OpenGLDrawFunctionsWidget::*cleanupFunction )(),
                              const QString & functionName );
            DrawFunctionData();
            bool enabled                                           = false;
            void ( OpenGLDrawFunctionsWidget::*initFunction )()    = nullptr;
            void ( OpenGLDrawFunctionsWidget::*drawFunction )()    = nullptr;
            void ( OpenGLDrawFunctionsWidget::*cleanupFunction )() = nullptr;
            QString functionName;
        };

        std::unordered_map<DRAW_FUNCTIONS, DrawFunctionData> allDrawFunctions;
    };

} // namespace Ouquitoure
