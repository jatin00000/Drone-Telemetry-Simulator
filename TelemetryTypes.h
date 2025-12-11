/******************************************************************************
 * TelemetryTypes.h
 * Author: Jatin Kumawat
 * Date: 12-12-2025
 *
 * Description:
 *   Data model representing drone telemetry at a single time frame.
 *
 *   - Holds all sensor-like values: GPS coordinates, altitude, heading,
 *  speed, battery, GPS fix type, and ID metadata
 *   - Used as the primary data exchange structure between simulator and UI
 ******************************************************************************/

#ifndef TELEMETRYTYPES_H
#define TELEMETRYTYPES_H

#pragma once
#include <QString>
#include <QMetaType> // Required for Q_DECLARE_METATYPE and thread safety in Qt signals/slots.
#include <cstdint>

// Structure holding a complete snapshot of the drone's telemetry data at a specific moment.
struct TelemetrySnapshot
{
    QString id;             // Unique identifier for the drone.
    double latitude = 0.0;  // Geographic latitude (degrees).
    double longitude = 0.0; // Geographic longitude (degrees).
    double altitude = 0.0;  // Altitude in meters.
    double heading = 0.0;   // Direction of travel (degrees 0-360).
    double speed = 0.0;     // Current velocity (m/s).
    int battery = 100;      // Remaining battery percentage (0-100).

    // Enumeration defining the quality of the GPS positional fix.
    enum class GpsFix
    {
        NoFix = 0,            // No reliable GPS lock.
        Fix2D = 1,            // 2-dimensional position fix (latitude/longitude).
        Fix3D = 2             // 3-dimensional position fix (latitude/longitude/altitude).
    } gpsFix = GpsFix::Fix3D; // The current GPS fix status.

    qint64 timestampMs = 0; // Timestamp of the measurement, in milliseconds.
};

// Makes TelemetrySnapshot usable in Qt signal/slot mechanism, especially across threads.
Q_DECLARE_METATYPE(TelemetrySnapshot)
// Makes the GpsFix enum usable in Qt signal/slot mechanism.
Q_DECLARE_METATYPE(TelemetrySnapshot::GpsFix)

#endif // TELEMETRYTYPES_H