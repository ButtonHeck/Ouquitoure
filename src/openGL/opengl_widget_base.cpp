#include "OpenGLApps/OpenGLWidgetBase"

#include "Log"

namespace Ouquitoure
{

    OpenGLWidgetBase::OpenGLWidgetBase( const QString & name, QWidget * parent )
        : QOpenGLWidget( parent )
        , name( name )
    {
        OQ_LOG_DEBUG << name << " widget ctor";
    }

    OpenGLWidgetBase::~OpenGLWidgetBase()
    {
        OQ_LOG_DEBUG << name << " widget dtor";
    }

    const QString & OpenGLWidgetBase::getName() const noexcept
    {
        return name;
    }

} // namespace Ouquitoure
