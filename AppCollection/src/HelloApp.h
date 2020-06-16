#pragma once

#include "AppCollection_global.h"
#include <QWidget>

class APPCOLLECTION_EXPORT HelloApp : public QWidget
{
    Q_OBJECT
public:
    explicit HelloApp( QWidget * parent = nullptr );
};
