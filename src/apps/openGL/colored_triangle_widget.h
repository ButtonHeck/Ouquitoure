#pragma once

#include "Apps/OpenGL/OpenGLWidgetBase"
#include "Math/Point2Pos3Color"

#include <array>

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
        /**
         * @brief slot to update vertex position. Vertex is defined by the signal sender object name, which contains
         * information of a vertex ordinal and its coordinate to update
         * @param value position new value
         */
        void vertexPositionChanged( int value );

        /**
         * @brief slot to update vertex color. Vertex is defined by the signal sender object name, which contains
         * information of a vertex ordinal and its color component to update
         * @param value color new value
         */
        void vertexColorChanged( int value );

    protected:
        void initializeOpenGLObjects() override;
        void initializeOpenGLShaders() override;
        void cleanup() override;

    private:
        /**
         * @brief helper function to update vertex buffer object
         */
        void updateData();

    private:
        GLuint                            vao;
        GLuint                            vbo;
        std::array<Point2p3c, NUM_POINTS> points;
    };

} // namespace Ouquitoure
