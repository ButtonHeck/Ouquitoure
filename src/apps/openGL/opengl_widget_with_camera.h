#pragma once

#include "Apps/OpenGL/OpenGLWidgetBase"
#include "Camera"

namespace Ouquitoure
{
    class KeybindingsManager;

    /**
     * @brief Base class for all OpenGL view widgets that use virtual camera
     */
    class OpenGLWidgetWithCamera : public OpenGLWidgetBase
    {
        Q_OBJECT
    public:
        /// @brief besides constructing, connects camera update signal with this widget
        OpenGLWidgetWithCamera( const QString & name, const KeybindingsManager & keybindingsManager, QWidget * parent = nullptr );

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
        void updateCameraControls();

    protected:
        Camera camera;

        /// @brief reference to keybindings manager needs to update camera settings
        const KeybindingsManager & keybindingsManager;
    };

} // namespace Ouquitoure
