#pragma once

#include <QLabel>

#include <OpenGLApps/OpenGLAppBase>
#include <OpenGLApps/ColoredTriangleWidget>

namespace Ouquitoure
{
    class ColoredTriangleApp : public OpenGLAppBase
    {
        Q_OBJECT
    public:
        ColoredTriangleApp( const QString & appName, QWidget * parent );
        ~ColoredTriangleApp() = default;

    protected:
        void initializeDescription() override;

    private slots:
        void positionSliderValueChanged( int value );

    private:
        ColoredTriangleWidget viewWidget;

        QLabel * xPosLabel[ ColoredTriangleWidget::NUM_POINTS ];
        QLabel * yPosLabel[ ColoredTriangleWidget::NUM_POINTS ];
    };

} // namespace Ouquitoure
