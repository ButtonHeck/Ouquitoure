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
        connect( &keybindingsManager, SIGNAL( cameraControlsChanged() ), this, SLOT( updateControlKeysView() ) );
        connect( &keybindingsManager, SIGNAL( cameraControlsChanged() ), this, SLOT( enableRecordButtons() ) );
        connect( &keybindingsManager, SIGNAL( cameraControlsChanged() ), this, SLOT( clearRecordButtonsFocus() ) );

        recButtons.addButton( ui.moveForwardRecButton );
        recButtons.addButton( ui.moveBackwardRecButton );
        recButtons.addButton( ui.moveLeftRecButton );
        recButtons.addButton( ui.moveRightRecButton );
        recButtons.addButton( ui.moveUpRecButton );
        recButtons.addButton( ui.moveDownRecButton );

        // connect rec buttons to activate recording
        for( auto * recButton: recButtons.buttons() )
        {
            connect( recButton, SIGNAL( clicked() ), &keybindingsManager, SLOT( prepareRecordCameraControls() ) );
        }

        // connect rec buttons to disable all other buttons
        for( auto * recButton: recButtons.buttons() )
        {
            connect( recButton, SIGNAL( clicked() ), this, SLOT( disableRecordButtons() ) );
        }

        // need this to capture key press events
        installEventFilter( (QObject *)&keybindingsManager );
    }

#ifdef QT_DEBUG
    CameraSettingsDialog::~CameraSettingsDialog()
    {
        OQ_LOG_DEBUG << "Camera settings dialog dtor";
    }
#endif

    void CameraSettingsDialog::updateControlKeysView()
    {
        ui.moveForwardEdit->setText( keybindingsManager.getStringRepresentation( keybindingsManager.getCameraControlsKey( FORWARD ) ) );
        ui.moveBackwardEdit->setText( keybindingsManager.getStringRepresentation( keybindingsManager.getCameraControlsKey( BACKWARD ) ) );
        ui.moveLeftEdit->setText( keybindingsManager.getStringRepresentation( keybindingsManager.getCameraControlsKey( LEFT ) ) );
        ui.moveRightEdit->setText( keybindingsManager.getStringRepresentation( keybindingsManager.getCameraControlsKey( RIGHT ) ) );
        ui.moveUpEdit->setText( keybindingsManager.getStringRepresentation( keybindingsManager.getCameraControlsKey( UP ) ) );
        ui.moveDownEdit->setText( keybindingsManager.getStringRepresentation( keybindingsManager.getCameraControlsKey( DOWN ) ) );
    }

    void CameraSettingsDialog::clearRecordButtonsFocus()
    {
        for( auto * recButton: recButtons.buttons() )
        {
            recButton->clearFocus();
        }
    }

    void CameraSettingsDialog::disableRecordButtons()
    {
        for( auto * recButton: recButtons.buttons() )
        {
            if( sender() != recButton )
            {
                recButton->setDisabled( true );
            }
        }
    }

    void CameraSettingsDialog::enableRecordButtons()
    {
        for( auto * recButton: recButtons.buttons() )
        {
            recButton->setEnabled( true );
        }
    }

} // namespace Ouquitoure
