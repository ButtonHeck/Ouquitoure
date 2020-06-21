#pragma once

#include <QAbstractTableModel>
#include <QWidget>

#include "AppWindowBase"

class QMainWindow;

namespace Ouquitoure
{
    class AppCollectionModel : public QAbstractTableModel
    {
        Q_OBJECT
    public:
        explicit AppCollectionModel( QObject * parent = nullptr );

        AppWindowBase * getApplication(const QString & name);
        AppInfo getCurrentAppInfo() const noexcept;

        int rowCount( const QModelIndex &parent = QModelIndex() ) const override;
        int columnCount( const QModelIndex &parent = QModelIndex() ) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    private:
        enum MODEL_COLUMNS
        {
            APP_NAME = 0,
            APP_TAGS = 1,
            NUM_COLUMNS
        };
        static constexpr const char * MODEL_COLUMNS_NAMES[MODEL_COLUMNS::NUM_COLUMNS] {"App name", "Tags"};

    private slots:
        void tableEntryClick(const QModelIndex & index);

    private:
        std::vector<AppWindowBase*> apps;
        AppInfo currentAppInfo;
        QWidget invisibleParentForApps;
    };
}
