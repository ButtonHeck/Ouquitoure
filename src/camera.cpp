#include "Camera"

#include <glm/gtc/matrix_transform.hpp>

#include "Log"

namespace Ouquitoure
{

    Camera::Camera( float x, float y, float z, float yaw, float pitch )
        : position( x, y, z )
        , worldUp( 0.0f, 1.0f, 0.0f )
        , yaw( yaw )
        , pitch( pitch )
    {
        updateViewDirectionVectors();
        startTimer( 1000.0f / 60.0f );

        // explicitly define keys for movement
        keys[ Qt::Key_W ]     = false;
        keys[ Qt::Key_A ]     = false;
        keys[ Qt::Key_S ]     = false;
        keys[ Qt::Key_D ]     = false;
        keys[ Qt::Key_Space ] = false;
        keys[ Qt::Key_Shift ] = false;
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

    void Camera::processKeyboardInput( int keyCode, bool isPressed )
    {
        keys[ keyCode ] = isPressed;
    }

    void Camera::processMouseMove( int x, int y )
    {
        int deltaX = x - lastX;
        int deltaY = lastY - y;
        lastX      = x;
        lastY      = y;
        yaw += deltaX * 0.25f;
        pitch += deltaY * 0.25;
        if( pitch >= 89.0f )
        {
            pitch = 89.0f;
        }
        if( pitch <= -89.0f )
        {
            pitch = -89.0f;
        }
        updateViewDirectionVectors();
        emit viewChanged();
    }

    void Camera::updateLastPos( int x, int y )
    {
        lastX = x;
        lastY = y;
    }

    void Camera::timerEvent( QTimerEvent * event )
    {
        // Forward / Backward
        if( keys[ Qt::Key_W ] )
        {
            move( FORWARD, 0.05f );
        }
        if( keys[ Qt::Key_S ] )
        {
            move( BACKWARD, 0.05f );
        }

        // Left / Right
        if( keys[ Qt::Key_A ] )
        {
            move( LEFT, 0.05f );
        }
        if( keys[ Qt::Key_D ] )
        {
            move( RIGHT, 0.05f );
        }

        // Up / Down
        if( keys[ Qt::Key_Space ] )
        {
            move( UP, 0.05f );
        }
        if( keys[ Qt::Key_Shift ] )
        {
            move( DOWN, 0.05f );
        }
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

    /**
     * @brief updates front, right and up vectors based on current yaw and pitch angles
     */
    void Camera::updateViewDirectionVectors()
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
