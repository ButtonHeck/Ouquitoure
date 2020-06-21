#pragma once

#include <QVector>
#include "OpenGLApps/OpenGLAppBase"
#include "SoftwareApps/SoftwareAppBase"

namespace Ouquitoure
{
    class AppLibraryManager
    {
    public:
        AppLibraryManager();

        QVector<AppInfo> getAppInfos(APP_TYPE type) const;
        QMainWindow * getApplication(APP_TYPE appType, const QString & appName);

    private:
        QVector<OpenGLAppBase*> openGLApps;
        QVector<SoftwareAppBase*> softwareApps;
        QWidget invisibleParentForApps;
    };
}
