#include "HoverStrategy.h"

#include <QRandomGenerator>

#include <cmath>

TelemetrySnapshot HoverStrategy::step(const TelemetrySnapshot &current, double dt)
{

    TelemetrySnapshot next = current;

    double jitter = 0.00001;

    next.latitude += randRange(-1.0, 1.0) * jitter;

    next.longitude += randRange(-1.0, 1.0) * jitter;

    next.heading = fmod(next.heading + randRange(-1.0, 1.0), 360.0);

    next.battery = std::max(0, next.battery - (int)(dt * 0.02));

    next.speed = std::max(0.0, next.speed * 0.98);

    return next;
}