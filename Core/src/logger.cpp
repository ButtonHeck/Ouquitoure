#include "logger.h"

#include <QTextEdit>
#include <QTime>

namespace Ouquitoure
{
    QTextEdit * Logger::coreLogger;

    void Logger::logHandler(QtMsgType messageType, const QMessageLogContext & logContext, const QString & message)
    {
        auto & coreLogger = Ouquitoure::Logger::getCoreLogger();
        QTime time = QTime::currentTime();
        QString outputString = time.toString(Qt::TextDate).append(": ");
        QString file{logContext.file};
        file = file.right(file.size() - file.lastIndexOf('\\') - 1 );
        QString func{logContext.function};
        func = func.right( func.size() - func.lastIndexOf(':') - 1 );
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

        QTextCursor cursor = coreLogger.textCursor();
        QTextCharFormat boldFormat;
        boldFormat.setFontWeight(QFont::Bold);
        QTextCharFormat plainFormat;        

        outputString.append(file)
                    .append(" (line ")
                    .append(QString::number(logContext.line))
                    .append(") in ")
                    .append(func)
                    .append(": ");
        cursor.insertText(outputString, plainFormat);
        cursor.insertText(message, boldFormat);
        cursor.insertText("\n");
    }

    void Logger::instantiateCoreLogger(QWidget * parent)
    {
        if(!coreLogger)
        {
            coreLogger = new QTextEdit(parent);
        }
    }

    QTextEdit & Logger::getCoreLogger()
    {
        return *coreLogger;
    }

}
