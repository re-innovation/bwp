#include <Arduino.h>
#include "DiagnosticStatSecondsMode.h"
#include "SW1.h"
#include "MutilaDebug.h"
#include "Mp3Player.h"
#include "Settings.h"
#include "Config.h"

// Our global instance of the mode...
DiagnosticStatSecondsMode_ DiagnosticStatSecondsMode;

DiagnosticStatSecondsMode_::DiagnosticStatSecondsMode_()
{
}

void DiagnosticStatSecondsMode_::modeStart()
{
    DBLN(F("DiagnosticStatSecondsMode::modeStart"));
    Mp3Player.appendElement(MP3_TRACK_TOTAL_RUNTIME);
    unsigned long mins = Settings.getUseSeconds()/60;
    Mp3Player.readNumber(mins);
    Mp3Player.appendElement(mins == 1 ? MP3_TRACK_MINUTE : MP3_TRACK_MINUTES);
}

void DiagnosticStatSecondsMode_::modeStop()
{
    DBLN(F("DiagnosticStatSecondsMode::modeStop()"));
    Mp3Player.stop();
}

bool DiagnosticStatSecondsMode_::isFinished()
{
    return SW1.tapped() != 0;
}

