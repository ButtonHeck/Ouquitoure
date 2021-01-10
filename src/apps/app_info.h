#pragma once

#include "Apps/AppType"
#include "Apps/AppDescription"

#include <QStringList>

namespace Ouquitoure
{

    /**
     * @brief Application information class
     */
    class AppInfo
    {
    public:
        AppInfo() = default;
        AppInfo( const QString & name, const std::initializer_list<QString> & tags, APP_TYPE type );
        [[nodiscard]] const QString &        getName() const noexcept;
        [[nodiscard]] const QStringList &    getTags() const noexcept;
        [[nodiscard]] APP_TYPE               getType() const noexcept;
        [[nodiscard]] AppDescription &       getDescription() noexcept;
        [[nodiscard]] const AppDescription & getDescription() const noexcept;

    private:
        QStringList    tags;
        APP_TYPE       type;
        AppDescription description;
    };

} // namespace Ouquitoure
