#include "AppCollectionModel"

#include "Log"

namespace Ouquitoure
{

    AppCollectionModel::AppCollectionModel(QObject * parent)
        : QAbstractTableModel(parent)
        , currentAppInfo()
    {}

    void AppCollectionModel::addAppInfoEntry(const Ouquitoure::AppInfo & appInfo)
    {
        beginInsertRows(QModelIndex(), appInfos.size(), appInfos.size() );
        appInfos << appInfo;
        endInsertRows();
    }

    AppInfo AppCollectionModel::getCurrentAppInfo() const noexcept
    {
        return currentAppInfo;
    }

    int AppCollectionModel::rowCount(const QModelIndex & parent) const
    {
        Q_UNUSED(parent);
        return appInfos.size();
    }

    int AppCollectionModel::columnCount(const QModelIndex & parent) const
    {
        Q_UNUSED(parent);
        return NUM_COLUMNS;
    }

    QVariant AppCollectionModel::data(const QModelIndex & index, int role) const
    {
        if (role == Qt::DisplayRole)
        {
            if (index.column() == APP_NAME)
            {
                return appInfos[index.row()].getName();
            }
            else
            {
                return appInfos[index.row()].getTags().join(";");
            }
        }
        else
        {
            return QVariant{};
        }
    }

    QVariant AppCollectionModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
        if (orientation == Qt::Horizontal &&
            role == Qt::DisplayRole)
        {
            return MODEL_COLUMNS_NAMES[section];
        }
        return QVariant{};
    }

    void AppCollectionModel::tableEntryClick(const QModelIndex & index)
    {
#ifdef QT_DEBUG
        QStringList output{"Mouse click: "};
        output << "sender(" << sender()->objectName() << "): ";
        if (index.column() == APP_TAGS)
        {
            output << "(Tags) ";
        }
        output << index.data(Qt::DisplayRole).toString();
        OQ_LOG_INFO << output.join("");
#endif
        currentAppInfo = appInfos[index.row()];
    }

}
