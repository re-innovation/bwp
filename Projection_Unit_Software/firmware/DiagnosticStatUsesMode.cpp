#include <Arduino.h>
#include "Config.h"
#include "DiagnosticStatUsesMode.h"
#include "SW1.h"
#include "MutilaDebug.h"
#include "Mp3Player.h"
#include "Settings.h"

// Our global instance of the mode...
DiagnosticStatUsesMode_ DiagnosticStatUsesMode;

DiagnosticStatUsesMode_::DiagnosticStatUsesMode_()
{
}

void DiagnosticStatUsesMode_::modeStart()
{
    Serial.println(F("DiagnosticStatUsesMode"));
    STOP_MP3;
    Mp3Player.appendElement(MP3_TRACK_NUMBER_OF_USES);
    Serial.print(F("Total Uses: "));
    Serial.println(UseCountStat.get());
    Mp3Player.readNumber(UseCountStat.get());
}

void DiagnosticStatUsesMode_::modeStop()
{
    Mp3Player.stop();
}

bool DiagnosticStatUsesMode_::isFinished()
{
    return SW1.tapped() != 0;
}

