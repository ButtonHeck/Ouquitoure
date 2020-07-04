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

    private:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;
        float     yaw;
        float     pitch;

        // View options
        float fov   = 60.0f;
        int   lastX = 0;
        int   lastY = 0;

        // Key map
        QMap<int, bool> keys;
    };

} // namespace Ouquitoure
