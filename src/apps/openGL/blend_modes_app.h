#pragma once

#include "Apps/OpenGL/OpenGLAppBase"
#include "Apps/OpenGL/BlendModesWidget"

namespace Ouquitoure
{
    /**
     * @brief OpenGL blend modes application
     */
    class BlendModesApp : public OpenGLAppBase
    {
        Q_OBJECT
    public:
        BlendModesApp( const QString & appName, QWidget * parent );

    protected:
        void initializeDescription() override;

    private:
        BlendModesWidget viewWidget;
    };

} // namespace Ouquitoure
