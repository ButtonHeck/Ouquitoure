#pragma once

#include "AppLibraryManager"
#include "KeybindingsManager"

#include <QMainWindow>
#include <QVector>

namespace Ui
{
    class CoreAppWindow;
}

class QItemSelectionModel;

namespace Ouquitoure
{
    class AppCollectionModel;
    class AppCollectionView;
    class CameraSettingsDialog;

    /**
     * @brief Ouquitoure main window class
     */
    class CoreAppWindow final : public QMainWindow
    {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE( CoreAppWindow )
    public:
        /// @brief all Qt connections and ui setup happens here
        explicit CoreAppWindow( QWidget * parent = nullptr );

        ~CoreAppWindow();

    private slots:
        /// @brief slot to launch an application. An application is chosen based on the app name and
        /// its type that is currently in the selected state of the view
        bool launchApp();

        /// @brief slot to update an application HTML info in the description view window.
        /// An application is chosen based on the app name and
        /// its type that is currently in the selected state of the view
        void updateDescriptionWindowInfo();

        /// @brief slot to switch description view window visibility
        void switchDescriptionWindowVisible();

        /// @brief slot to add application to one of the models defined by the app type
        void addApplication( AppWindowBase * app );

        /// @brief searches all the apps whose names contains given string
        /// @note if only one match for name found than the app with that name is set to be chosen to launch
        void searchByName( const QString & name );

        /// @brief searches all the apps whose tags contains all of the given tags
        /// @note if only one match for tags set found than the app with those tags is set to be chosen to launch
        void searchByTags( const QString & tags );

        /// @brief shows 3D camera settings dialog
        void showCameraSettingsDialog();

    private:
        /// @brief utility function to get application type based on the view tab widget current index
        [[nodiscard]] APP_TYPE getViewTabCurrentAppType();

        /// @brief get the name of the app that is to be launched
        /// @param type application type
        [[nodiscard]] QString getCurrentlyChosenAppName( APP_TYPE type );

        /// @brief get pointer of application collection model for a given application type enumerator
        /// @return application collection model pointer or nullptr if enumerator is incorrect or not implemented
        [[nodiscard]] AppCollectionModel * getAppCollectionModelForType( APP_TYPE appType );

        /// @brief get app window that is currently chosen in the preview
        /// @return application window pointer or nullptr if no app with the given name was found
        [[nodiscard]] AppWindowBase * getCurrentlyChosenAppWindow( APP_TYPE appType, const QString & appName );

        /// @brief get application collection view for a given app type enumerator
        /// @return application collection view pointer or nullptr if enumerator is incorrect or not implemented
        [[nodiscard]] AppCollectionView * getAppCollectionViewForType( APP_TYPE appType );

        /// @brief get selection of a view for a given app type enumerator
        /// @return selection model pointer or nullptr if enumerator is incorrect or not implemented
        [[nodiscard]] QItemSelectionModel * getSelectionModelForType( APP_TYPE appType );

    private:
        Ui::CoreAppWindow *    ui;
        AppCollectionModel *   openGLAppsCollectionModel;
        AppCollectionModel *   softwareAppsCollectionModel;
        AppLibraryManager      appLibraryManager;
        KeybindingsManager     keybindingsManager;
        CameraSettingsDialog * cameraSettingsDialog;
    };
} // namespace Ouquitoure
