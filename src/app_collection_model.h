#pragma once

#include <QAbstractTableModel>

#include "Apps/AppWindowBase"

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

        void                     addApplication( AppWindowBase * app );
        AppWindowBase *          getApplication( const QString & name );
        AppInfo                  getCurrentAppInfo() const noexcept;
        const QVector<QString> & getApplicationNames() const noexcept;

        int      rowCount( const QModelIndex & parent = QModelIndex() ) const override;
        int      columnCount( const QModelIndex & parent = QModelIndex() ) const override;
        QVariant data( const QModelIndex & index, int role = Qt::DisplayRole ) const override;
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
        void updateCurrentAppInfo( const QModelIndex & index );

    private:
        QVector<AppWindowBase *> apps;
        AppInfo                  currentAppInfo;
        QVector<QString>         appsNames;
    };

} // namespace Ouquitoure
