/******************************************************************************
 * HoverStrategy.h
 * Author: Jatin Kumawat
 * Date: 12-12-2025
 *
 * Description:
 *   Minimal drift “hover mode” strategy for drone simulation.
 *
 *   - Keeps drone almost stationary
 *   - Introduces small jitter to simulate real hover drift
 *   - Gradually reduces speed to 0 (hover stabilization)
 ******************************************************************************/

#pragma once

#include "utils.h"
#include "MovementStrategy.h"

// Implements a strategy where the drone attempts to remain stationary.
class HoverStrategy : public MovementStrategy
{
public:
    // Calculates and returns the next telemetry snapshot based on minimal drift movement.
    TelemetrySnapshot step(const TelemetrySnapshot &current, double dt) override;
};