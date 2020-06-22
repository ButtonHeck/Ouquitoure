#include <OpenGLApps/ColoredTriangleApp>

namespace Ouquitoure
{

    ColoredTriangleApp::ColoredTriangleApp( const QString & appName, QWidget * parent )
        : OpenGLAppBase( appName, parent )
        , viewWidget( appName, parent )
    {
        info = AppInfo( appName, { "basic", "triangle" }, OPENGL_APP );
        installOpenGLViewWidget( viewWidget );
    }

} // namespace Ouquitoure
