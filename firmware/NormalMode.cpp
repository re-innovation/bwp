#include <Arduino.h>
#include <MutilaDebug.h>
#include <EMAVDivSampler.h>
#include "NormalMode.h"
#include "ProjectorHeartbeat.h"
#include "ModeButton.h"
#include "Projector.h"
#include "Mp3Player.h"

EMAVDivSampler VoltageSampler(VIN_MONITOR_PIN, VIN_R1, VIN_R2, VIN_REF, VIN_PERIOD_MS, VIN_EMA_ALPHA);

// Our global mode object
NormalMode_ NormalMode(VoltageSampler, VIN_THRESH_LOW, VIN_THRESH_HIGH);

NormalMode_::NormalMode_(EMAVDivSampler& vSampler, const float vThreshLow, const float vThreshHigh) : 
    BrownoutMode(vSampler, vThreshLow, vThreshHigh)
{
}

void NormalMode_::modeStart()
{
    DBLN(F("NormalMode::modeStart"));
    ProjectorHeartbeat.setMode(Heartbeat::Normal);
}

void NormalMode_::modeStop()
{
    DBLN(F("NormalMode::modeStop"));
    Mp3Player.stop();
}

void NormalMode_::enterBrownout()
{
    // Typical use: save state to EEPROM etc...
    Serial.println(F("NormalMode::enterBrownout()"));
    Projector.closeShutter();
    Mp3Player.stop();
}

void NormalMode_::exitBrownout()
{
    // Typical use: restore state from EEPROM
    Serial.println(F("NormalMode::exitBrownout()"));
}

void NormalMode_::modeUpdate()
{
    if (!brownedOut()) {
        Projector.update();
    }
}

bool NormalMode_::isFinished()
{
    return ModeButton.tapped() != 0;
}


