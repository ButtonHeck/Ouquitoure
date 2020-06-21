#include "AppLibraryManager"

#include "OpenGLApps/ColoredTriangleApp"

namespace Ouquitoure
{

    AppLibraryManager::AppLibraryManager()
        : invisibleParentForApps()
    {
        openGLApps << new ColoredTriangleApp(&invisibleParentForApps);
    }

    QVector<AppInfo> AppLibraryManager::getAppInfos(APP_TYPE type) const
    {
        QVector<AppInfo> infos;
        switch(type)
        {
        case OPENGL_APP:
        {
            for (const auto & app : openGLApps)
            {
                infos << app->getInfo();
            }
            return infos;
        }
        case SOFTWARE_APP:
        {
            for (const auto & app : softwareApps)
            {
                infos << app->getInfo();
            }
            return infos;
        }
        }
    }

    QMainWindow * AppLibraryManager::getApplication(APP_TYPE appType, const QString & appName)
    {
        switch(appType)
        {
        case OPENGL_APP:
        {
            auto appIter = std::find_if(openGLApps.cbegin(), openGLApps.cend(), [&](OpenGLAppBase* application)
            {
                return application->getInfo().getName() == appName;
            });
            if (appIter != openGLApps.cend())
            {
                return *appIter;
            }
            else
            {
                return nullptr;
            }
        }
        case SOFTWARE_APP:
            auto appIter = std::find_if(softwareApps.cbegin(), softwareApps.cend(), [&](SoftwareAppBase * application)
            {
                return application->getInfo().getName() == appName;
            });
            if (appIter != softwareApps.cend())
            {
                return *appIter;
            }
            else
            {
                return nullptr;
            }
        }
    }

}
