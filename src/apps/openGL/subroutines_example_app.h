#pragma once

#include "Apps/OpenGL/OpenGLAppBase"
#include "Apps/OpenGL/SubroutinesExampleWidget"

namespace Ouquitoure
{
    /**
     * @brief Subroutines example application class
     */
    class SubroutinesExampleApp : public OpenGLAppBase
    {
        Q_OBJECT
    public:
        SubroutinesExampleApp( const QString & appName, QWidget * parent );

    protected:
        void initializeDescription() override;

    private:
        SubroutinesExampleWidget viewWidget;
    };

} // namespace Ouquitoure
