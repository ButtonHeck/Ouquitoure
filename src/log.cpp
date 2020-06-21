#include "Log"

#include <QTime>

namespace Ouquitoure
{
    void logHandler(QtMsgType messageType, const QMessageLogContext & logContext, const QString & message)
    {
        QTime time = QTime::currentTime();

        QString outputString = time.toString(Qt::TextDate).append(": ");
        switch(messageType)
        {
        case QtDebugMsg:
            outputString.append("[DEBUG]: ");
            break;
        case QtWarningMsg:
            outputString.append("[WARNING]: ");
            break;
        case QtCriticalMsg:
            outputString.append("[CRITICAL]: ");
            break;
        case QtFatalMsg:
            outputString.append("[FATAL]: ");
            break;
        case QtInfoMsg:
            outputString.append("[INFO]: ");
            break;
        }

        if (message.startsWith(OQ_LOG_PRECISION_FULL))
        {
            QString file{logContext.file};
            file = file.right(file.size() - file.lastIndexOf('\\') - 1 );
            QString func{logContext.function};
            func = func.right( func.size() - func.lastIndexOf(':') - 1 );
            outputString.append(file)
                        .append(" (line ")
                        .append(QString::number(logContext.line))
                        .append(") in ")
                        .append(func)
                        .append(": ");
            outputString.append(message);
            outputString.remove(OQ_LOG_PRECISION_FULL);
        }
        else
        {
            outputString.append(message);
            outputString.remove(OQ_LOG_PRECISION_SHORT);
        }

        qInfo().noquote() << outputString;
    }
}
