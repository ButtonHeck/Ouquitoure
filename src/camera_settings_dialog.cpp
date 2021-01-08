#include "CameraSettingsDialog"
#include "Log"
#include "KeybindingsManager"

namespace Ouquitoure
{

    CameraSettingsDialog::CameraSettingsDialog( const KeybindingsManager & keybindingsManager, QWidget * parent )
        : QDialog( parent )
        , ui()
        , keybindingsManager( keybindingsManager )
    {
        ui.setupUi( this );
        ui.moveForwardEdit->setText( keybindingsManager.getStringRepresentation( keybindingsManager.getCameraControlsKey( FORWARD ) ) );
        ui.moveBackwardEdit->setText( keybindingsManager.getStringRepresentation( keybindingsManager.getCameraControlsKey( BACKWARD ) ) );
        ui.moveLeftEdit->setText( keybindingsManager.getStringRepresentation( keybindingsManager.getCameraControlsKey( LEFT ) ) );
        ui.moveRightEdit->setText( keybindingsManager.getStringRepresentation( keybindingsManager.getCameraControlsKey( RIGHT ) ) );
        ui.moveUpEdit->setText( keybindingsManager.getStringRepresentation( keybindingsManager.getCameraControlsKey( UP ) ) );
        ui.moveDownEdit->setText( keybindingsManager.getStringRepresentation( keybindingsManager.getCameraControlsKey( DOWN ) ) );
    }

#ifdef QT_DEBUG
    CameraSettingsDialog::~CameraSettingsDialog()
    {
        OQ_LOG_DEBUG << "Camera settings dialog dtor";
    }
#endif

} // namespace Ouquitoure
