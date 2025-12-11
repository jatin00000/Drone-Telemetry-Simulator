/******************************************************************************
 * DroneSimulator.h
 * Author: Jatin Kumawat
 * Date: 12-12-2025
 *
 * Description:
 *   Core real-time drone telemetry simulator component.
 *
 *   - Generates live telemetry updates (lat/long, altitude, speed, heading,
 *  battery, GPS fix state)
 *   - Uses QTimer for timed simulation ticks
 *   - Applies selected movement strategy (Strategy Pattern)
 *   - Emits telemetry snapshots via Qt signals for UI consumption (Observer Pattern)
 *
 ******************************************************************************/
#ifndef DRONESIMULATOR_H
#define DRONESIMULATOR_H

#include <QTimer>
#include <QObject>
#include <QDateTime>
#include <memory>
#include "TelemetryTypes.h"
#include "MovementStrategy.h"
#include "utils.h"

class DroneSimulator : public QObject
{
    Q_OBJECT

public:
    explicit DroneSimulator(const QString &id, QObject *parent = nullptr); // Constructor: Initializes the simulator with a unique ID.

    void start(); // Starts the simulation timer.

    void stop(); // Stops the simulation timer.

    void setStrategy(std::unique_ptr<MovementStrategy> strategy); // Sets the movement behavior (Strategy Pattern).

signals:

    void simulatedTick(const TelemetrySnapshot &); // Emits the current telemetry state at each tick.

    void eventOccurred(const QString &); // Emits a general event or status message.

private slots:

    void onTick(); // Slot: Called every time the internal timer fires.

private:
    QString m_id; // Unique identifier for this drone instance.

    TelemetrySnapshot m_state; // The current simulated telemetry state of the drone.

    QDateTime m_lastUpdate; // Timestamp of the last simulation state update.

    QTimer *m_timer; // Timer responsible for driving the simulation ticks.

    std::unique_ptr<MovementStrategy> m_strategy; // The current strategy controlling drone movement.
};

#endif // DRONESIMULATOR_H