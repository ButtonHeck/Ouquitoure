#pragma once

#include "OpenGLApps/OpenGLWidgetBase"
#include "Utils/Point2Pos3Color"

namespace Ouquitoure
{
    class ColoredTriangleWidget : public OpenGLWidgetBase
    {
    public:
        explicit ColoredTriangleWidget( const QString & name, QWidget * parent = nullptr );
        ~ColoredTriangleWidget();

        void initializeGL() override;
        void paintGL() override;

    protected:
        void initializeOpenGLObjects() override;
        void initializeOpenGLShaders() override;

    private:
        GLuint vao;
        GLuint vbo;
        QVector<Utils::Point2Pos3Color> points;
    };

} // namespace Ouquitoure
