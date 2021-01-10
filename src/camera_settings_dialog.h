#pragma once

#include "ui_camera_settings_dialog.h"

#include <QDialog>
#include <QMainWindow>
#include <QButtonGroup>

namespace Ouquitoure
{
    class KeybindingsManager;

    /**
     * @brief Camera settings dialog,
     * keyboard bindings, fov and other settings
     */
    class CameraSettingsDialog final : public QDialog
    {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE( CameraSettingsDialog )
    public:
        explicit CameraSettingsDialog( const KeybindingsManager & keybindingsManager, QWidget * parent = nullptr );

#ifdef QT_DEBUG
        ~CameraSettingsDialog();
#else
        ~CameraSettingsDialog() = default;
#endif
    private slots:
        void updateControlKeysView();
        void clearRecordButtonsFocus();
        void disableRecordButtons();
        void enableRecordButtons();

    private:
        Ui::CameraSettingsDialog   ui;
        const KeybindingsManager & keybindingsManager;
        QButtonGroup               recButtons;
    };

} // namespace Ouquitoure
