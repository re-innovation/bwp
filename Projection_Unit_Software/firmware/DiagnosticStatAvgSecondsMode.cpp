#include <Arduino.h>
#include "DiagnosticStatAvgSecondsMode.h"
#include "SW1.h"
#include "MutilaDebug.h"
#include "Mp3Player.h"
#include "Settings.h"
#include "Config.h"

// Our global instance of the mode...
DiagnosticStatAvgSecondsMode_ DiagnosticStatAvgSecondsMode;

DiagnosticStatAvgSecondsMode_::DiagnosticStatAvgSecondsMode_()
{
}

void DiagnosticStatAvgSecondsMode_::modeStart()
{
    DBLN(F("DiagnosticStatAvgSecondsMode::modeStart"));
    Mp3Player.appendElement(MP3_TRACK_AVERAGE_RUNTIME);
    uint8_t secs = Settings.getUseSeconds() / Settings.getUseCount();
    Mp3Player.readNumber(secs);
    Mp3Player.appendElement(secs == 1 ? DFPReader::Mp3TrackSecond : DFPReader::Mp3TrackSeconds);
}

void DiagnosticStatAvgSecondsMode_::modeStop()
{
    DBLN(F("DiagnosticStatAvgSecondsMode::modeStop()"));
    Mp3Player.stop();
}

bool DiagnosticStatAvgSecondsMode_::isFinished()
{
    return SW1.tapped() != 0;
}

