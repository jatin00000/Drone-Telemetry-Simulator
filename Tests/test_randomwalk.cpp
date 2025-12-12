#include <QtTest>
#include "../RandomWalkStrategy.h"
#include "../TelemetryTypes.h"

class TestRandomWalk : public QObject {
    Q_OBJECT

private slots:

    void test_step_changes_position() {
        RandomWalkStrategy strat;

        TelemetrySnapshot t;
        t.speed = 5.0;          // IMPORTANT: ensure movement is possible
        t.heading = 45.0;       // any non-zero heading is fine

        double dt = 1.0;
        auto t2 = strat.step(t, dt);

        double dLat = std::abs(t2.latitude  - t.latitude);
        double dLon = std::abs(t2.longitude - t.longitude);

        const double EPS = 1e-12;

        QVERIFY2(
            (dLat > EPS) || (dLon > EPS),
            "RandomWalkStrategy must change latitude or longitude when speed > 0"
        );
    }

    void test_speed_non_negative() {
        RandomWalkStrategy strat;
        TelemetrySnapshot t;
        t.speed = 1.0;

        double dt = 1.0;
        auto t2 = strat.step(t, dt);

        QVERIFY2(t2.speed >= 0.0, "Speed must remain non-negative");
    }

    void test_heading_within_bounds() {
        RandomWalkStrategy strat;
        TelemetrySnapshot t;
        t.heading = 90.0;

        double dt = 1.0;
        auto t2 = strat.step(t, dt);

        QVERIFY2(
            t2.heading >= 0.0 && t2.heading < 360.0,
            "Heading must stay within [0, 360)"
        );
    }
};

QTEST_MAIN(TestRandomWalk)
#include "test_randomwalk.moc"
