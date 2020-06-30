#include "Apps/OpenGL/OpenGLDrawFunctionsWidget"

namespace Ouquitoure
{

    OpenGLDrawFunctionsWidget::OpenGLDrawFunctionsWidget( const QString & name, QWidget * parent )
        : OpenGLWidgetBase( name, parent )
    {
    }

    OpenGLDrawFunctionsWidget::~OpenGLDrawFunctionsWidget()
    {
        cleanup();
    }

    void OpenGLDrawFunctionsWidget::initializeGL()
    {
        OpenGLWidgetBase::initializeGL();
        cleanup();

        glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
        initializeOpenGLObjects();
        initializeOpenGLShaders();
    }

    void OpenGLDrawFunctionsWidget::paintGL()
    {
    }

    void OpenGLDrawFunctionsWidget::initializeOpenGLObjects()
    {
    }

    void OpenGLDrawFunctionsWidget::initializeOpenGLShaders()
    {
    }

    void OpenGLDrawFunctionsWidget::cleanup()
    {
    }

} // namespace Ouquitoure
