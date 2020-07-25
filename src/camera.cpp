#include "Camera"
#include "Log"

#include <glm/gtc/matrix_transform.hpp>

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
        keys[ Qt::Key_E ]     = false;
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
        yaw += deltaX * mouseSensitivity;
        pitch += deltaY * mouseSensitivity;
        clampPitch();
        updateViewDirectionVectors();
        emit viewChanged();
    }

    void Camera::updateLastPos( int x, int y )
    {
        lastX = x;
        lastY = y;
    }

    void Camera::setPosition( float x, float y, float z )
    {
        position.x = x;
        position.y = y;
        position.z = z;
        emit viewChanged();
    }

    void Camera::timerEvent( QTimerEvent * event )
    {
        Q_UNUSED( event );

        // Forward / Backward
        if( keys[ Qt::Key_W ] )
        {
            move( FORWARD, moveSensitivity );
        }
        if( keys[ Qt::Key_S ] )
        {
            move( BACKWARD, moveSensitivity );
        }

        // Left / Right
        if( keys[ Qt::Key_A ] )
        {
            move( LEFT, moveSensitivity );
        }
        if( keys[ Qt::Key_D ] )
        {
            move( RIGHT, moveSensitivity );
        }

        // Up / Down
        if( keys[ Qt::Key_E ] )
        {
            move( UP, moveSensitivity );
        }
        if( keys[ Qt::Key_Shift ] )
        {
            move( DOWN, moveSensitivity );
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

    void Camera::clampPitch()
    {
        pitch = glm::clamp( pitch, MIN_PITCH, MAX_PITCH );
    }

} // namespace Ouquitoure
