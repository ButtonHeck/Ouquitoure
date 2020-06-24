#include "AppDescription"

namespace Ouquitoure
{

    AppDescription::AppDescription()
    {
    }

    AppDescription::AppDescription( const QString &                                name,
                                    const QString &                                author,
                                    const QString &                                email,
                                    const QString &                                brief,
                                    const QString &                                appImageFilename,
                                    const QVector<AppDescription::ReferenceInfo> & references )
        : name( name )
        , author( author )
        , email( email )
        , brief( brief )
        , references( references )
    {
        appImage.load( appImageFilename );
    }

    void AppDescription::setName( const QString & name )
    {
        this->name = name;
    }

    void AppDescription::setAuthor( const QString & author )
    {
        this->author = author;
    }

    void AppDescription::setEmail( const QString & email )
    {
        this->email = email;
    }

    void AppDescription::setBrief( const QString & brief )
    {
        this->brief = brief;
    }

    void AppDescription::setAppImage( const QString & appViewFilename )
    {
        appImage.load( appViewFilename );
    }

    void AppDescription::appReference( const AppDescription::ReferenceInfo & reference )
    {
        references << reference;
    }

    QString AppDescription::getFullDescription() const
    {
        QString result{"name: "};
        result.append(name);
        return result;
    }

} // namespace Ouquitoure
