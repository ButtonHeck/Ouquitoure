#pragma once

#include "Apps/AppInfo"

#include <QAbstractTableModel>

class QMainWindow;

namespace Ouquitoure
{
    class AppWindowBase;

    /**
     * @brief Applications collection model class
     */
    class AppCollectionModel final : public QAbstractTableModel
    {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE( AppCollectionModel )
    public:
        explicit AppCollectionModel( QObject * parent = nullptr );

        /// @brief adds application to the model
        void addApplication( AppWindowBase * app );

        /// @brief get application for its name
        /// @return pointer to the application of nullptr if not found
        [[nodiscard]] AppWindowBase * getApplication( const QString & name );

        /// @brief get the current application information object
        [[nodiscard]] AppInfo getCurrentAppInfo() const noexcept;

        /// @brief get names of all the applications containing in model
        [[nodiscard]] const QVector<QString> & getApplicationNames() const noexcept;

        /// @brief effectively returns number of applications in model
        [[nodiscard]] int rowCount( const QModelIndex & parent = QModelIndex() ) const override;

        /// @brief get the columns number
        [[nodiscard]] int columnCount( const QModelIndex & parent = QModelIndex() ) const override;

        /// @brief returns either name of the application or the set of its tags if the index is valid
        [[nodiscard]] QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const override;

        /// @brief returns name of the column
        [[nodiscard]] QVariant headerData( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const override;

    private:
        enum MODEL_COLUMNS
        {
            APP_NAME = 0,
            APP_TAGS = 1,
            NUM_COLUMNS
        };
        static constexpr const char * MODEL_COLUMNS_NAMES[ MODEL_COLUMNS::NUM_COLUMNS ]{ "App name", "Tags" };

    private slots:
        /// @brief slot to update current application info
        void updateCurrentAppInfo( const QModelIndex & index );

    private:
        QVector<AppWindowBase *> apps;
        AppInfo                  currentAppInfo;
        QVector<QString>         appsNames;
    };

} // namespace Ouquitoure
