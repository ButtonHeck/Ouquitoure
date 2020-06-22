#pragma once

#include "AppWindowBase"

namespace Ouquitoure
{
    class SoftwareAppBase : public AppWindowBase
    {
        Q_OBJECT
    public:
        explicit SoftwareAppBase( const QString & appName, QWidget * parent = nullptr );
        virtual ~SoftwareAppBase();

    protected:
        QString appName;
    };

} // namespace Ouquitoure
