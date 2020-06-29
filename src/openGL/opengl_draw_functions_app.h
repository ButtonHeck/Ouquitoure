#pragma once

#include "OpenGLApps/OpenGLAppBase"
#include "OpenGLApps/OpenGLDrawFunctionsWidget"

namespace Ouquitoure
{

    /**
     * @brief OpenGL draw functions class
     */
    class OpenGLDrawFunctionsApp : public OpenGLAppBase
    {
        Q_OBJECT
    public:
        explicit OpenGLDrawFunctionsApp( const QString & appName, QWidget * parent );

    protected:
        void initializeDescription() override;

    private:
        OpenGLDrawFunctionsWidget viewWidget;
    };

} // namespace Ouquitoure
