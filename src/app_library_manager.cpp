#include "AppLibraryManager"

#include "OpenGLApps/ColoredTriangleApp"

namespace Ouquitoure
{

    AppLibraryManager::AppLibraryManager( AppCollectionModel & openGLAppsModel, AppCollectionModel & softwareAppsModel )
        : invisibleParentForApps()
        , openGLAppsModel( openGLAppsModel )
        , softwareAppsModel( softwareAppsModel )
    {
        OpenGLAppBase * app = new ColoredTriangleApp( "Colored Triangle", &invisibleParentForApps );
        openGLAppsModel.addApplication( app );
    }

} // namespace Ouquitoure
