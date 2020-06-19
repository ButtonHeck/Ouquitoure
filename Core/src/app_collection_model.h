#pragma once

#include <QAbstractTableModel>

namespace Ouquitoure
{
    using AppTableToken = QPair<QString, QString>;

    class AppCollectionModel : public QAbstractTableModel
    {
        Q_OBJECT
    public:
        explicit AppCollectionModel( QObject * parent = nullptr );

        void addAppTableToken(const QString & appName, const QString & appTags);
        AppTableToken getCurrentAppTableToken() const noexcept;

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
        void tableTokenClick(const QModelIndex & index);

    private:
        QVector<AppTableToken> appsTableTokens;
        AppTableToken currentAppTableToken;
    };
}
