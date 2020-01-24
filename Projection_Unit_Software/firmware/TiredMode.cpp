#include <Arduino.h>
#include <MutilaDebug.h>
#include <Millis.h>
#include "Config.h"
#include "TiredMode.h"
#include "NormalMode.h"
#include "CrankMonitor.h"
#ifdef ENABLE_HEARTBEAT
#include "ProjectorHeartbeat.h"
#endif
#include "Projector.h"
#include "Mp3Player.h"
#include "ModeSwitch.h"

// Our global instance of the mode...
TiredMode_ TiredMode;

TiredMode_::TiredMode_()
{
    // Do not put debug here as Mode objects are typically constructed before
    // setup() is run, and so the Serial interface is not ready - if you use it
    // the Arduino may hang.
}

void TiredMode_::modeStart()
{
    _startTime = Millis();
#ifdef ENABLE_HEARTBEAT
    ProjectorHeartbeat.setMode(Heartbeat::Quick);
#endif
    setUpdatePeriod(TIRED_MS / Mp3Player.volume());
    Projector.closeShutter();

    Serial.println(F("TiredMode"));
}

void TiredMode_::modeStop()
{
}

void TiredMode_::modeUpdate()
{
    if (crankSpeedAboveThreshold()) {
        DBLN(F("TiredMode_::modeUpdate crank sped up, resuming"));
        switchMode(&NormalMode);
    } else {
        uint8_t volume = Mp3Player.volume();
        if (volume > 0) {
            Mp3Player.setVolume(volume-1);
        }
    }
}

bool TiredMode_::isFinished()
{
    return (Millis() - _startTime) >= TIRED_MS;
}

