#include "TelemetryModel.h"

TelemetryModel::TelemetryModel(QObject *parent) : QObject(parent) {}

TelemetrySnapshot TelemetryModel::snapshot()
{

    QMutexLocker locker(&m_mutex);

    return m_snapshot;
}

void TelemetryModel::updateFromSimulator(const TelemetrySnapshot &snap)
{

    {

        QMutexLocker locker(&m_mutex);

        // basic copy

        TelemetrySnapshot old = m_snapshot;

        m_snapshot = snap;

        // emit change signals outside lock as much as possible
    }

    emit telemetryUpdated();

    if (snap.battery <= 20)
    {

        emit batteryLow(snap.battery);
    }

    emit gpsFixChanged(snap.gpsFix);
}
