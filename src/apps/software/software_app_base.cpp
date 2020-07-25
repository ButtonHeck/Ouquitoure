#include "Apps/Software/SoftwareAppBase"
#include "Log"

#include <QLabel>

namespace Ouquitoure
{

    SoftwareAppBase::SoftwareAppBase( const QString & name, QWidget * parent )
        : AppWindowBase( parent )
        , appName( name )
    {
        OQ_LOG_DEBUG << appName << " app ctor";
        setWindowTitle( appName );

        QLabel * label = new QLabel( this );
        label->setText( "Software" );
    }

    SoftwareAppBase::~SoftwareAppBase()
    {
        OQ_LOG_DEBUG << appName << " app dtor";
    }

} // namespace Ouquitoure
