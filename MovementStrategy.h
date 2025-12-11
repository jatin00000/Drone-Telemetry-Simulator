/******************************************************************************
 * MovementStrategy.h
 * Author: Jatin Kumawat
 * Date: 12-12-2025
 *
 * Description:
 *   Abstract base class defining the movement behavior for the drone.
 *
 *   - Encapsulates navigation algorithms
 *   - Implemented by multiple strategy classes (Hover, Random Walk, etc.)
 *   - Allows dynamic switching of movement patterns at runtime
 *
 ******************************************************************************/

#ifndef MOVEMENTSTRATEGY_H
#define MOVEMENTSTRATEGY_H
#pragma once

#include "TelemetryTypes.h"

// Abstract base class defining the interface for all movement algorithms (Strategy Pattern).
class MovementStrategy
{
public:
    virtual ~MovementStrategy() = default; // Virtual destructor ensures proper cleanup of derived classes.

    // dt in seconds
    // Pure virtual function: Calculates and returns the next telemetry state based on the movement logic.
    virtual TelemetrySnapshot step(const TelemetrySnapshot &current, double dt) = 0;
};

#endif // MOVEMENTSTRATEGY_H