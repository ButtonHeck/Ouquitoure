#pragma once

#include "AppWindowBase"

namespace Ouquitoure
{
    class SoftwareAppBase : public AppWindowBase
    {
        Q_OBJECT
    public:
        explicit SoftwareAppBase( QWidget * parent = nullptr );
        virtual ~SoftwareAppBase() = default;

    protected:
    };
} // namespace Ouquitoure
