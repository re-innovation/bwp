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
    uint16_t hours = Settings.getUseSeconds() / 3600;
    uint8_t mins = (Settings.getUseSeconds() / 60) % 60;
    uint8_t secs = Settings.getUseSeconds() % 60;
    if (hours > 0) {
        Mp3Player.readNumber(hours);
        Mp3Player.appendElement(hours == 1 ? DFPReader::Mp3TrackHour : DFPReader::Mp3TrackHours);
    }
    if (mins > 0) {
        Mp3Player.readNumber(mins);
        Mp3Player.appendElement(mins == 1 ? DFPReader::Mp3TrackMinute : DFPReader::Mp3TrackMinutes);
    }
    if (secs > 0) {
        Mp3Player.readNumber(secs);
        Mp3Player.appendElement(secs == 1 ? DFPReader::Mp3TrackSecond : DFPReader::Mp3TrackSeconds);
    }
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

