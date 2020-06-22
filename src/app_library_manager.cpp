#include "AppLibraryManager"

#include "OpenGLApps/ColoredTriangleApp"

namespace Ouquitoure
{

    AppLibraryManager::AppLibraryManager( AppCollectionModel & openGLAppsModel, AppCollectionModel & softwareAppsModel )
        : invisibleParentForApps()
        , openGLAppsModel( openGLAppsModel )
        , softwareAppsModel( softwareAppsModel )
    {
        openGLAppsModel.addApplication( new ColoredTriangleApp( "Colored Triangle", &invisibleParentForApps ) );
    }

} // namespace Ouquitoure
