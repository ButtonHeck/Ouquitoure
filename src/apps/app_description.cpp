#include "Apps/AppDescription"

namespace Ouquitoure
{

    AppDescription::AppDescription( const QString &                name,
                                    const QString &                author,
                                    const QString &                email,
                                    const QString &                brief,
                                    const QString &                appImageFilename,
                                    const QVector<ReferenceInfo> & references,
                                    const QString &                notes )
        : name( name )
        , author( author )
        , email( email )
        , brief( brief )
        , appImageFilename( appImageFilename )
        , references( references )
        , notes( notes )
    {
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

    void AppDescription::setAppImage( const QString & appImageFilename )
    {
        this->appImageFilename = appImageFilename;
    }

    void AppDescription::addReference( const AppDescription::ReferenceInfo & reference )
    {
        references << reference;
    }

    void AppDescription::setNotes( const QString & notes )
    {
        this->notes = notes;
    }

    QString AppDescription::getFullDescription() const
    {
        QStringList text{ "<!DOCTYPE html><html><head>" };

        // meta info
        text << "<meta charset=\"utf-8\">";
        text << "<title>" << name << "</title>";
        text << "<style>";
        text << "h1 { font-family: 'Monospace'; }";
        text << "p { font-family: 'Monospace'; font-size: 14pt; }";
        text << "</style>";
        text << "</head>";

        // body begin
        text << "<body>";

        // application name
        text << "<h1>" << name << "</h1>";

        // application author
        text << "<p><u>Author"
             << "</u>"
             << ": " << author << "</p>";

        // author E-mail
        text << "<p><u>E-mail"
             << "</u>"
             << ": " << email << "</p>";

        // application brief info
        text << "<p><u>Brief"
             << "</u>"
             << ": " << brief << "</p>";

        // application image
        text << "<p><u>Image</u>:<br>";
        if( appImageFilename != "" )
        {
            text << "<img src='" << appImageFilename << "' height='400' width='600'/></p>";
        }
        else
        {
            text << "none</p>";
        }

        // application references links
        text << "<p><u>References</u>:<br>";
        for( auto & reference: references )
        {
            text << "<u>" << reference.first.url() << "</u><br>";
            text << "<i>" << reference.second << "</i><br>";
        }
        text << "</p>";

        // application additional notes
        text << "<p><u>Notes"
             << "</u>"
             << ": " << notes << "</p>";

        // body end
        text << "</body></html>";

        return text.join( "" );
    }

} // namespace Ouquitoure
