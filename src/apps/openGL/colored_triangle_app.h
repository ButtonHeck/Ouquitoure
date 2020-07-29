#pragma once

#include "Apps/OpenGL/OpenGLAppBase"
#include "Apps/OpenGL/ColoredTriangleWidget"

#include <QLabel>

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
        /**
         * @brief slot to update position label's text. Label is defined by the sender object's name, which contains
         * information about label ordinal
         * @param value label text integer representation
         */
        void updatePositionLabelText( int value );

    private:
        ColoredTriangleWidget viewWidget;

        QLabel * xPosLabel[ ColoredTriangleWidget::NUM_POINTS ];
        QLabel * yPosLabel[ ColoredTriangleWidget::NUM_POINTS ];
    };

} // namespace Ouquitoure
