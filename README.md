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

- - -
## Unit & Integration Tests

This project tests to ensure correctness of movement strategies and telemetry stability.
All test executables are located inside:

```
/Tests
   ├── test_randomwalk.cpp
   └── test_hover.cpp
```

Qt’s built-in **QtTest framework** is used.

---

### 1. TestRandomWalk – RandomWalk Strategy Validation

The **RandomWalkStrategy** introduces heading changes, variable speed, and real movement across each tick.
The unit test ensures:

#### **Test Cases**

| Test                           | Purpose                                                                                       |
| ------------------------------ | --------------------------------------------------------------------------------------------- |
| `test_step_changes_position()` | Confirms that the strategy results in real movement (lat/long change) when initial speed > 0. |
| `test_speed_non_negative()`    | Ensures the computed speed never becomes negative.                                            |
| `test_heading_within_bounds()` | Ensures heading remains within 0–360 degrees.                                                 |


### 2. TestHover – Hover Strategy Stability Tests

The **HoverStrategy** simulates hovering in place with very small jitter/noise.
This test ensures the drone does **not move significantly**.

#### **Test Cases**

| Test                          | Purpose                                                                                 |
| ----------------------------- | --------------------------------------------------------------------------------------- |
| `test_hover_small_movement()` | Ensures tiny jitter remains within a safe tolerance (EPS) and the drone does not drift. |

- - -

### How the Tests Are Built (CMake)

Each test is compiled as a separate standalone executable using QtTest.

---

### Running Tests in Qt Creator
#### **Method 1 – Run All Tests (Recommended)**

Use the integrated test runner:

1. Open the menu
   **Tools → Tests**
2. Select:
   **Run All Tests**
   *(Shortcut: `Alt + Shift + T`, then `Alt + A`)*

This runs **both** test suites:

* TestHover
* TestRandomWalk

Qt Creator will open the *Test Results* panel automatically.

---

#### **Method 2 – Run Selected Tests**

1. Go to
   **Tools → Tests**
2. Choose:
   **Run Selected Tests**
   *(Shortcut: `Alt + Shift + T`, `Alt + R`)*
3. Qt Creator will execute only the chosen test executable.

This is useful when working on a single strategy.

---

### **Viewing Results**

After running tests, open the **Test Results** panel:

* Shows pass/fail status
* Shows execution time (in ms)
* Expands to show each test function
* Green "PASS" indicators confirm success

Example result view:

```
PASS    Executing test case TestHover
PASS    Executing test function test_hover_small_movement
PASS    Executing test case TestRandomWalk
PASS    Executing test function test_step_changes_position
PASS    Executing test function test_speed_non_negative
PASS    Executing test function test_heading_within_bounds
```

You will also see a summary at the top such as:

```
Test summary: 8 passes, 0 fails (4 ms)
```
