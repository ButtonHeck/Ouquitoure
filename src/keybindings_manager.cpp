#include "KeybindingsManager"

#include <QKeySequence>
#include <QKeyEvent>

namespace Ouquitoure
{

    KeybindingsManager::KeybindingsManager()
        : cameraKeys( CAMERA_MOVE_DIRECTION::NUM_DIRECTIONS )
        , cameraMoveDirectionToRecord( CAMERA_MOVE_DIRECTION::EMPTY )
    {
        cameraKeys[ FORWARD ]  = Qt::Key_W;
        cameraKeys[ BACKWARD ] = Qt::Key_S;
        cameraKeys[ RIGHT ]    = Qt::Key_D;
        cameraKeys[ LEFT ]     = Qt::Key_A;
        cameraKeys[ UP ]       = Qt::Key_E;
        cameraKeys[ DOWN ]     = Qt::Key_Shift;
    }

    Qt::Key KeybindingsManager::getCameraControlsKey( CAMERA_MOVE_DIRECTION moveDirection ) const
    {
        return cameraKeys.at( moveDirection );
    }

    void KeybindingsManager::setCameraControlsKey( CAMERA_MOVE_DIRECTION moveDirection, Qt::Key newKey )
    {
        if( newKey != Qt::Key_Escape )
        {
            cameraKeys[ moveDirection ] = newKey;
        }
        emit cameraControlsChanged();
    }

    QString KeybindingsManager::getStringRepresentation( Qt::Key key )
    {
        if( key == Qt::Key_Shift )
        {
            return "Shift";
        }
        else if( key == Qt::Key_Control )
        {
            return "Ctrl";
        }
        else if( key == Qt::Key_Alt )
        {
            return "Alt";
        }
        else
        {
            return QKeySequence( key ).toString();
        }
    }

    bool KeybindingsManager::eventFilter( QObject * watched, QEvent * event )
    {
        if( event->type() == QEvent::KeyPress )
        {
            QKeyEvent * key = static_cast<QKeyEvent *>( event );
            setCameraControlsKey( cameraMoveDirectionToRecord, Qt::Key( key->key() ) );
            // ignoring any other key records until next record
            cameraMoveDirectionToRecord = CAMERA_MOVE_DIRECTION::EMPTY;
        }
        return QObject::eventFilter( watched, event );
    }

    void KeybindingsManager::prepareRecordCameraControls()
    {
        if( sender()->objectName().contains( "Forward", Qt::CaseInsensitive ) )
        {
            cameraMoveDirectionToRecord = FORWARD;
        }
        else if( sender()->objectName().contains( "Backward", Qt::CaseInsensitive ) )
        {
            cameraMoveDirectionToRecord = BACKWARD;
        }
        else if( sender()->objectName().contains( "Left", Qt::CaseInsensitive ) )
        {
            cameraMoveDirectionToRecord = LEFT;
        }
        else if( sender()->objectName().contains( "Right", Qt::CaseInsensitive ) )
        {
            cameraMoveDirectionToRecord = RIGHT;
        }
        else if( sender()->objectName().contains( "Up", Qt::CaseInsensitive ) )
        {
            cameraMoveDirectionToRecord = UP;
        }
        else if( sender()->objectName().contains( "Down", Qt::CaseInsensitive ) )
        {
            cameraMoveDirectionToRecord = DOWN;
        }
    }

} // namespace Ouquitoure
