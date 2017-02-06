#include <Arduino.h>
#include "DiagnosticStatUsesMode.h"
#include "SW1.h"
#include "MutilaDebug.h"
#include "Mp3Player.h"
#include "Settings.h"
#include "Config.h"

// Our global instance of the mode...
DiagnosticStatUsesMode_ DiagnosticStatUsesMode;

DiagnosticStatUsesMode_::DiagnosticStatUsesMode_()
{
}

void DiagnosticStatUsesMode_::modeStart()
{
    DBLN(F("DiagnosticStatUsesMode::modeStart"));
    Mp3Player.appendElement(MP3_TRACK_NUMBER_OF_USES);
    Mp3Player.readNumber(Settings.getUseCount());
}

void DiagnosticStatUsesMode_::modeStop()
{
    DBLN(F("DiagnosticStatUsesMode::modeStop()"));
}

bool DiagnosticStatUsesMode_::isFinished()
{
    return SW1.tapped() != 0;
}

