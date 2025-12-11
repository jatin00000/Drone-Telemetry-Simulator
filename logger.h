#pragma once

#include <QObject>
#include <QString>
#include <QMutex>

// Singleton class responsible for centralized, thread-safe logging.
class Logger : public QObject
{
    Q_OBJECT

public:
    // Static method to get the single instance of the Logger (Singleton Pattern).
    static Logger &instance();

    // Writes a log message, ensuring thread safety.
    void log(const QString &msg);

signals:
    // Emits the new log message for display in the UI or other connected components.
    void newLog(const QString &msg);

private:
    // Private constructor prevents direct instantiation outside of the class.
    Logger(QObject *parent = nullptr);
    // Explicitly default the destructor.
    ~Logger() override = default;
    // Mutex used to protect shared log access in multi-threaded environments.
    QMutex m_mutex;
};