#pragma once

#include "Apps/OpenGL/OpenGLWidgetBase"
#include "Camera"

namespace Ouquitoure
{

    class OpenGLWidgetWithCamera : public OpenGLWidgetBase
    {
        Q_OBJECT
    public:
        /**
         * @brief connects camera update signal with this widget
         */
        explicit OpenGLWidgetWithCamera( const QString & name, QWidget * parent = nullptr );

        Camera & getCamera();

        void mousePressEvent( QMouseEvent * event ) override;
        void mouseReleaseEvent( QMouseEvent * event ) override;
        void mouseMoveEvent( QMouseEvent * event ) override;
        void keyPressEvent( QKeyEvent * event ) override;
        void keyReleaseEvent( QKeyEvent * event ) override;
        bool eventFilter( QObject * watched, QEvent * event ) override;
        void resizeGL( int width, int height ) override;

    protected slots:
        void updateViewMatrixForMainProgram();
        void updateProjectionMatrixForMainProgram();

    protected:
        Camera camera;
    };

} // namespace Ouquitoure
