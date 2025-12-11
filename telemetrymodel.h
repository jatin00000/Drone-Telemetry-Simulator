#ifndef TELEMETRYMODEL_H
#define TELEMETRYMODEL_H

#pragma once
#include <QObject>
#include <QMutex>
#include "TelemetryTypes.h"

// Model class that holds the drone's current telemetry state and manages thread-safe access.
class TelemetryModel : public QObject
{
    Q_OBJECT

public:
    explicit TelemetryModel(QObject *parent = nullptr); // Constructor: Initializes the model object.

    TelemetrySnapshot snapshot(); // Returns a copy of the current telemetry state in a thread-safe manner.

public slots:

    // Slot: Receives new telemetry data from the simulator and updates the internal state.
    void updateFromSimulator(const TelemetrySnapshot &snap);

signals:

    void telemetryUpdated(); // Signal emitted whenever the internal telemetry data has changed.

    void batteryLow(int pct); // Signal emitted when the battery level drops below a critical threshold.

    void gpsFixChanged(TelemetrySnapshot::GpsFix newFix); // Signal emitted when the GPS fix status changes.

private:
    TelemetrySnapshot m_snapshot; // The internal structure holding the most recent telemetry data.

    QMutex m_mutex; // Mutex to ensure thread-safe read/write access to m_snapshot.
};

#endif // TELEMETRYMODEL_H