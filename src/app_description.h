#pragma once

#include <QString>
#include <QPair>
#include <QVector>
#include <QUrl>

namespace Ouquitoure
{

    class AppDescription
    {
    public:
        using ReferenceInfo = QPair<QUrl, QString>;

        AppDescription() = default;
        AppDescription( const QString &                name,
                        const QString &                author,
                        const QString &                email,
                        const QString &                brief,
                        const QString &                appImageFilename,
                        const QVector<ReferenceInfo> & references,
                        const QString &                notes );

        void    setName( const QString & name );
        void    setAuthor( const QString & author );
        void    setEmail( const QString & email );
        void    setBrief( const QString & brief );
        void    setAppImage( const QString & appImageFilename );
        void    addReference( const ReferenceInfo & reference );
        void    setNotes( const QString & notes );
        QString getFullDescription() const;

    private:
        QString                name;
        QString                author;
        QString                email;
        QString                brief;
        QString                appImageFilename;
        QVector<ReferenceInfo> references;
        QString                notes;
    };

} // namespace Ouquitoure
