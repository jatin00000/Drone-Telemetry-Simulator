#pragma once

#include <QString>
#include <memory>

class DroneSimulator; // Forward declaration of the simulator class.

// Namespace defining the available movement strategies for easy selection.
namespace StrategyType
{
    enum Type
    {
        Hover = 0,     // Strategy for keeping the drone nearly stationary.
        RandomWalk = 1 // Strategy for making the drone wander randomly.
    };
}

// Static factory class responsible for creating configured instances of the simulator.
class SimulatorFactory
{
public:
    // Static method: Creates a DroneSimulator instance with the specified ID and movement strategy.
    static DroneSimulator *createSingleDroneSimulator(const QString &droneId, int strategyType, QObject *parent = nullptr);
};