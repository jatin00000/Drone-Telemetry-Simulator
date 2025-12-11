/******************************************************************************
 * RandomWalkStrategy.h
 * Author: Jatin Kumawat
 * Date: 12-12-2025
 *
 * Description:
 *   Random Walk movement algorithm for drone simulation.
 *
 *   - Applies random heading changes per tick
 *   - Adjusts speed gradually within allowed limits
 *   - Moves drone in a pseudo-random direction each frame
 *   - Generates natural-looking wandering patterns
 ******************************************************************************/

#pragma once

#include "MovementStrategy.h"
#include "utils.h"

// Implements a strategy where the drone changes direction and speed randomly.
class RandomWalkStrategy : public MovementStrategy
{
public:
    // Calculates and returns the next telemetry snapshot based on random movement and heading changes.
    TelemetrySnapshot step(const TelemetrySnapshot &current, double dt) override;
};