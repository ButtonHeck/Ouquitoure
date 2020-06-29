#pragma once

#include "OpenGLApps/OpenGLWidgetBase"

namespace Ouquitoure
{

    /**
     * @brief OpenGL draw functions view widget class
     */
    class OpenGLDrawFunctionsWidget : public OpenGLWidgetBase
    {
        Q_OBJECT
    public:
        explicit OpenGLDrawFunctionsWidget( const QString & name, QWidget * parent = nullptr );
        ~OpenGLDrawFunctionsWidget();

        void initializeGL() override;
        void paintGL() override;

    protected:
        void initializeOpenGLObjects() override;
        void initializeOpenGLShaders() override;
        void cleanup() override;

    private:
    };

} // namespace Ouquitoure
