#pragma once

#include "Apps/OpenGL/OpenGLWidgetWithCamera"

namespace Ouquitoure
{

    /**
     * @brief OpenGL draw functions view widget class
     */
    class OpenGLDrawFunctionsWidget : public OpenGLWidgetWithCamera
    {
        Q_OBJECT
    public:
        explicit OpenGLDrawFunctionsWidget( const QString & name, QWidget * parent = nullptr );
        ~OpenGLDrawFunctionsWidget();

        void initializeGL() override;
        void paintGL() override;

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

        // utility functions
        void setupVertexArrayAttribs();
        void setupVertexArrayInstancedAttribs();
        void openGLBufferCleanup( GLuint & bufferObject );
        void openGLVertexArrayCleanup( GLuint & vertexArray );

    private:
        // glDrawArrays
        GLuint               drawArr_Vao;
        GLuint               drawArr_Vbo;
        constexpr static int DRAW_ARR_NUM_POINTS = 3;

        // glDrawArraysInstanced + glDrawArraysInstancedBaseInstance
        GLuint               drawArrInst_Vao;
        GLuint               drawArrInst_Vbo;
        GLuint               drawArrInst_VboInst;
        constexpr static int DRAW_ARR_INST_NUM_POINTS    = 3;
        constexpr static int DRAW_ARR_INST_NUM_INSTANCES = 4;

        // glDrawArraysIndirect
        GLuint               drawArrInd_Vao;
        GLuint               drawArrInd_Vbo;
        GLuint               drawArrInd_VboInst;
        GLuint               drawArrInd_Dibo;
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
        GLuint               drawElem_Vao;
        GLuint               drawElem_Vbo;
        GLuint               drawElem_Ebo;
        constexpr static int DRAW_ELEM_NUM_ELEMENTS = 6;

        // glDrawElementsBaseVertex
        GLuint               drawElemBV_Vao;
        GLuint               drawElemBV_Vbo;
        GLuint               drawElemBV_Ebo;
        constexpr static int DRAW_ELEM_BV_NUM_POINTS   = 8;
        constexpr static int DRAW_ELEM_BV_NUM_ELEMENTS = 6;

        // glDrawElementsIndirect
        GLuint drawElemInd_Vao;
        GLuint drawElemInd_Vbo;
        GLuint drawElemInd_Ebo;
        GLuint drawElemInd_Dibo;
        typedef struct
        {
            GLuint count;
            GLuint primCount;
            GLuint firstIndex;
            GLuint baseVertex;
            GLuint baseInstance;
        } DrawElementsIndirectCommand;

        // glDrawElementsInstanced + glDrawElementsInstancedBaseInstance
        GLuint               drawElemInst_Vao;
        GLuint               drawElemInst_Vbo;
        GLuint               drawElemInst_VboInst;
        GLuint               drawElemInst_Ebo;
        constexpr static int DRAW_ELEM_INST_NUM_ELEMENTS  = 6;
        constexpr static int DRAW_ELEM_INST_NUM_INSTANCES = 4;

        // glDrawElementsInstancedBaseVertex + glDrawElementsInstancedBaseVertexBaseInstance
        GLuint               drawElemInstBV_Vao;
        GLuint               drawElemInstBV_Vbo;
        GLuint               drawElemInstBV_VboInst;
        GLuint               drawElemInstBV_Ebo;
        constexpr static int DRAW_ELEM_INST_BV_NUM_ELEMENTS  = 6;
        constexpr static int DRAW_ELEM_INST_BV_NUM_INSTANCES = 3;

        // glDrawRangeElements
        GLuint               drawRangeElem_Vao;
        GLuint               drawRangeElem_Vbo;
        GLuint               drawRangeElem_Ebo;
        constexpr static int DRAW_RANGE_ELEM_NUM_ELEMENTS = 6;

        // glDrawRangeElementsBaseVertex
        GLuint               drawRangeElemBV_Vao;
        GLuint               drawRangeElemBV_Vbo;
        GLuint               drawRangeElemBV_Ebo;
        constexpr static int DRAW_RANGE_ELEM_BV_NUM_ELEMENTS = 6;

        // glMultiDrawArrays
        GLuint               mDrawArr_Vao;
        GLuint               mDrawArr_Vbo;
        constexpr static int M_DRAW_ARR_NUM_POINTS = 6;

        // glMultiDrawArraysIndirect
        GLuint               mDrawArrInd_Vao;
        GLuint               mDrawArrInd_Vbo;
        GLuint               mDrawArrInd_Dibo;
        constexpr static int M_DRAW_ARR_IND_NUM_COMMANDS = 2;

        // glMultiDrawElements
        GLuint mDrawElem_Vao;
        GLuint mDrawElem_Vbo;
        GLuint mDrawElem_Ebo;
    };

} // namespace Ouquitoure
