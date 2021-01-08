#pragma once

#include <CameraMoveDirection>

#include <QObject>
#include <parallel_hashmap/phmap.h>

namespace Ouquitoure
{
    /**
     * @brief The manager of all the key bindings of the Ouquitoure
     */
    class KeybindingsManager : public QObject
    {
        Q_OBJECT
    public:
        KeybindingsManager();

        Qt::Key getCameraControlsKey( CAMERA_MOVE_DIRECTION moveDirection ) const;
        void    setCameraControlsKey( CAMERA_MOVE_DIRECTION moveDirection, Qt::Key newKey );

    signals:
        void cameraControlsChanged();

    private:
        phmap::flat_hash_map<CAMERA_MOVE_DIRECTION, Qt::Key> cameraKeys;
    };
} // namespace Ouquitoure
