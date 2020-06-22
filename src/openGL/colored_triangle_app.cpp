#include <OpenGLApps/ColoredTriangleApp>

namespace Ouquitoure
{

    ColoredTriangleApp::ColoredTriangleApp( const QString & appName, QWidget * parent )
        : OpenGLAppBase( appName, parent )
    {
        info = AppInfo( appName, { "basic", "triangle" }, OPENGL_APP );
    }

} // namespace Ouquitoure
