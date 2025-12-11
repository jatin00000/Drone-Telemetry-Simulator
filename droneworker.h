#pragma once

#include <QObject>
#include <QThread>
#include "DroneSimulator.h"

// Simple wrapper that owns a QThread and a DroneSimulator moved into it
class DroneWorker : public QObject
{ // Class manages the life cycle of a simulator running in its own thread.
    Q_OBJECT

public:
    explicit DroneWorker(QObject *parent = nullptr); // Constructor: Initializes the thread object.

    ~DroneWorker() override; // Destructor: Cleans up the worker thread safely.

    void startSimulator(DroneSimulator *sim); // Moves the simulator object to this worker's thread and starts the thread.

    void stopSimulator(); // Stops the simulator's internal processes and quits the worker thread.

signals:

    void started(); // Signal emitted when the worker thread and simulator have successfully started.

    void stopped(); // Signal emitted when the worker thread and simulator have successfully stopped.

private:
    QThread m_thread; // The dedicated thread where the simulator will run.

    DroneSimulator *m_sim = nullptr; // Pointer to the DroneSimulator instance managed by this worker.
};