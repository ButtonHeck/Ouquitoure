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
        startTimer( 1000.0f / DEFAULT_FPS );

        // explicitly define keys for movement
        keys[ FORWARD ]  = false;
        keys[ LEFT ]     = false;
        keys[ BACKWARD ] = false;
        keys[ RIGHT ]    = false;
        keys[ UP ]       = false;
        keys[ DOWN ]     = false;
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
        int deltaX     = x - lastMousePos.x;
        int deltaY     = lastMousePos.y - y;
        lastMousePos.x = x;
        lastMousePos.y = y;
        yaw += deltaX * mouseSensitivity;
        pitch += deltaY * mouseSensitivity;
        pitch = glm::clamp( pitch, MIN_PITCH, MAX_PITCH );
        updateViewDirectionVectors();
        emit viewChanged();
    }

    void Camera::updateLastPos( int x, int y )
    {
        lastMousePos.x = x;
        lastMousePos.y = y;
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

        for( int & key: keys.keys() )
        {
            if( keys[ key ] )
            {
                move( (CAMERA_MOVE_DIRECTION)key, moveSensitivity );
            }
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
