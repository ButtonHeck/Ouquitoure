#pragma once

#include <QString>
#include <QPair>
#include <QVector>
#include <QPixmap>
#include <QUrl>

namespace Ouquitoure
{

    class AppDescription
    {
    public:
        using ReferenceInfo = QPair<QUrl, QString>;

        AppDescription();
        AppDescription( const QString &                name,
                        const QString &                author,
                        const QString &                email,
                        const QString &                brief,
                        const QString &                appImageFilename,
                        const QVector<ReferenceInfo> & references );

        void    setName( const QString & name );
        void    setAuthor( const QString & author );
        void    setEmail( const QString & email );
        void    setBrief( const QString & brief );
        void    setAppImage( const QString & appViewFilename );
        void    appReference( const ReferenceInfo & reference );
        QString getFullDescription() const;

    private:
        QString                name;
        QString                author;
        QString                email;
        QString                brief;
        QPixmap                appImage;
        QVector<ReferenceInfo> references;
    };

} // namespace Ouquitoure
