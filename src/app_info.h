#pragma once

#include <QString>
#include <QStringList>

#include <AppType>

namespace Ouquitoure
{
    class AppInfo
    {
    public:
        AppInfo() = default;
        AppInfo(QString && name, QStringList && tags, APP_TYPE type);
        AppInfo(const char * name, const std::initializer_list<QString> & tags, APP_TYPE type);
        const QString & getName() const noexcept;
        const QStringList & getTags() const noexcept;
        APP_TYPE getType() const noexcept;

    private:
        QString name;
        QStringList tags;
        APP_TYPE type;
    };
}
