#pragma once

#include <QOpenGLWidget>
#include <QString>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_4_5_Core>

namespace Ouquitoure
{
    class OpenGLWidgetBase : public QOpenGLWidget, public QOpenGLFunctions_4_5_Core
    {
    public:
        explicit OpenGLWidgetBase( const QString & name, QWidget * parent = nullptr );
        virtual ~OpenGLWidgetBase();

        void initializeGL() override;
        void resizeGL( int width, int height ) override;

    protected:
        bool addShaderProgram( QVector<QOpenGLShader::ShaderType> && types,
                               QVector<QString> &&                   sources,
                               const QString &                       programName = "main" );

        virtual void initializeOpenGLObjects() = 0;
        virtual void initializeOpenGLShaders() = 0;
        virtual void cleanup()                 = 0;

    protected:
        QMap<QString, QOpenGLShaderProgram *> shaderPrograms;
        QString                               name;

    private:
        bool glFunctionsInitialized = false;
    };

} // namespace Ouquitoure
