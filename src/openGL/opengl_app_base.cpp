#include "OpenGLApps/OpenGLAppBase"

#include <QHBoxLayout>
#include <QGroupBox>
#include <QDockWidget>
#include <QResizeEvent>

#include "OpenGLApps/OpenGLWidgetBase"
#include "Log"

namespace Ouquitoure
{

    OpenGLAppBase::OpenGLAppBase( const QString & name, QWidget * parent )
        : AppWindowBase( parent )
        , appName( name )
    {
        OQ_LOG_DEBUG << appName << " app ctor";
        setWindowTitle( appName );

        QWidget *     centralWidget = new QWidget{ this };
        QHBoxLayout * mainLayout    = new QHBoxLayout();
        setCentralWidget( centralWidget );
        centralWidget->setLayout( mainLayout );

        QSizePolicy sizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
        centralWidget->setSizePolicy( sizePolicy );

        QHBoxLayout * appLayout        = new QHBoxLayout();
        QGroupBox *   controlsGroupBox = new QGroupBox( "Controls" );
        controlsGroupBox->setSizePolicy( sizePolicy );
        controlsGroupBox->setMinimumSize( 480, 480 );

        viewDockWidget = new QDockWidget( centralWidget );
        viewDockWidget->setAllowedAreas( Qt::RightDockWidgetArea );
        viewDockWidget->setWindowTitle( "View" );
        OpenGLWidgetBase * viewOpenGLWidget = new OpenGLWidgetBase( appName, this );
        viewDockWidget->setWidget( viewOpenGLWidget );
        viewOpenGLWidget->setMinimumSize( 640, 480 );
        viewOpenGLWidget->setSizePolicy( sizePolicy );
        addDockWidget( Qt::RightDockWidgetArea, viewDockWidget );

        appLayout->addWidget( controlsGroupBox );

        mainLayout->addLayout( appLayout );
    }

    OpenGLAppBase::~OpenGLAppBase()
    {
        OQ_LOG_DEBUG << appName << " app dtor";
    }

    void OpenGLAppBase::resizeEvent( QResizeEvent * event )
    {
        resizeDocks( { viewDockWidget }, { event->size().width() / 2 }, Qt::Horizontal );
    }

} // namespace Ouquitoure
