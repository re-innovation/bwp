#include <Arduino.h>
#include "DiagnosticNumberOfSamplesMode.h"
#include "SW1.h"
#include "SW2.h"
#include "SW3.h"
#include "MutilaDebug.h"
#include "Mp3Player.h"
#include "Config.h"
#include "Settings.h"

// Our global instance of the mode...
DiagnosticNumberOfSamplesMode_ DiagnosticNumberOfSamplesMode;

DiagnosticNumberOfSamplesMode_::DiagnosticNumberOfSamplesMode_()
{
}

void DiagnosticNumberOfSamplesMode_::modeStart()
{
    Mp3Player.play(MP3_TRACK_AUDIO_MARK_COUNT);
    DB(F("DiagnosticNumberOfSamplesMode::modeStart count="));
    DBLN(Settings.audioCount());
}

void DiagnosticNumberOfSamplesMode_::modeStop()
{
    DBLN(F("DiagnosticNumberOfSamplesMode::modeStop()"));
    Settings.save();
}

void DiagnosticNumberOfSamplesMode_::modeUpdate()
{
    uint8_t count = Settings.audioCount();
    if (SW3.tapped()) {
        count = (count+1) % 10;
    }
    if (SW2.tapped()) {
        count = 0;
    }
    if (count != Settings.audioCount()) {
        DB(F("setting audio count to "));
        DBLN(count);
        Settings.setAudioCount(count);
        Mp3Player.readNumber(count);
    }
}

bool DiagnosticNumberOfSamplesMode_::isFinished()
{
    return SW1.tapped() != 0;
}

