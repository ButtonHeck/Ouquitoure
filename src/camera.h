#pragma once

#include "CameraMoveDirection"

#include <QObject>
#include <QMap>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

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
        constexpr static float DEFAULT_FPS               = 60.0f;

    public:
        /// @brief sets initial position, view angles and controls keybindings
        Camera( float x, float y, float z, float yaw = -90.0f, float pitch = 0.0f );

        /// @brief get view matrix for the current camera setup
        glm::mat4 getViewMatrix() const;

        /// @brief set field of view (in degrees)
        void setFov( float fov ) noexcept;

        /// @brief get current field of view value (in degrees)
        float getFov() const noexcept;

        /// @brief record key press/release event
        void processKeyboardInput( int keyCode, bool isPressed );

        /// @brief process mouse move event (x,y) and update view vectors
        void processMouseMove( int x, int y );

        /// @brief register new x and y values for last position
        void updateLastPos( int x, int y );

        /// @brief sets position coordinates
        void setPosition( float x, float y, float z );

    signals:
        /// @brief use this signal in case position or view vectors were changed
        void viewChanged();

    private:
        /// @brief processes input events for camera for each update
        void timerEvent( QTimerEvent * event ) override;

        /// @brief updates position of the camera
        void move( CAMERA_MOVE_DIRECTION direction, float velocity = 1.0f );

        /// @brief updates front, right and up vectors based on current yaw and pitch angles
        void updateViewDirectionVectors();

    private:
        // Position
        glm::vec3  position;
        glm::ivec2 lastMousePos{ 0, 0 };

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
