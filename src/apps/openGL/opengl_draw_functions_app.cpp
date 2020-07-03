#include "Apps/OpenGL/OpenGLDrawFunctionsApp"

#include <QKeyEvent>

#include "Log"

namespace Ouquitoure
{

    OpenGLDrawFunctionsApp::OpenGLDrawFunctionsApp( const QString & appName, QWidget * parent )
        : OpenGLAppBase( appName, parent )
        , viewWidget( appName, parent )
    {
        initializeDescription();
        installOpenGLViewWidget( viewWidget );
    }

    void OpenGLDrawFunctionsApp::keyPressEvent( QKeyEvent * event )
    {
        viewWidget.getCamera().move( event->key(), 0.05f );
    }

    void OpenGLDrawFunctionsApp::initializeDescription()
    {
        info = AppInfo( appName, { "basic", "3D", "draw_functions" }, OPENGL_APP );
        info.getDescription().setName( appName );
        info.getDescription().setAuthor( "Ilya Malgin (Buttonheck)" );
        info.getDescription().setEmail( "buttonheck@gmail.com" );
    }

} // namespace Ouquitoure