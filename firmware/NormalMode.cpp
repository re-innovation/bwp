#include <Arduino.h>
#include <MutilaDebug.h>
#include <EMAVDivSampler.h>
#include "NormalMode.h"
#include "ProjectorHeartbeat.h"
#include "ModeButton.h"
#include "Projector.h"

EMAVDivSampler VoltageSampler(VIN_MONITOR_PIN, VIN_R1, VIN_R2, VIN_REF, VIN_PERIOD_MS, VIN_EMA_ALPHA);

// Our global mode object
NormalMode_ NormalMode(VoltageSampler, VIN_THRESH_LOW, VIN_THRESH_HIGH);

NormalMode_::NormalMode_(EMAVDivSampler& vSampler, const float vThreshLow, const float vThreshHigh) : 
    BrownoutMode(vSampler, vThreshLow, vThreshHigh)
{
    setUpdatePeriod(100);
}

void NormalMode_::modeStart()
{
    DBLN(F("NormalMode::modeStart"));
    ProjectorHeartbeat.setMode(Heartbeat::Normal);
}

void NormalMode_::modeStop()
{
    DBLN(F("NormalMode::modeStop"));
}

void NormalMode_::enterBrownout()
{
    // Typical use: save state to EEPROM etc...
    Serial.println(F("NormalMode::enterBrownout()"));
}

void NormalMode_::exitBrownout()
{
    // Typical use: restore state from EEPROM
    Serial.println(F("NormalMode::exitBrownout()"));
}

void NormalMode_::modeUpdate()
{
    DB(F("NormalMode::modeUpdate() volts="));
    DBLN(_vSampler.averageVolts());
}

bool NormalMode_::isFinished()
{
    return ModeButton.tapped() != 0;
}


