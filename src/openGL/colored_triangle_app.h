#pragma once

#include <OpenGLApps/OpenGLAppBase>
#include <OpenGLApps/ColoredTriangleWidget>

namespace Ouquitoure
{
    class ColoredTriangleApp : public OpenGLAppBase
    {
    public:
        ColoredTriangleApp( const QString & appName, QWidget * parent );
        ~ColoredTriangleApp() = default;

    private:
        ColoredTriangleWidget viewWidget;
    };

} // namespace Ouquitoure
