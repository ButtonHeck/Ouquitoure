#include "Apps/OpenGL/OpenGLWidgetBase"
#include "Log"

#include <QOpenGLShader>
#include <QVector>
#include <QFile>

namespace Ouquitoure
{

    OpenGLWidgetBase::OpenGLWidgetBase( const QString & name, QWidget * parent )
        : QOpenGLWidget( parent )
        , name( name )
    {
        OQ_LOG_DEBUG << name << " widget ctor";
    }

#ifdef QT_DEBUG
    OpenGLWidgetBase::~OpenGLWidgetBase()
    {
        OQ_LOG_DEBUG << name << " widget dtor";
    }
#endif

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

    void OpenGLWidgetBase::openGLShaderProgramsCleanup()
    {
        for( auto & shaderProgram: shaderPrograms.values() )
        {
            glDeleteProgram( shaderProgram->programId() );
        }
        shaderPrograms.clear();
    }

    void OpenGLWidgetBase::initializeOpenGLMainShaderProgram( const char * dirName )
    {
        QString          shadersPath = QString{ ":/shaders/" }.append( dirName );
        QVector<QString> shaderSources;
        QFile            vertexShaderFile( QString{ shadersPath }.append( "/main.vs" ) );
        if( vertexShaderFile.open( QIODevice::ReadOnly ) )
        {
            shaderSources << vertexShaderFile.readAll();
        }
        vertexShaderFile.close();
        QFile fragmentShaderFile( QString{ shadersPath }.append( "/main.fs" ) );
        if( fragmentShaderFile.open( QIODevice::ReadOnly ) )
        {
            shaderSources << fragmentShaderFile.readAll();
        }
        fragmentShaderFile.close();

        addShaderProgram( { QOpenGLShader::Vertex, QOpenGLShader::Fragment }, std::forward<decltype( shaderSources )>( shaderSources ) );
    }

    void OpenGLWidgetBase::initializeGL()
    {
        OQ_LOG_INFO << name << " GL context initialization";
        initializeOpenGLFunctions();
        glFunctionsInitialized = true;
        makeCurrent();

        /* QDockWidget (un)docking invokes reinitialization of a GL context,
         * thus every OpenGL related objects (shader programs, buffers etc.) should be deleted explicitly
         * (if any of them were created during previous context initialization)
         */
        cleanup();
    }

    void OpenGLWidgetBase::resizeGL( int width, int height )
    {
        glViewport( 0, 0, width, height );
    }

} // namespace Ouquitoure
