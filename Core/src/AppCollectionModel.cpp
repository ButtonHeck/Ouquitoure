#include "AppCollectionModel.h"
#include <QDebug>

namespace Ouquitoure
{

    AppCollectionModel::AppCollectionModel(QObject * parent)
        : QAbstractTableModel(parent)
        , currentAppData("", "")
    {
    }

    void AppCollectionModel::addNewAppData(const QString & appName, const QString & appTags)
    {
        beginInsertRows(QModelIndex(), testData.size(), testData.size() );
        testData.push_back( AppData( appName,appTags ) );
        endInsertRows();
    }

    AppData AppCollectionModel::getCurrentAppData() const
    {
        return currentAppData;
    }

    int AppCollectionModel::rowCount(const QModelIndex & parent) const
    {
        Q_UNUSED(parent);
        return testData.size();
    }

    int AppCollectionModel::columnCount(const QModelIndex & parent) const
    {
        Q_UNUSED(parent);
        return MODEL_COLUMNS;
    }

    QVariant AppCollectionModel::data(const QModelIndex & index, int role) const
    {
        if (role == Qt::DisplayRole)
        {
            if (index.column() == 0)
            {
                return testData[index.row()].first;
            }
            else
            {
                return testData[index.row()].second;
            }
        }
        else
        {
            return QVariant{};
        }
    }

    QVariant AppCollectionModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
        static constexpr const char * HEADER_NAMES[MODEL_COLUMNS] {"App name", "Tags"};
        if (orientation == Qt::Horizontal &&
            role == Qt::DisplayRole)
        {
            return HEADER_NAMES[section];
        }
        return QVariant{};
    }

    void AppCollectionModel::debugMouseClickSlot(const QModelIndex & index)
    {
        QStringList output{"Mouse click:"};
        if (index.column() == 1)
        {
            output << "(Tags)";
        }
        output << index.data(Qt::DisplayRole).toString();
        qDebug() << output.join(" ");
        currentAppData = testData[index.row()];
    }

    void AppCollectionModel::debugDoubleMouseClickSlot(const QModelIndex & index)
    {
        QStringList output{"Double mouse click:"};
        if (index.column() == 1)
        {
            output << "(Tags)";
        }
        output << index.data(Qt::DisplayRole).toString();
        qDebug() << output.join(" ");
        currentAppData = testData[index.row()];
    }
}
