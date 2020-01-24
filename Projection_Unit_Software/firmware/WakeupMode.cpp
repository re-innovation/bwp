#include <Arduino.h>
#include <MutilaDebug.h>
#include <Millis.h>
#include "Config.h"
#include "WakeupMode.h"
#include "SleepMode.h"
#include "DiagnosticMode.h"
#include "CrankMonitor.h"
#ifdef ENABLE_HEARTBEAT
#include "ProjectorHeartbeat.h"
#endif
#include "ModeSwitch.h"
#include "SW1.h"
#include "SW3.h"

// Our global instance of the mode...
WakeupMode_ WakeupMode;

WakeupMode_::WakeupMode_()
{
    // Do not put debug here as Mode objects are typically constructed before
    // setup() is run, and so the Serial interface is not ready - if you use it
    // the Arduino may hang.
    setUpdatePeriod(50);
}

void WakeupMode_::modeStart()
{
    _startTime = Millis();
#ifdef ENABLE_HEARTBEAT
    ProjectorHeartbeat.setMode(Heartbeat::Quick);
#endif
    DBLN("WakeupMode::modeStart()");
}

void WakeupMode_::modeStop()
{
    DBLN("WakeupMode::modeStop()");
}

void WakeupMode_::modeUpdate()
{
    if (!crankSpeedAboveThreshold()) {
        DBLN("WakeupMode::modeUpdate crank too slow");
        switchMode(&SleepMode);
    }

    if (SW1.on() || SW3.on()) {
        switchMode(&DiagnosticMode);
    }
}

bool WakeupMode_::isFinished()
{
    return (Millis() - _startTime) >= WAKEUP_MS;
}

