#pragma once

#include "Apps/OpenGL/OpenGLAppBase"
#include "Apps/OpenGL/OpenGLDrawFunctionsWidget"

namespace Ouquitoure
{

    /**
     * @brief OpenGL draw functions application class
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
