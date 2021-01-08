#pragma once

#include "Apps/OpenGL/OpenGLAppBase"
#include "Apps/OpenGL/OpenGLDrawFunctionsWidget"

namespace Ouquitoure
{
    class KeybindingsManager;

    /**
     * @brief OpenGL draw functions application class
     */
    class OpenGLDrawFunctionsApp : public OpenGLAppBase
    {
        Q_OBJECT
    public:
        OpenGLDrawFunctionsApp( const QString & appName, QWidget * parent, const KeybindingsManager & keybindingsManager );

    protected:
        void initializeDescription() override;

    private:
        OpenGLDrawFunctionsWidget viewWidget;
    };

} // namespace Ouquitoure
