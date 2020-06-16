#pragma once

#include <QWidget>
#include <QTableView>

namespace Ouquitoure
{
    class AppCollectionView : public QTableView
    {
        Q_OBJECT
    public:
        explicit AppCollectionView( QWidget *parent = nullptr );
    };
}
