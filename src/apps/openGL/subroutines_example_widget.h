#pragma once

#include "Apps/OpenGL/OpenGLWidgetBase"
#include "Math/Point2Pos3Color"
#include "Utils/BufferCollection"

#include <array>

namespace Ouquitoure
{

    /**
     * @brief Subroutines example application view widget class
     */
    class SubroutinesExampleWidget : public OpenGLWidgetBase
    {
        Q_OBJECT
    public:
        constexpr static int              NUM_POINTS      = 3;
        constexpr static int              NUM_SUBROUTINES = 7;
        constexpr static std::string_view SUBROUTINE_NAMES[ NUM_SUBROUTINES ]{ "bypass",  "grayscale", "shiftRight", "shiftLeft",
                                                                               "onlyRed", "onlyGreen", "onlyBlue" };

    public:
        explicit SubroutinesExampleWidget( const QString & name, QWidget * parent = nullptr );
        ~SubroutinesExampleWidget();

        void initializeGL() override;
        void paintGL() override;

    public slots:
        /// @brief slot to update shader active subroutine function
        void switchSubroutine();

    protected:
        void initializeOpenGLObjects() override;
        void initializeOpenGLShaders() override;
        void cleanup() override;

    private:
        BufferCollection                  buffers;
        std::array<Point2p3c, NUM_POINTS> points;
        GLint                             subroutineUniformLocation;
        QMap<QString, GLuint>             subroutineIndices;
    };

} // namespace Ouquitoure
