#pragma once

#include <QObject>
#include <QMap>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

#include "CameraMoveDirection"

namespace Ouquitoure
{

    /**
     * @brief Custom camera class
     */
    class Camera : public QObject
    {
        Q_OBJECT
    public:
        constexpr static float DEFAULT_FOV               = 60.0f;
        constexpr static float DEFAULT_MOVE_SENSITIVITY  = 0.05f;
        constexpr static float DEFAULT_MOUSE_SENSITIVITY = 0.25f;
        constexpr static float MAX_PITCH                 = 89.0f;
        constexpr static float MIN_PITCH                 = -89.0f;

    public:
        Camera( float x, float y, float z, float yaw = -90.0f, float pitch = 0.0f );

        glm::mat4 getViewMatrix() const;
        void      setFov( float fov ) noexcept;
        float     getFov() const noexcept;
        void      processKeyboardInput( int keyCode, bool isPressed );
        void      processMouseMove( int x, int y );
        void      updateLastPos( int x, int y );

    signals:
        void viewChanged();

    private:
        void timerEvent( QTimerEvent * event ) override;
        void move( CAMERA_MOVE_DIRECTION direction, float value = 1.0f );
        void updateViewDirectionVectors();
        void clampPitch();

    private:
        // Position
        glm::vec3 position;
        int       lastX = 0;
        int       lastY = 0;

        // View
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;
        float     yaw;
        float     pitch;

        // Common
        float fov              = DEFAULT_FOV;
        float moveSensitivity  = DEFAULT_MOVE_SENSITIVITY;
        float mouseSensitivity = DEFAULT_MOUSE_SENSITIVITY;

        // Key map
        QMap<int, bool> keys;
    };

} // namespace Ouquitoure
