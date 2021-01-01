#include "CameraSettingsDialog"
#include "Log"

namespace Ouquitoure
{

    CameraSettingsDialog::CameraSettingsDialog( QWidget * parent )
        : QDialog( parent )
        , ui()
    {
        ui.setupUi( this );
    }

#ifdef QT_DEBUG
    CameraSettingsDialog::~CameraSettingsDialog()
    {
        OQ_LOG_DEBUG << "Camera settings dialog dtor";
    }
#endif

} // namespace Ouquitoure
