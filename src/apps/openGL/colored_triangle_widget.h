#pragma once

#include <array>

#include "Apps/OpenGL/OpenGLWidgetBase"
#include "Math/Point2Pos3Color"

namespace Ouquitoure
{

    /**
     * @brief Colored triangle application view widget class
     */
    class ColoredTriangleWidget : public OpenGLWidgetBase
    {
        Q_OBJECT
    public:
        constexpr static int NUM_POINTS = 3;

    public:
        explicit ColoredTriangleWidget( const QString & name, QWidget * parent = nullptr );
        ~ColoredTriangleWidget();

        void                                      initializeGL() override;
        void                                      paintGL() override;
        const std::array<Point2p3c, NUM_POINTS> & getPoints() const noexcept;

    public slots:
        void vertexPositionChanged( int value );
        void vertexColorChanged( int value );

    protected:
        void initializeOpenGLObjects() override;
        void initializeOpenGLShaders() override;
        void cleanup() override;

    private:
        void updateData();

    private:
        GLuint                            vao;
        GLuint                            vbo;
        std::array<Point2p3c, NUM_POINTS> points;
    };

} // namespace Ouquitoure
