#include "AppCollectionView.h"

#include <QHeaderView>

namespace Ouquitoure
{
    AppCollectionView::AppCollectionView( QWidget * parent )
        : QTableView(parent)
    {        
        horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        setSelectionMode(QAbstractItemView::SingleSelection);
    }
}
