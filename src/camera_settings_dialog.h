#pragma once

#include "ui_camera_settings_dialog.h"

#include <QDialog>
#include <QMainWindow>

namespace Ouquitoure
{
    /**
     * @brief Camera settings dialog,
     * keyboard bindings, fov and other settings
     */
    class CameraSettingsDialog : public QDialog
    {
        Q_OBJECT
    public:
        explicit CameraSettingsDialog( QWidget * parent = nullptr );

#ifdef QT_DEBUG
        ~CameraSettingsDialog();
#else
        ~CameraSettingsDialog() = default;
#endif
    private:
        Ui::CameraSettingsDialog ui;
    };

} // namespace Ouquitoure
