#include "Apps/OpenGL/SubroutinesExampleApp"

#include <QVBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>

namespace Ouquitoure
{

    SubroutinesExampleApp::SubroutinesExampleApp( const QString & appName, QWidget * parent )
        : OpenGLAppBase( appName, parent )
        , viewWidget( appName, parent )
    {
        initializeDescription();
        installOpenGLViewWidget( viewWidget );

        // GUI view and layouts
        QVBoxLayout *  controlsLayout = new QVBoxLayout( controlsGroupBox );
        QButtonGroup * radioButtons   = new QButtonGroup( controlsLayout );
        for( int subroutineIndex = 0; subroutineIndex < SubroutinesExampleWidget::NUM_SUBROUTINES; ++subroutineIndex )
        {
            QString        name   = QString( SubroutinesExampleWidget::SUBROUTINE_NAMES[ subroutineIndex ].data() );
            QRadioButton * button = new QRadioButton( name );
            QFont          buttonFont;
            buttonFont.setPointSizeF( 20.0 );
            button->setFont( buttonFont );
            button->setObjectName( name );
            radioButtons->addButton( button );
            controlsLayout->addWidget( button );
            connect( button, SIGNAL( clicked() ), &viewWidget, SLOT( switchSubroutine() ) );
        }
        radioButtons->buttons().first()->setChecked( true );
    }

    void SubroutinesExampleApp::initializeDescription()
    {
        info = AppInfo( appName, { "basic", "2D", "subroutines" }, OQ_APP_TYPE_OPENGL );
        info.getDescription().setAuthor( "Ilya Malgin (Buttonheck)" );
        info.getDescription().setEmail( "buttonheck@gmail.com" );
        info.getDescription().setBrief( "Testing how to use subroutine mechanics in OpenGL shaders in both GLSL and client side code."
                                        " Subroutines here are represented as a set of color manipulation functions." );
        info.getDescription().setAppImage( ":/appImages/SubroutinesExample.png" );
        info.getDescription().addReference(
            { QUrl( "https://www.khronos.org/opengl/wiki/Shader_Subroutine" ), "OpenGL Wiki: Shader subroutine" } );
        info.getDescription().addReference(
            { QUrl( "http://www.opengl-redbook.com/" ), "OpenGL book: Chapter 2, Shader Subroutines section" } );
    }

} // namespace Ouquitoure
