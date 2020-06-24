#include "AppDescription"

namespace Ouquitoure
{

    AppDescription::AppDescription( const QString &                                name,
                                    const QString &                                author,
                                    const QString &                                email,
                                    const QString &                                brief,
                                    const QString &                                appImageFilename,
                                    const QVector<AppDescription::ReferenceInfo> & references,
                                    const QString &                                notes )
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

    void AppDescription::appReference( const AppDescription::ReferenceInfo & reference )
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
        text << "<meta charset=\"utf-8\">";
        text << "<title>" << name << "</title>";
        text << "<style>";
        text << "h1 { font-family: 'Times New Roman', Times, serif; }";
        text << "p { font-family: 'Times New Roman', Times, serif; font-size: 14pt; }";
        text << "</style>";

        text << "</head>";

        text << "<body>";

        text << "<h1>" << name << "</h1>";
        text << "<p><u>Author"
             << "</u>"
             << ": " << author << "</p>";
        text << "<p><u>E-mail"
             << "</u>"
             << ": " << email << "</p>";
        text << "<p><u>Brief"
             << "</u>"
             << ": " << brief << "</p>";
        text << "<p><u>Image</u>:<br>"
             << "<img src='" << appImageFilename << "' height='300' width='480'/></p>";
        text << "<p><u>References</u>:<br>";
        for( auto & reference: references )
        {
            text << "<u>" << reference.first.url() << "</u><br>";
            text << reference.second << "<br>";
        }
        text << "</p>";
        text << "<p><u>Notes"
             << "</u>"
             << ": " << notes << "</p>";

        text << "</body></html>";

        return text.join( "" );
    }

} // namespace Ouquitoure
