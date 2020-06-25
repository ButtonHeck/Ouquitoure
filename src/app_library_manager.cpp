#include "AppLibraryManager"

#include "OpenGLApps/ColoredTriangleApp"

namespace Ouquitoure
{

    AppLibraryManager::AppLibraryManager()
        : invisibleParentForApps()
    {
    }

    void AppLibraryManager::loadApplications()
    {
        OpenGLAppBase * app = new ColoredTriangleApp( "Colored Triangle", &invisibleParentForApps );
        emit            applicationAdded( app, OPENGL_APP );
    }

} // namespace Ouquitoure
