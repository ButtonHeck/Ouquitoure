#include "Apps/OpenGL/OpenGLDrawFunctionsApp"
#include "Log"

#include <QKeyEvent>
#include <QCheckBox>

namespace Ouquitoure
{

    OpenGLDrawFunctionsApp::OpenGLDrawFunctionsApp( const QString & appName, QWidget * parent )
        : OpenGLAppBase( appName, parent )
        , viewWidget( appName, parent )
    {
        initializeDescription();
        installOpenGLViewWidget( viewWidget );
        installEventFilter( &viewWidget );

        QVBoxLayout * controlsLayout = new QVBoxLayout( controlsGroupBox );
        for( int functionIndex = 0; functionIndex < OpenGLDrawFunctionsWidget::NUM_FUNCTIONS; ++functionIndex )
        {
            QHBoxLayout * drawFunctionLayout = new QHBoxLayout;

            QCheckBox * drawFunctionCheckbox =
                new QCheckBox( viewWidget.getDrawFunctionName( (OpenGLDrawFunctionsWidget::DRAW_FUNCTIONS)functionIndex ) );
            drawFunctionCheckbox->setTristate( false );
            drawFunctionCheckbox->setChecked( true );
            drawFunctionCheckbox->setObjectName( QString::number( functionIndex ) );
            connect( drawFunctionCheckbox, SIGNAL( clicked( bool ) ), &viewWidget, SLOT( setFunctionEnabled( bool ) ) );

            drawFunctionLayout->addWidget( drawFunctionCheckbox );
            controlsLayout->addLayout( drawFunctionLayout );
        }
    }

    void OpenGLDrawFunctionsApp::initializeDescription()
    {
        info = AppInfo( appName, { "basic", "3D", "draw_functions" }, OPENGL_APP );
        info.getDescription().setAuthor( "Ilya Malgin (Buttonheck)" );
        info.getDescription().setEmail( "buttonheck@gmail.com" );
        info.getDescription().setBrief( "All OpenGL functions usage examples (except drawing transform feedback)" );
        info.getDescription().setAppImage( ":/appImages/OpenGLDrawFunctions.png" );
        info.getDescription().addReference(
            { QUrl( "https://www.khronos.org/opengl/wiki/Vertex_Rendering" ), "Vertex rendering page from OpenGL Wiki" } );
        info.getDescription().addReference(
            { QUrl( "http://www.opengl-redbook.com/" ), "OpenGL book: Chapter 3, OpenGL Drawing Commands section" } );
    }

} // namespace Ouquitoure
