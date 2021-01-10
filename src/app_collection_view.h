#pragma once

#include <QTableView>

namespace Ouquitoure
{

    /**
     * @brief Applications collection view class
     */
    class AppCollectionView final : public QTableView
    {
        Q_OBJECT
        Q_DISABLE_COPY_MOVE( AppCollectionView )
    public:
        explicit AppCollectionView( QWidget * parent = nullptr );
    };

} // namespace Ouquitoure
