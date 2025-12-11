#include "Logger.h"

#include <QDateTime>

Logger &Logger::instance()
{

    static Logger inst;

    return inst;
}

Logger::Logger(QObject *parent) : QObject(parent) {}

void Logger::log(const QString &msg)
{

    QMutexLocker locker(&m_mutex);

    QString entry = QDateTime::currentDateTime().toString(Qt::ISODate) + " - " + msg;

    // emit as queued to be thread-safe when invoked from other threads

    emit newLog(entry);
}