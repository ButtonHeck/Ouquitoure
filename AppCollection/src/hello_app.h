#pragma once

#include "AppCollection_global.h"
#include <QMainWindow>
#include <Qt3DCore/QNodePtr>

class APPCOLLECTION_EXPORT HelloApp : public QMainWindow
{
    Q_OBJECT
public:
    explicit HelloApp( QWidget * parent = nullptr );
    ~HelloApp();
};
