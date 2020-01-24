#include <Arduino.h>
#include "Config.h"
#include "DiagnosticStatAvgSecondsMode.h"
#include "SW1.h"
#include "MutilaDebug.h"
#include "Mp3Player.h"
#include "Settings.h"

// Our global instance of the mode...
DiagnosticStatAvgSecondsMode_ DiagnosticStatAvgSecondsMode;

DiagnosticStatAvgSecondsMode_::DiagnosticStatAvgSecondsMode_()
{
}

void DiagnosticStatAvgSecondsMode_::modeStart()
{
    Serial.println(F("DiagnosticStatAvgSecondsMode"));
    STOP_MP3;
    Mp3Player.appendElement(MP3_TRACK_AVERAGE_RUNTIME);
    uint8_t secs = UseSecondsStat.get() / UseCountStat.get();
    Mp3Player.readNumber(secs);
    Mp3Player.appendElement(secs == 1 ? DFPReader::Mp3TrackSecond : DFPReader::Mp3TrackSeconds);
    Serial.print(F("Average Runtime: "));
    Serial.print(secs);
    Serial.println(F(" sec"));
}

void DiagnosticStatAvgSecondsMode_::modeStop()
{
    Mp3Player.stop();
}

bool DiagnosticStatAvgSecondsMode_::isFinished()
{
    return SW1.tapped() != 0;
}

