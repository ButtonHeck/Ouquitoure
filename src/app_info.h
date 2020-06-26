#pragma once

#include <QString>
#include <QStringList>

#include <AppType>
#include <AppDescription>

namespace Ouquitoure
{

    /**
     * @brief Application information class
     */
    class AppInfo
    {
    public:
        AppInfo() = default;
        AppInfo( QString && name, QStringList && tags, APP_TYPE type );
        AppInfo( const QString & name, const std::initializer_list<QString> & tags, APP_TYPE type );
        const QString &        getName() const noexcept;
        const QStringList &    getTags() const noexcept;
        APP_TYPE               getType() const noexcept;
        AppDescription &       getDescription() noexcept;
        const AppDescription & getDescription() const noexcept;

    private:
        QString        name;
        QStringList    tags;
        APP_TYPE       type;
        AppDescription description;
    };

} // namespace Ouquitoure
