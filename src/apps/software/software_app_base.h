#pragma once

#include "Apps/AppWindowBase"

namespace Ouquitoure
{

    /**
     * @brief Software application base class
     */
    class SoftwareAppBase : public AppWindowBase
    {
        Q_OBJECT
    public:
        explicit SoftwareAppBase( const QString & appName, QWidget * parent = nullptr );
#ifdef QT_DEBUG
        virtual ~SoftwareAppBase();
#else
        virtual ~SoftwareAppBase() = default;
#endif

    protected:
        QString appName;
    };

} // namespace Ouquitoure
