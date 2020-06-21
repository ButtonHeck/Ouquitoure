#include <OpenGLApps/ColoredTriangleApp>

#include "Log"

namespace Ouquitoure
{

    ColoredTriangleApp::ColoredTriangleApp(QWidget * parent)
        : OpenGLAppBase(parent)
    {
        OQ_LOG_DEBUG << "ColoredTriangleApp ctor";
        info = AppInfo("Colored Triangle", {"basic", "triangle"}, OPENGL_APP);
    }

}
