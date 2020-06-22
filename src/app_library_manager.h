#pragma once

#include <QWidget>

#include "AppCollectionModel"

namespace Ouquitoure
{
    class AppLibraryManager
    {
    public:
        AppLibraryManager( AppCollectionModel & openGLAppsModel, AppCollectionModel & softwareAppsModel );

    private:
        QWidget              invisibleParentForApps;
        AppCollectionModel & openGLAppsModel;
        AppCollectionModel & softwareAppsModel;
    };
} // namespace Ouquitoure
