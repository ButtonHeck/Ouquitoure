#include "AppCollectionModel"
#include "Apps/AppWindowBase"
#include "Log"

namespace Ouquitoure
{

    AppCollectionModel::AppCollectionModel( QObject * parent )
        : QAbstractTableModel( parent )
        , currentAppInfo()
    {
    }

    void AppCollectionModel::addApplication( AppWindowBase * app )
    {
        beginInsertRows( QModelIndex(), apps.size(), apps.size() );
        apps << app;
        endInsertRows();
        appsNames.push_back( app->getInfo().getName() );
    }

    AppWindowBase * AppCollectionModel::getApplication( const QString & name )
    {
        auto appIter = std::find_if( apps.cbegin(), apps.cend(), [ & ]( AppWindowBase * application ) {
            return application->getInfo().getName() == name;
        } );
        return ( appIter != apps.cend() ) ? *appIter : nullptr;
    }

    AppInfo AppCollectionModel::getCurrentAppInfo() const noexcept
    {
        return currentAppInfo;
    }

    const QVector<QString> & AppCollectionModel::getApplicationNames() const noexcept
    {
        return appsNames;
    }

    int AppCollectionModel::rowCount( const QModelIndex & parent ) const
    {
        Q_UNUSED( parent );
        return static_cast<int>( apps.size() );
    }

    int AppCollectionModel::columnCount( const QModelIndex & parent ) const
    {
        Q_UNUSED( parent );
        return NUM_COLUMNS;
    }

    QVariant AppCollectionModel::data( const QModelIndex & index, int role ) const
    {
        if( role == Qt::DisplayRole )
        {
            if( index.column() == APP_NAME )
            {
                return apps[ index.row() ]->getInfo().getName();
            }
            else
            {
                return apps[ index.row() ]->getInfo().getTags().join( ";" );
            }
        }
        else
        {
            return QVariant{};
        }
    }

    QVariant AppCollectionModel::headerData( int section, Qt::Orientation orientation, int role ) const
    {
        if( orientation == Qt::Horizontal && role == Qt::DisplayRole )
        {
            return MODEL_COLUMNS_NAMES[ section ];
        }
        return QVariant{};
    }

    void AppCollectionModel::updateCurrentAppInfo( const QModelIndex & index )
    {
#ifdef QT_DEBUG
        QStringList output{ "Mouse click: " };
        output << "sender(" << sender()->objectName() << "): ";
        if( index.column() == APP_TAGS )
        {
            output << "(Tags) ";
        }
        output << index.data( Qt::DisplayRole ).toString();
        OQ_LOG_INFO << output.join( "" );
#endif
        currentAppInfo = apps[ index.row() ]->getInfo();
    }

} // namespace Ouquitoure
