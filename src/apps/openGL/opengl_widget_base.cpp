#include "Apps/OpenGL/OpenGLWidgetBase"
#include "Log"

#include <QOpenGLShader>
#include <QVector>

namespace Ouquitoure
{

    OpenGLWidgetBase::OpenGLWidgetBase( const QString & name, QWidget * parent )
        : QOpenGLWidget( parent )
        , name( name )
    {
        OQ_LOG_DEBUG << name << " widget ctor";
    }

    OpenGLWidgetBase::~OpenGLWidgetBase()
    {
        OQ_LOG_DEBUG << name << " widget dtor";
    }

    /**
     * @brief creates and adds OpenGL shader program to internal storage
     */
    bool OpenGLWidgetBase::addShaderProgram( QVector<QOpenGLShader::ShaderType> && types,
                                             QVector<QString> &&                   sources,
                                             const QString &                       programName )
    {
        if( !glFunctionsInitialized )
        {
            OQ_LOG_WARNING << "Could not add shader program as OpenGL functions were not initialized";
            return false;
        }
        QVector<QOpenGLShader *> shaders{ sources.size() };
        for( int shaderSourceIndex = 0; shaderSourceIndex < sources.size(); ++shaderSourceIndex )
        {
            QOpenGLShader * shader = new QOpenGLShader{ types[ shaderSourceIndex ] };
            shader->compileSourceCode( sources[ shaderSourceIndex ] );
            if( !shader->isCompiled() )
            {
                OQ_LOG_CRITICAL << name << " - Shader compilation error: " << shader->log();
                return false;
            }
            shaders << shader;
        }
        QOpenGLShaderProgram * shaderProgram = new QOpenGLShaderProgram;
        for( int shaderIndex = 0; shaderIndex < shaders.size(); shaderIndex++ )
        {
            shaderProgram->addShader( shaders[ shaderIndex ] );
        }
        shaderProgram->link();
        if( !shaderProgram->isLinked() )
        {
            OQ_LOG_CRITICAL << name << " - Shader program link error: " << shaderProgram->log();
            return false;
        }
        shaderPrograms.insert( programName, shaderProgram );
        return true;
    }

    void OpenGLWidgetBase::initializeGL()
    {
        OQ_LOG_INFO << name << " GL context initialization";
        initializeOpenGLFunctions();
        glFunctionsInitialized = true;
        makeCurrent();
    }

    void OpenGLWidgetBase::resizeGL( int width, int height )
    {
        glViewport( 0, 0, width, height );
    }

} // namespace Ouquitoure
