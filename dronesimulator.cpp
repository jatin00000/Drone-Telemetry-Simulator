#include "DroneSimulator.h"

#include <QTimer>

#include <QRandomGenerator>

#include <cmath>

DroneSimulator::DroneSimulator(const QString &id, QObject *parent)

    : QObject(parent),

      m_id(id),

      m_timer(new QTimer(this))

{

    m_state.id = id;

    connect(m_timer, &QTimer::timeout, this, &DroneSimulator::onTick);
}

void DroneSimulator::setStrategy(std::unique_ptr<MovementStrategy> strategy)
{

    m_strategy = std::move(strategy);
}

void DroneSimulator::start()
{

    m_lastUpdate = QDateTime::currentDateTime();

    m_timer->start(500);
}

void DroneSimulator::stop()
{

    m_timer->stop();
}

void DroneSimulator::onTick()
{

    if (!m_strategy)

        return;

    auto now = QDateTime::currentDateTime();

    double dt = m_lastUpdate.msecsTo(now) / 1000.0;

    m_lastUpdate = now;

    TelemetrySnapshot next = m_strategy->step(m_state, dt);

    // Add tiny GPS drift

    next.latitude += randRange(-1e-6, 1e-6);

    next.longitude += randRange(-1e-6, 1e-6);

    // Simulate GPS loss

    if (randRange(0.0, 1.0) < 0.01)
    {

        next.gpsFix = TelemetrySnapshot::GpsFix::NoFix;
    }

    // Auto battery drain

    next.battery = std::max(0, next.battery - 1);

    m_state = next;

    emit simulatedTick(next);
}