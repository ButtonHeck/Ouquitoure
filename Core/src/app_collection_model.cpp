#include "app_collection_model.h"
#include "logger.h"

namespace Ouquitoure
{

    AppCollectionModel::AppCollectionModel(QObject * parent)
        : QAbstractTableModel(parent)
        , currentAppTableToken("", "")
    {}

    void AppCollectionModel::addAppTableToken(const QString & appName, const QString & appTags)
    {
        beginInsertRows(QModelIndex(), appsTableTokens.size(), appsTableTokens.size() );
        appsTableTokens << AppTableToken{ appName,appTags };
        endInsertRows();
    }

    AppTableToken AppCollectionModel::getCurrentAppTableToken() const noexcept
    {
        return currentAppTableToken;
    }

    int AppCollectionModel::rowCount(const QModelIndex & parent) const
    {
        Q_UNUSED(parent);
        return appsTableTokens.size();
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
                return appsTableTokens[index.row()].first;
            }
            else
            {
                return appsTableTokens[index.row()].second;
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

    void AppCollectionModel::tableTokenClick(const QModelIndex & index)
    {
#ifdef QT_DEBUG
        QStringList output{"Mouse click:"};
        output << " sender(" << sender()->objectName() << "): ";
        if (index.column() == APP_TAGS)
        {
            output << "(Tags)";
        }
        output << index.data(Qt::DisplayRole).toString();
        qInfo() << output.join(" ");
#endif
        currentAppTableToken = appsTableTokens[index.row()];
    }

}
