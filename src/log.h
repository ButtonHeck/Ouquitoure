#pragma once

#include <QDebug>

#define OQ_LOG_ALWAYS_FULL false
#define OG_LOG_FORCE_NOOP  false

#define OQ_LOG_PRECISION_FULL "@Ouqre-log-full"
#if( OG_LOG_FORCE_NOOP )
struct logSinkhole
{
    template<typename T>
    inline logSinkhole & operator<<( T )
    {
        return *this;
    }
};
    #define OQ_LOG_DEBUG_FULL    logSinkhole()
    #define OQ_LOG_WARNING_FULL  logSinkhole()
    #define OQ_LOG_CRITICAL_FULL logSinkhole()
    #define OQ_LOG_INFO_FULL     logSinkhole()
    #define OQ_LOG_FATAL_FULL    logSinkhole()
#else
    #define OQ_LOG_DEBUG_FULL    qDebug().nospace() << OQ_LOG_PRECISION_FULL
    #define OQ_LOG_WARNING_FULL  qWarning().nospace() << OQ_LOG_PRECISION_FULL
    #define OQ_LOG_CRITICAL_FULL qCritical().nospace() << OQ_LOG_PRECISION_FULL
    #define OQ_LOG_INFO_FULL     qInfo().nospace() << OQ_LOG_PRECISION_FULL
    #define OQ_LOG_FATAL_FULL    qFatal().nospace() << OQ_LOG_PRECISION_FULL
#endif

#if( OQ_LOG_ALWAYS_FULL || OG_LOG_FORCE_NOOP )
    #define OQ_LOG_PRECISION_SHORT OQ_LOG_PRECISION_FULL
    #define OQ_LOG_DEBUG           OQ_LOG_DEBUG_FULL
    #define OQ_LOG_WARNING         OQ_LOG_WARNING_FULL
    #define OQ_LOG_CRITICAL        OQ_LOG_CRITICAL_FULL
    #define OQ_LOG_INFO            OQ_LOG_INFO_FULL
    #define OQ_LOG_FATAL           OQ_LOG_FATAL_FULL
#else
    #define OQ_LOG_PRECISION_SHORT "@Ouqre-log-short"
    #define OQ_LOG_DEBUG           qDebug().nospace() << OQ_LOG_PRECISION_SHORT
    #define OQ_LOG_WARNING         qWarning().nospace() << OQ_LOG_PRECISION_SHORT
    #define OQ_LOG_CRITICAL        qCritical().nospace() << OQ_LOG_PRECISION_SHORT
    #define OQ_LOG_INFO            qInfo().nospace() << OQ_LOG_PRECISION_SHORT
    #define OQ_LOG_FATAL           qFatal().nospace() << OQ_LOG_PRECISION_SHORT
#endif

namespace Ouquitoure
{
    void logHandler( QtMsgType messageType, const QMessageLogContext & logContext, const QString & message );
}
