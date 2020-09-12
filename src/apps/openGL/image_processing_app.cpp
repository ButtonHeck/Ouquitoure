#include "Apps/OpenGL/ImageProcessingApp"

namespace Ouquitoure
{

    ImageProcessingApp::ImageProcessingApp( const QString & appName, QWidget * parent )
        : OpenGLAppBase( appName, parent )
        , viewWidget( appName, parent )
    {
        initializeDescription();
        installOpenGLViewWidget( viewWidget );
    }

    void ImageProcessingApp::initializeDescription()
    {
        info = AppInfo{ appName, { "image", "filters", "2D" }, OQ_OPENGL_APP };
        info.getDescription().setAuthor( "Ilya Malgin (Buttonheck)" );
        info.getDescription().setEmail( "buttonheck@gmail.com" );
    }

} // namespace Ouquitoure
