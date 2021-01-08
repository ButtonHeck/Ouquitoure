#include "AppLibraryManager"
#include "Apps/OpenGL/ColoredTriangleApp"
#include "Apps/OpenGL/OpenGLDrawFunctionsApp"
#include "Apps/OpenGL/SubroutinesExampleApp"
#include "Apps/OpenGL/BlendModesApp"
#include "Apps/OpenGL/ImageProcessingApp"
#include "KeybindingsManager"

namespace Ouquitoure
{

    AppLibraryManager::AppLibraryManager()
        : invisibleParentForApps()
    {
    }

    void AppLibraryManager::loadApplications( const KeybindingsManager & keybindingsManager )
    {
        OpenGLAppBase * app = new ColoredTriangleApp( "Colored Triangle", &invisibleParentForApps );
        emit            applicationCreated( app );

        app = new OpenGLDrawFunctionsApp( "OpenGL Draw Functions", &invisibleParentForApps, keybindingsManager );
        emit applicationCreated( app );

        app = new SubroutinesExampleApp( "Subroutines example", &invisibleParentForApps );
        emit applicationCreated( app );

        app = new BlendModesApp( "Blend modes", &invisibleParentForApps );
        emit applicationCreated( app );

        app = new ImageProcessingApp( "Image processing", &invisibleParentForApps );
        emit applicationCreated( app );
    }

} // namespace Ouquitoure
