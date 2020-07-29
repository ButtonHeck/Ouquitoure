#pragma once

#include <QOpenGLWidget>
#include <QString>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_4_5_Core>

namespace Ouquitoure
{

    /**
     * @brief OpenGL widget base class
     */
    class OpenGLWidgetBase : public QOpenGLWidget, public QOpenGLFunctions_4_5_Core
    {
    public:
        explicit OpenGLWidgetBase( const QString & name, QWidget * parent = nullptr );
        virtual ~OpenGLWidgetBase();

        void initializeGL() override;
        void resizeGL( int width, int height ) override;

    protected:
        /**
         * @brief creates and adds OpenGL shader program to internal storage
         * @param types list of shader types provided
         * @param sources string sources of the shaders
         * @param programName name of the program
         * @return true if shader was compiled, linked and added successfully
         */
        bool addShaderProgram( QVector<QOpenGLShader::ShaderType> && types,
                               QVector<QString> &&                   sources,
                               const QString &                       programName = "main" );

        /**
         * @brief initializes all OpenGL buffers, vertex arrays etc.
         */
        virtual void initializeOpenGLObjects() = 0;
        /**
         * @brief initializes all shader programs
         */
        virtual void initializeOpenGLShaders() = 0;
        /**
         * @brief performs all cleanup routines for OpenGL objects and other stuff
         */
        virtual void cleanup() = 0;

    protected:
        QMap<QString, QOpenGLShaderProgram *> shaderPrograms;
        QString                               name;

    private:
        bool glFunctionsInitialized = false;
    };

} // namespace Ouquitoure
