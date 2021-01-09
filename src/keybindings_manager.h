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
        static QString getStringRepresentation( Qt::Key key );

    public:
        KeybindingsManager();

        Qt::Key getCameraControlsKey( CAMERA_MOVE_DIRECTION moveDirection ) const;
        void    setCameraControlsKey( CAMERA_MOVE_DIRECTION moveDirection, Qt::Key newKey );
        bool    eventFilter( QObject * watched, QEvent * event ) override;

    public slots:
        void prepareRecordCameraControls();

    signals:
        void cameraControlsChanged();

    private:
        phmap::flat_hash_map<CAMERA_MOVE_DIRECTION, Qt::Key> cameraKeys;
        CAMERA_MOVE_DIRECTION                                cameraMoveDirectionToRecord;
    };
} // namespace Ouquitoure
