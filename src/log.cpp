#include "Log"

#include <QTime>

namespace Ouquitoure
{
    /**
     * @brief custom message handler callback. Prints message time, message type, its context (if full logging is used)
     * and then the message itself
     */
    void logHandler( QtMsgType messageType, const QMessageLogContext & logContext, const QString & message )
    {
        QTime time = QTime::currentTime();

        QString fullMessage = time.toString( Qt::TextDate ).append( ": " );
        switch( messageType )
        {
        case QtDebugMsg:
            fullMessage.append( "[DEBUG]: " );
            break;
        case QtWarningMsg:
            fullMessage.append( "[WARNING]: " );
            break;
        case QtCriticalMsg:
            fullMessage.append( "[CRITICAL]: " );
            break;
        case QtFatalMsg:
            fullMessage.append( "[FATAL]: " );
            break;
        case QtInfoMsg:
            fullMessage.append( "[INFO]: " );
            break;
        }

        if( message.startsWith( OQ_LOG_PRECISION_FULL ) )
        {
            QString file{ logContext.file };
            file = file.right( file.size() - file.lastIndexOf( '\\' ) - 1 );
            QString func{ logContext.function };
            func = func.right( func.size() - func.lastIndexOf( ':' ) - 1 );
            fullMessage.append( file )
                .append( " (line " )
                .append( QString::number( logContext.line ) )
                .append( ") in " )
                .append( func )
                .append( ": " );
            fullMessage.append( message );
            fullMessage.remove( OQ_LOG_PRECISION_FULL );
        }
        else
        {
            fullMessage.append( message );
            fullMessage.remove( OQ_LOG_PRECISION_SHORT );
        }

        qInfo().noquote() << fullMessage;
    }
} // namespace Ouquitoure
