#include "Camera"

#include <glm/gtc/matrix_transform.hpp>

namespace Ouquitoure
{

    Camera::Camera( float x, float y, float z, float yaw, float pitch )
        : position( x, y, z )
        , worldUp( 0.0f, 1.0f, 0.0f )
        , yaw( yaw )
        , pitch( pitch )
    {
        updateVectors();
    }

    glm::mat4 Camera::getViewMatrix() const
    {
        return glm::lookAt( position, position + front, worldUp );
    }

    void Camera::setFov( float fov ) noexcept
    {
        this->fov = fov;
    }

    float Camera::getFov() const noexcept
    {
        return fov;
    }

    void Camera::move( CAMERA_MOVE_DIRECTION direction, float value )
    {
        // Forward / Backward
        if( direction == FORWARD )
        {
            position += front * value;
        }
        else if( direction == BACKWARD )
        {
            position -= front * value;
        }

        // Left / Right
        if( direction == LEFT )
        {
            position -= right * value;
        }
        else if( direction == RIGHT )
        {
            position += right * value;
        }

        // Up / Down
        if( direction == UP )
        {
            position += worldUp * value;
        }
        else if( direction == DOWN )
        {
            position -= worldUp * value;
        }

        emit viewChanged();
    }

    void Camera::move( int keyCode, float value )
    {
        // Forward / Backward
        if( keyCode == Qt::Key_W )
        {
            move( FORWARD, value );
        }
        else if( keyCode == Qt::Key_S )
        {
            move( BACKWARD, value );
        }

        // Left / Right
        if( keyCode == Qt::Key_A )
        {
            move( LEFT, value );
        }
        else if( keyCode == Qt::Key_D )
        {
            move( RIGHT, value );
        }

        // Up / Down
        if( keyCode == Qt::Key_Space )
        {
            move( UP, value );
        }
        else if( keyCode == Qt::Key_Shift )
        {
            move( DOWN, value );
        }
    }

    /**
     * @brief updates front, right and up vectors based on current yaw and pitch angles
     */
    void Camera::updateVectors()
    {
        float     x = std::cos( glm::radians( yaw ) ) * std::cos( glm::radians( pitch ) );
        float     y = std::sin( glm::radians( pitch ) );
        float     z = std::sin( glm::radians( yaw ) ) * std::cos( glm::radians( pitch ) );
        glm::vec3 newFront( x, y, z );
        front = glm::normalize( newFront );
        right = glm::normalize( glm::cross( front, worldUp ) );
        up    = glm::normalize( glm::cross( right, front ) );
    }

} // namespace Ouquitoure
