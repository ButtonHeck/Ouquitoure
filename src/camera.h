#pragma once

#include <QObject>
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
        void      move( CAMERA_MOVE_DIRECTION direction, float value = 1.0f );
        void      move( int keyCode, float value = 1.0f );

    signals:
        void viewChanged();

    private:
        void updateVectors();

    private:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;
        float     yaw;
        float     pitch;

        // View options
        float fov = 60.0f;
    };

} // namespace Ouquitoure
