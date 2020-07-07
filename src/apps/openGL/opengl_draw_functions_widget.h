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
        GLuint               drawArraysVao;
        GLuint               drawArraysVbo;
        constexpr static int DRAW_ARRAYS_NUM_POINTS = 3;

        // glDrawArraysInstanced
        GLuint               drawArraysInstancedVao;
        GLuint               drawArraysInstancedVbo;
        GLuint               drawArraysInstancedVboInstanced;
        constexpr static int DRAW_ARRAYS_INSTANCED_NUM_POINTS    = 3;
        constexpr static int DRAW_ARRAYS_INSTANCED_NUM_INSTANCES = 4;

        // glDrawArraysIndirect
        GLuint               drawArraysIndirectVao;
        GLuint               drawArraysIndirectVbo;
        GLuint               drawArraysIndirectVboInstanced;
        GLuint               drawArraysIndirectDibo;
        constexpr static int DRAW_ARRAYS_INDIRECT_NUM_POINTS    = 3;
        constexpr static int DRAW_ARRAYS_INDIRECT_NUM_INSTANCES = 2;
        typedef struct
        {
            GLuint count;
            GLuint primCount;
            GLuint first;
            GLuint baseInstance;
        } DrawArraysIndirectCommand;

        // glDrawElements
        GLuint               drawElementsVao;
        GLuint               drawElementsVbo;
        GLuint               drawElementsEbo;
        constexpr static int DRAW_ELEMENTS_NUM_POINTS   = 4;
        constexpr static int DRAW_ELEMENTS_NUM_ELEMENTS = 6;
    };

} // namespace Ouquitoure
