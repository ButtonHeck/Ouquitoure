#pragma once

#include "AppLibraryManager"

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

    /**
     * @brief Ouquitoure main window class
     */
    class CoreAppWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        /**
         * @brief all Qt connections and ui setup happens here
         */
        explicit CoreAppWindow( QWidget * parent = nullptr );

        ~CoreAppWindow();

    private slots:
        /**
         * @brief slot to launch an application. An application is chosen based on the app name and
         * its type that is currently in the selected state of the view
         * @return true in case of successful launch
         */
        bool launchApp();

        /**
         * @brief slot to update an application HTML info in the description view window.
         * An application is chosen based on the app name and
         * its type that is currently in the selected state of the view
         */
        void updateDescriptionWindowInfo();

        /**
         * @brief slot to switch description view window visibility
         */
        void switchDescriptionWindowVisible();

        /**
         * @brief slot to add application to one of the models defined by the given type
         * @param app new application
         * @param type type of the added application
         */
        void addApplication( AppWindowBase * app, APP_TYPE type );

        /**
         * @brief searches all the apps whose names contains given string
         * @param name name string
         * @note if only one match for name found than the app with that name is set to be chosen to launch
         */
        void searchByName( const QString & name );

        /**
         * @brief searches all the apps whose tags contains all of the given tags
         * @param tags tags string
         * @note if only one match for tags set found than the app with those tags is set to be chosen to launch
         */
        void searchByTags( const QString & tags );

    private:
        /**
         * @brief utility function to get application type based on the view tab widget current index
         * @return application type enumeration value
         */
        APP_TYPE getViewTabCurrentAppType();

        /**
         * @brief get the name of the app that is to be launched
         * @param type application type
         * @return name of the app that is to be launched
         */
        QString getCurrentlyChosenAppName( APP_TYPE type );

        /**
         * @brief get pointer of application collection model for a given application type enumerator
         * @param appType app type enumerator
         * @return application collection model pointer or nullptr if enumerator is incorrect of not implemented
         */
        AppCollectionModel * getAppCollectionModelForType( APP_TYPE appType );

        /**
         * @brief get app window that is currently chosen in the preview
         * @param appType application type
         * @param appName name for the application of interest
         * @return application window pointer or nullptr if no app with the given name was found
         */
        AppWindowBase * getCurrentlyChosenAppWindow( APP_TYPE appType, const QString & appName );

        /**
         * @brief get application collection view for a given app type enumerator
         * @param appType app type enumerator
         * @return application collection view pointer or nullptr if enumerator is incorrect or not implemented
         */
        AppCollectionView * getAppCollectionViewForType( APP_TYPE appType );

        /**
         * @brief get selection of a view for a given app type enumerator
         * @param appType application type enumerator
         * @return selection model pointer or nullptr if enumerator is incorrect or not implemented
         */
        QItemSelectionModel * getSelectionModelForType( APP_TYPE appType );

    private:
        Ui::CoreAppWindow *  ui;
        AppCollectionModel * openGLAppsCollectionModel;
        AppCollectionModel * softwareAppsCollectionModel;
        AppLibraryManager    appLibraryManager;
    };
} // namespace Ouquitoure
