#include "KeybindingsManager"

#include <QKeySequence>

namespace Ouquitoure
{

    KeybindingsManager::KeybindingsManager()
        : cameraKeys( CAMERA_MOVE_DIRECTION::NUM_DIRECTIONS )
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
        cameraKeys[ moveDirection ] = newKey;
    }

    QString KeybindingsManager::getStringRepresentation( Qt::Key key ) const
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

} // namespace Ouquitoure
