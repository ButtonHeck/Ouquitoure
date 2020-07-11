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
        // glDrawArrays
        GLuint               drawArr_Vao;
        GLuint               drawArr_Vbo;
        constexpr static int DRAW_ARR_NUM_POINTS = 3;

        // glDrawArraysInstanced
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
        constexpr static int DRAW_ELEM_NUM_POINTS   = 4;
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
    };

} // namespace Ouquitoure
