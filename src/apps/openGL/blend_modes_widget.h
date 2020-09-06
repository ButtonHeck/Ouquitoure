#pragma once

#include "Apps/OpenGL/OpenGLWidgetBase"
#include "Math/Point2Pos4Color"
#include "Utils/BufferCollection"

#include <array>

namespace Ouquitoure
{
    /**
     * @brief Blend modes widget class,
     * contains control elements for 2 colored quads and opengl blend modes for both source and destination
     */
    class BlendModesWidget : public OpenGLWidgetBase
    {
        Q_OBJECT
    public:
        constexpr static int NUM_POINTS   = 8;
        constexpr static int NUM_ELEMENTS = 6 * 2;

    public:
        explicit BlendModesWidget( const QString & name, QWidget * parent = nullptr );
        ~BlendModesWidget();

        void                                      initializeGL() override;
        void                                      paintGL() override;
        const std::array<Point2p4c, NUM_POINTS> & getPoints() const noexcept;

    public slots:
        /**
         * @brief slot to update quad color, sender which connects to this slot,
         * should have name that include info about the quad and color indices to be updated
         * @param value value of the color (expected to be in range from 0 to 255)
         */
        void quadColorChanged( int value );

        /**
         * @brief slot to update blend function mode for either source or destination,
         * depending on a name of the sender
         */
        void blendFuncModeChanged();

        /**
         * @brief update blend color component, object name of the sender should be exactly color component letter (eg. R)
         * @param value value of the color (expected to be in range from 0 to 255)
         */
        void blendColorChanged( int value );

        /**
         * @brief update blend equation, object name of the sender should be exactly GLenum equation code
         */
        void blendFuncEquationChanged();

    protected:
        void initializeOpenGLObjects() override;
        void initializeOpenGLShaders() override;
        void cleanup() override;

    private:
        /**
         * @brief helper function to update vertex buffer data
         */
        void updateData();

    private:
        BufferCollection                  buffers;
        std::array<Point2p4c, NUM_POINTS> points;
        GLenum                            srcBlendFunc;
        GLenum                            dstBlendFunc;
        GLclampf                          blendColorRGBA[ 4 ];
    };

} // namespace Ouquitoure
