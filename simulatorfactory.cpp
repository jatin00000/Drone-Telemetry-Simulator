#include "SimulatorFactory.h"

#include "DroneSimulator.h"

#include "HoverStrategy.h"

#include "RandomWalkStrategy.h"

#include "Logger.h"

DroneSimulator *SimulatorFactory::createSingleDroneSimulator(const QString &droneId, int strategyType, QObject *parent)
{

    DroneSimulator *sim = new DroneSimulator(droneId, parent);

    std::unique_ptr<MovementStrategy> strat;

    if (strategyType == StrategyType::RandomWalk)
    {

        strat = std::make_unique<RandomWalkStrategy>();
    }
    else
    {

        strat = std::make_unique<HoverStrategy>();
    }

    sim->setStrategy(std::move(strat));

    Logger::instance().log(QString("Factory: Created simulator %1 with strategy %2").arg(droneId).arg(strategyType));

    return sim;
}