#pragma once

#include <QDebug>

class QTextEdit;
class QWidget;

namespace Ouquitoure
{
    class Logger
    {
    public:
        static void logHandler(QtMsgType messageType, const QMessageLogContext & logContext, const QString & message);
        static void instantiateCoreLogger( QWidget * parent );
        static QTextEdit & getCoreLogger();

    private:
        static QTextEdit * coreLogger;
    };
}
