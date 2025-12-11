#include "TelemetryTypes.h"

#include <QMetaType>

// nothing else needed; ensures the object file is generated

static bool registerTelemetryTypes()

{

    qRegisterMetaType<TelemetrySnapshot>("TelemetrySnapshot");

    qRegisterMetaType<TelemetrySnapshot::GpsFix>("TelemetrySnapshot::GpsFix");

    return true;
}

static bool _reg = registerTelemetryTypes();
