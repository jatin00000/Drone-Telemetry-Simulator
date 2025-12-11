#include "RandomWalkStrategy.h"

#include <cmath>

#include <QRandomGenerator>

static constexpr double DEG_PER_METER = 1.0 / 111320.0;

TelemetrySnapshot RandomWalkStrategy::step(const TelemetrySnapshot &current, double dt)
{

    TelemetrySnapshot next = current;

    // heading change (-15 to +15 deg)

    double deltaHeading = randRange(-15.0, 15.0) * dt;

    next.heading = fmod(next.heading + deltaHeading + 360.0, 360.0);

    // speed change

    double speedChange = randRange(-1.0, 1.5) * dt;

    next.speed = std::max(0.0, next.speed + speedChange);

    // convert speed to movement

    double dist = next.speed * dt;

    double rad = next.heading * M_PI / 180.0;

    double dy = cos(rad) * dist;

    double dx = sin(rad) * dist;

    next.latitude += dy * DEG_PER_METER;

    next.longitude += dx * DEG_PER_METER / cos(next.latitude * M_PI / 180.0);

    // battery drain proportional to movement

    next.battery = std::max(0, next.battery - (int)(dt * (0.05 + next.speed * 0.01)));

    // altitude change

    next.altitude += randRange(-0.2, 0.5) * dt;

    return next;
}