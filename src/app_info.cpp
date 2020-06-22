#include "AppInfo"

namespace Ouquitoure
{

    AppInfo::AppInfo( QString && name, QStringList && tags, APP_TYPE type )
        : name( name )
        , tags( tags )
        , type( type )
    {
    }

    AppInfo::AppInfo( const QString & name, const std::initializer_list<QString> & tags, Ouquitoure::APP_TYPE type )
        : name( name )
        , tags( tags )
        , type( type )
    {
    }

    const QString & AppInfo::getName() const noexcept
    {
        return name;
    }

    const QStringList & AppInfo::getTags() const noexcept
    {
        return tags;
    }

    APP_TYPE AppInfo::getType() const noexcept
    {
        return type;
    }

} // namespace Ouquitoure
