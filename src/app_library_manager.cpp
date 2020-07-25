#include "AppLibraryManager"
#include "Apps/OpenGL/ColoredTriangleApp"
#include "Apps/OpenGL/OpenGLDrawFunctionsApp"

namespace Ouquitoure
{

    AppLibraryManager::AppLibraryManager()
        : invisibleParentForApps()
    {
    }

    /**
     * @brief instantiates all the applications and emits signals that one was created
     */
    void AppLibraryManager::loadApplications()
    {
        OpenGLAppBase * app = new ColoredTriangleApp( "Colored Triangle", &invisibleParentForApps );
        emit            applicationCreated( app, OPENGL_APP );

        app = new OpenGLDrawFunctionsApp( "OpenGL Draw Functions", &invisibleParentForApps );
        emit applicationCreated( app, OPENGL_APP );
    }

} // namespace Ouquitoure
