#pragma once

#include <QTableView>

namespace Ouquitoure
{
    class AppCollectionView : public QTableView
    {
        Q_OBJECT
    public:
        explicit AppCollectionView( QWidget * parent = nullptr );
    };
} // namespace Ouquitoure
