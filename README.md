# DroneTelemetrySimulator – Real-Time Drone Telemetry Desktop Simulator

A **Qt 6.x Desktop Application** that simulates real-time drone telemetry, including GPS coordinates, heading, altitude, speed, battery, and GPS fix quality.

-----

## Features

  * **Live Telemetry Simulation**
      * Auto-updating drone position (lat/long), calculated heading, speed, and altitude.
      * GPS Fix state (3D Fix, 2D Fix, No Fix).
      * Battery drain simulation.
      * Random drift & event simulation (e.g., GPS loss).
  * **Movement Strategies (Pluggable)**
      * **`RandomWalkStrategy`**: Randomized movement, heading changes, and speed variance.
      * **`HoverStrategy`**: Small jitter movements around a fixed position.
      * Easily add new movement strategies via the **Strategy Pattern**.
  * **UI Integration (Qt Widgets)**
      * Clean UI to display live telemetry.
      * Decoupled from logic—UI only listens to signals.
  * **Robust Update Loop**
      * Uses `QTimer` for periodic ticks.
      * Uses differential timestamps (`QDateTime`) for frame-accurate $\Delta t$.

-----

##  Installation

1.  Install **Qt 6.x** (Core, Gui, Widgets, and WebSockets modules are required).
2.  Download or clone the source code.
3.  Open the project in **Qt Creator**.
4.  During configuration, set the compiler to **MinGW 64-bit**.
5.  To run in **debug mode**:
    > Set the build directory to `..\Debug`
6.  To run in **release mode**:
    > Set the build directory to `..\Release`
7.  Build and run the project as usual.

-----

##  Usage

  * Launch the application.
  * Select a movement strategy (Random Walk / Hover).
  * Press **Start Simulation**.
  * View real-time telemetry updates.
  * Press **Stop Simulation** to pause.

The simulator updates position, heading, speed, altitude, and battery in real-time.

-----

##  Architecture Overview

### A. Core Components (Logic Layer)

  * **`DroneSimulator`**
      * Generates telemetry via timer events (`QTimer::timeout`).
      * Computes $\Delta t$ using `QDateTime`.
      * Emits telemetry updates using Qt signals.
  * **`DroneWorker`**
      * Wraps and executes `DroneSimulator` in its own `QThread` for non-blocking UI.
  * **`TelemetrySnapshot`**
      * Data structure holding all drone state values.
  * **`TelemetryModel`**
      * Manages the current state of `TelemetrySnapshot` and ensures thread-safe updates.
  * **`Logger`**
      * Provides a centralized, thread-safe mechanism for system logging.
  * **Movement Strategies**
      * `MovementStrategy` (abstract base interface).
      * `RandomWalkStrategy`.
      * `HoverStrategy`.

### B. Application Startup Flow

1.  **`main.cpp`**
      * Initializes the system, creates the `MainWindow`, and retrieves the `Logger` instance.
      * Sets up the simulator instance and the thread (`DroneWorker`).
      * Connects signals between the simulator and the UI table/chart (`simulatedTick` signal).
2.  **`MainWindow` Setup**
      * Allows the user to choose the movement strategy.
      * Displays live telemetry data.
      * Provides controls for start/stop.
3.  **`DroneSimulator`**
      * On start: begins `QTimer` @ 500ms.
      * On each tick:
          * Calculates $\Delta t$.
          * Applies the current movement strategy.
          * Emits the updated `TelemetrySnapshot`.
4.  **UI Layer**
      * Observes data updates from the `TelemetryModel` and `DroneSimulator`.
      * Displays values in real-time (Observer pattern).

-----

## Design Patterns Used

### 1\. Strategy Pattern

**Where:** Movement logic, allowing dynamic swapping of drone behavior.

| Interface | Implementations |
| :--- | :--- |
| `MovementStrategy` | `RandomWalkStrategy`, `HoverStrategy` |

### 2\. Observer Pattern (Qt Signals/Slots)

**Where:** Telemetry updates flow from the source to the display layer.

```
DroneSimulator → TelemetryModel → MainWindow (UI)
```

### 3\. Factory Pattern

**Where:** Object creation.

  * `SimulatorFactory` — Responsible for instantiating and configuring `DroneSimulator` objects with specific strategies.

### 4\. Singleton Pattern

**Where:** System logging.

  * `Logger` — Ensures only a single, globally accessible, and thread-safe instance exists to handle all log messages.