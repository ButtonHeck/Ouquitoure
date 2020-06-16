#pragma once

#include <QAbstractTableModel>

namespace Ouquitoure
{
    using AppData = QPair<QString, QString>;

    class AppCollectionModel : public QAbstractTableModel
    {
        Q_OBJECT
    public:
        explicit AppCollectionModel( QObject * parent = nullptr );

        void addNewAppData(const QString & appName, const QString & appTags);
        AppData getCurrentAppData() const;

        int rowCount( const QModelIndex &parent = QModelIndex() ) const override;
        int columnCount( const QModelIndex &parent = QModelIndex() ) const override;
        QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    private:
        static constexpr int MODEL_COLUMNS = 2;

    private slots:
        void debugDoubleMouseClickSlot(const QModelIndex & index);
        void debugMouseClickSlot(const QModelIndex & index);

    private:
        QVector<AppData> testData;

        AppData currentAppData;
    };
}
