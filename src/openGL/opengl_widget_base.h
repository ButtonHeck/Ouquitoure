#pragma once

#include <QOpenGLWidget>
#include <QString>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

namespace Ouquitoure
{
    class OpenGLWidgetBase : public QOpenGLWidget, public QOpenGLFunctions
    {
    public:
        explicit OpenGLWidgetBase( const QString & name, QWidget * parent = nullptr );
        ~OpenGLWidgetBase();

        const QString & getName() const noexcept;

        void initializeGL() override;
        void resizeGL( int width, int height ) override;

    protected:
        bool addShaderProgram( QVector<QOpenGLShader::ShaderType> && types,
                               QVector<QString> &&                   sources,
                               const QString &                       programName = "main" );

    protected:
        QMap<QString, QOpenGLShaderProgram *> shaderPrograms;
        QString                               name;
    };

} // namespace Ouquitoure
