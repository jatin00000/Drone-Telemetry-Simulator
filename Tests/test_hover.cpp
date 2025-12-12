#include <QtTest>

#include "../HoverStrategy.h"
#include "../TelemetryTypes.h"

class TestHover : public QObject {
    Q_OBJECT

private slots:
    void test_hover_small_movement() {
        HoverStrategy h;
        TelemetrySnapshot t;

        double dt = 1.0;
        TelemetrySnapshot t2 = h.step(t, dt);

        const double EPS = 1e-4;  // Hover allows very tiny random drift

        QVERIFY2(
            fabs(t2.latitude - t.latitude) < EPS,
            "HoverStrategy should not significantly change latitude"
        );

        QVERIFY2(
            fabs(t2.longitude - t.longitude) < EPS,
            "HoverStrategy should not significantly change longitude"
        );
    }
};

QTEST_MAIN(TestHover)
#include "test_hover.moc"
