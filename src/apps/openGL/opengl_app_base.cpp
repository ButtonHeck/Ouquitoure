#include "Apps/OpenGL/OpenGLAppBase"

#include <QDockWidget>
#include <QResizeEvent>

#include "Apps/OpenGL/OpenGLWidgetBase"
#include "Log"

namespace Ouquitoure
{

    OpenGLAppBase::OpenGLAppBase( const QString & name, QWidget * parent )
        : AppWindowBase( parent )
        , appName( name )
        , appLayout( new QHBoxLayout )
        , controlsGroupBox( new QGroupBox( "Controls" ) )
    {
        OQ_LOG_DEBUG << appName << " app ctor";
        setWindowTitle( appName );

        QWidget *     centralWidget = new QWidget{ this };
        QHBoxLayout * mainLayout    = new QHBoxLayout();
        setCentralWidget( centralWidget );
        centralWidget->setLayout( mainLayout );

        QSizePolicy sizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
        centralWidget->setSizePolicy( sizePolicy );

        controlsGroupBox->setSizePolicy( sizePolicy );
        controlsGroupBox->setMinimumSize( 480, 480 );

        viewDockWidget = new QDockWidget( centralWidget );
        viewDockWidget->setAllowedAreas( Qt::RightDockWidgetArea );
        viewDockWidget->setWindowTitle( appName );
        viewDockWidget->setFeatures( QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable );
        addDockWidget( Qt::RightDockWidgetArea, viewDockWidget );

        appLayout->addWidget( controlsGroupBox );

        mainLayout->addLayout( appLayout );
    }

    OpenGLAppBase::~OpenGLAppBase()
    {
        OQ_LOG_DEBUG << appName << " app dtor";
    }

    /**
     * @brief sets given view widget as the dock widget contents
     */
    void OpenGLAppBase::installOpenGLViewWidget( OpenGLWidgetBase & widget )
    {
        viewDockWidget->setWidget( &widget );
        widget.setMinimumSize( 640, 480 );
        widget.setSizePolicy( centralWidget()->sizePolicy() );
        viewDockWidget->installEventFilter( &widget );
    }

    void OpenGLAppBase::resizeEvent( QResizeEvent * event )
    {
        resizeDocks( { viewDockWidget }, { event->size().width() / 2 }, Qt::Horizontal );
    }

    void OpenGLAppBase::closeEvent( QCloseEvent * event )
    {
        Q_UNUSED( event );
        OQ_LOG_DEBUG << appName << " closes";
        if( viewDockWidget->isFloating() )
        {
            viewDockWidget->setFloating( false );
        }
    }

} // namespace Ouquitoure
