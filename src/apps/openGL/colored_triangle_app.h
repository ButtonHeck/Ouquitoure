#pragma once

#include <QLabel>

#include <Apps/OpenGL/OpenGLAppBase>
#include <Apps/OpenGL/ColoredTriangleWidget>

namespace Ouquitoure
{

    /**
     * @brief Colored triangle application class
     */
    class ColoredTriangleApp : public OpenGLAppBase
    {
        Q_OBJECT
    public:
        ColoredTriangleApp( const QString & appName, QWidget * parent );
        ~ColoredTriangleApp() = default;

    protected:
        void initializeDescription() override;

    private slots:
        void updatePositionLabelText( int value );

    private:
        ColoredTriangleWidget viewWidget;

        QLabel * xPosLabel[ ColoredTriangleWidget::NUM_POINTS ];
        QLabel * yPosLabel[ ColoredTriangleWidget::NUM_POINTS ];
    };

} // namespace Ouquitoure
