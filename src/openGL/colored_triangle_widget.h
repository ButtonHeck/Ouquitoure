#pragma once

#include "OpenGLApps/OpenGLWidgetBase"

namespace Ouquitoure
{
    class ColoredTriangleWidget : public OpenGLWidgetBase
    {
    public:
        explicit ColoredTriangleWidget( const QString & name, QWidget * parent = nullptr );
        ~ColoredTriangleWidget() = default;

        void initializeGL() override;
        void paintGL() override;

    private:
    };

} // namespace Ouquitoure
