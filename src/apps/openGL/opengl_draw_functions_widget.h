#pragma once

#include "Apps/OpenGL/OpenGLWidgetBase"
#include "Camera"

namespace Ouquitoure
{

    /**
     * @brief OpenGL draw functions view widget class
     */
    class OpenGLDrawFunctionsWidget : public OpenGLWidgetBase
    {
        Q_OBJECT
    public:
        explicit OpenGLDrawFunctionsWidget( const QString & name, QWidget * parent = nullptr );
        ~OpenGLDrawFunctionsWidget();

        Camera & getCamera();

        void initializeGL() override;
        void paintGL() override;
        void resizeGL( int width, int height ) override;
        void mousePressEvent( QMouseEvent * event ) override;
        void mouseReleaseEvent( QMouseEvent * event ) override;
        void mouseMoveEvent( QMouseEvent * event ) override;
        bool eventFilter( QObject * watched, QEvent * event ) override;
        void keyPressEvent( QKeyEvent * event ) override;

    protected:
        void initializeOpenGLObjects() override;
        void initializeOpenGLShaders() override;
        void cleanup() override;

    private slots:
        void updateViewMatrix();

    private:
        Camera camera;

        // glDrawArrays
        GLuint               drawArraysVao;
        GLuint               drawArraysVbo;
        constexpr static int DRAW_ARRAYS_NUM_POINTS = 3;

        // glDrawElements
        GLuint               drawElementsVao;
        GLuint               drawElementsVbo;
        GLuint               drawElementsEbo;
        constexpr static int DRAW_ELEMENTS_NUM_POINTS   = 4;
        constexpr static int DRAW_ELEMENTS_NUM_ELEMENTS = 6;
    };

} // namespace Ouquitoure
