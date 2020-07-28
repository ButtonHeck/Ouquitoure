#pragma once

#include <qnamespace.h>

namespace Ouquitoure
{
    /**
     * @brief enumeration of the possible camera move directions
     * this also setups keybindings
     */
    enum CAMERA_MOVE_DIRECTION
    {
        FORWARD  = Qt::Key_W,
        BACKWARD = Qt::Key_S,
        RIGHT    = Qt::Key_D,
        LEFT     = Qt::Key_A,
        UP       = Qt::Key_E,
        DOWN     = Qt::Key_Shift
    };
} // namespace Ouquitoure
