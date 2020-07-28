#pragma once

#include "Apps/AppWindowBase"

#include <QAbstractTableModel>

class QMainWindow;

namespace Ouquitoure
{

    /**
     * @brief Applications collection model class
     */
    class AppCollectionModel : public QAbstractTableModel
    {
        Q_OBJECT
    public:
        explicit AppCollectionModel( QObject * parent = nullptr );

        /**
         * @brief adds application to the model
         * @param app new application
         */
        void addApplication( AppWindowBase * app );

        /**
         * @brief get application for its name
         * @param name name of the application
         * @return pointer to the application of nullptr if not found
         */
        AppWindowBase * getApplication( const QString & name );

        /**
         * @brief get the current application information
         * @return appInfo object
         */
        AppInfo getCurrentAppInfo() const noexcept;

        /**
         * @brief get all containing in model applications names
         * @return vector of application names
         */
        const QVector<QString> & getApplicationNames() const noexcept;

        /**
         * @brief effectively returns number of applications in model
         */
        int rowCount( const QModelIndex & parent = QModelIndex() ) const override;

        /**
         * @brief get the columns number
         */
        int columnCount( const QModelIndex & parent = QModelIndex() ) const override;

        /**
         * @brief returns either name of the application or the set of its tags if the index is valid
         */
        QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const override;

        /**
         * @brief returns name of the column
         */
        QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const override;

    private:
        enum MODEL_COLUMNS
        {
            APP_NAME = 0,
            APP_TAGS = 1,
            NUM_COLUMNS
        };
        static constexpr const char * MODEL_COLUMNS_NAMES[ MODEL_COLUMNS::NUM_COLUMNS ]{ "App name", "Tags" };

    private slots:
        /**
         * @brief slot to update current application info
         * @param index index representing current application
         */
        void updateCurrentAppInfo( const QModelIndex & index );

    private:
        QVector<AppWindowBase *> apps;
        AppInfo                  currentAppInfo;
        QVector<QString>         appsNames;
    };

} // namespace Ouquitoure
