#pragma once

#include "Apps/OpenGL/OpenGLWidgetBase"
#include "Camera"

namespace Ouquitoure
{

    class OpenGLWidgetWithCamera : public OpenGLWidgetBase
    {
    public:
        explicit OpenGLWidgetWithCamera( const QString & name, QWidget * parent = nullptr );
        virtual ~OpenGLWidgetWithCamera() = default;

        Camera & getCamera();

        void mousePressEvent( QMouseEvent * event ) override;
        void mouseReleaseEvent( QMouseEvent * event ) override;
        void mouseMoveEvent( QMouseEvent * event ) override;
        void keyPressEvent( QKeyEvent * event ) override;
        void keyReleaseEvent( QKeyEvent * event ) override;
        bool eventFilter( QObject * watched, QEvent * event ) override;

    protected:
        Camera camera;
    };

} // namespace Ouquitoure
