/*
 * This file is part of buteo-syncfw package
 *
 * Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
 *
 * Contact: Sateesh Kavuri <sateesh.kavuri@nokia.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * version 2.1 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */


#ifndef LOGMACROS_H
#define LOGMACROS_H

#include <QString>
#include <QTime>
#include <QDebug>

//! Helper macro for writing log messages. Avoid using directly.
#ifndef QT_NO_DEBUG
#define LOG_MSG_L(level, msg) (QDebug((QtMsgType)(level)) << __FILE__ << __LINE__ << ":" << msg)
#define LOG_MSG_L_PLAIN(level, msg) (QDebug((QtMsgType)(level)) << msg)
#define QDEBUG(...) qDebug(__VA_ARGS__)
#else
#define LOG_MSG_L(level, msg)
#define LOG_MSG_L_PLAIN(level, msg)
#define QDEBUG(...)
#endif

// This macro is defined in both debug and release builds.
#define LOG_MSG_L_ALWAYS(level, msg) (QDebug((QtMsgType)(level)) << __FILE__ << __LINE__ << ":" << msg)

//! Macros for writing log messages. Use these.
//! Messages with level below warning are enabled only in debug builds.
#define LOG_FATAL(msg) LOG_MSG_L_ALWAYS(QtFatalMsg, msg)
#define LOG_CRITICAL(msg) LOG_MSG_L_ALWAYS(QtCriticalMsg, msg)
#define LOG_WARNING(msg) LOG_MSG_L_ALWAYS(QtWarningMsg, msg)
#define LOG_PROTOCOL(msg) LOG_MSG_L(QtDebugMsg, msg)
#define LOG_INFO(msg) LOG_MSG_L(QtDebugMsg, msg)
#define LOG_DEBUG(msg) LOG_MSG_L(QtDebugMsg, msg)
#define LOG_TRACE(msg) LOG_MSG_L(QtDebugMsg, msg)
#define LOG_TRACE_PLAIN(msg) LOG_MSG_L_PLAIN(QtDebugMsg, msg)

/*!
 * Creates a trace message to log when the function is entered and exited.
 * Logs also to time spent in the function.
 */
#define FUNCTION_CALL_TRACE Buteo::LogTimer timerDebugVariable(QString(__PRETTY_FUNCTION__));

namespace Buteo {
    
/*!
 * \brief Helper class for timing function execution time.
 */
class LogTimer
{
public:
    /*!
    * \brief Constructor. Creates an entry message to the log.
    *
    * @param aFunc Name of the function.
    */
    LogTimer(const QString &aFunc) : iFunc(aFunc)
    {
        LOG_TRACE_PLAIN(iFunc << ":Entry");
        iTimer.start();
    }

    /*!
     * \brief Destructor. Creates an exit message to the log, including
     *        function execution time.
     */
    ~LogTimer()
    {
        LOG_TRACE_PLAIN(iFunc << ":Exit, execution time:" << iTimer.elapsed()
            << "ms");
    }

private:
    QTime iTimer;
    QString iFunc;
};

}

#endif // LOGMACROS_H

