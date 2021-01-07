#pragma once

#include "Apps/OpenGL/OpenGLWidgetBase"
#include "Math/Point2Pos2TexCoords"
#include "Utils/BufferCollection"

#include <array>
#include <QImage>

namespace Ouquitoure
{

    /**
     * @brief Image processing view widget
     */
    class ImageProcessingWidget : public OpenGLWidgetBase
    {
        Q_OBJECT
    public:
        constexpr static int NUM_POINTS   = 4;
        constexpr static int NUM_ELEMENTS = 6;

    public:
        explicit ImageProcessingWidget( const QString & name, QWidget * parent = nullptr );
        ~ImageProcessingWidget();

        void initializeGL() override;
        void paintGL() override;

    protected:
        void initializeOpenGLObjects() override;
        void initializeOpenGLShaders() override;
        void cleanup() override;

    private:
        BufferCollection                  buffers;
        std::array<Point2p2t, NUM_POINTS> points;
        QImage                            image;
        GLuint                            textureID;
    };

} // namespace Ouquitoure
