#pragma once

#include <QTableView>

namespace Ouquitoure
{

    /**
     * @brief Applications collection view class
     */
    class AppCollectionView : public QTableView
    {
        Q_OBJECT
    public:
        explicit AppCollectionView( QWidget * parent = nullptr );
    };

} // namespace Ouquitoure
