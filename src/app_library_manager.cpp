#include "AppLibraryManager"
#include "Apps/OpenGL/ColoredTriangleApp"
#include "Apps/OpenGL/OpenGLDrawFunctionsApp"
#include "Apps/OpenGL/SubroutinesExampleApp"

namespace Ouquitoure
{

    AppLibraryManager::AppLibraryManager()
        : invisibleParentForApps()
    {
    }

    void AppLibraryManager::loadApplications()
    {
        OpenGLAppBase * app = new ColoredTriangleApp( "Colored Triangle", &invisibleParentForApps );
        emit            applicationCreated( app, OPENGL_APP );

        app = new OpenGLDrawFunctionsApp( "OpenGL Draw Functions", &invisibleParentForApps );
        emit applicationCreated( app, OPENGL_APP );

        app = new SubroutinesExampleApp( "Subroutines example", &invisibleParentForApps );
        emit applicationCreated( app, OPENGL_APP );
    }

} // namespace Ouquitoure
