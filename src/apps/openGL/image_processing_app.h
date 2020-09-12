#pragma once

#include "Apps/OpenGL/OpenGLAppBase"
#include "Apps/OpenGL/ImageProcessingWidget"

namespace Ouquitoure
{

    class ImageProcessingApp : public OpenGLAppBase
    {
        Q_OBJECT
    public:
        ImageProcessingApp( const QString & appName, QWidget * parent );

    protected:
        void initializeDescription() override;

    private:
        ImageProcessingWidget viewWidget;
    };

} // namespace Ouquitoure
