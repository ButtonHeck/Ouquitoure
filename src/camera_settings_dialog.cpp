#include "CameraSettingsDialog"
#include "Log"

namespace Ouquitoure
{

    CameraSettingsDialog::CameraSettingsDialog( QWidget * parent )
        : QDialog( parent )
    {
    }

#ifdef QT_DEBUG
    CameraSettingsDialog::~CameraSettingsDialog()
    {
        OQ_LOG_DEBUG << "Camera settings dialog dtor";
    }
#endif

} // namespace Ouquitoure
