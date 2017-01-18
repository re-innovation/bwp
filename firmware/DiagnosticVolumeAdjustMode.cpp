#include <Arduino.h>
#include "DiagnosticVolumeAdjustMode.h"
#include "SW1.h"
#include "SW2.h"
#include "MutilaDebug.h"
#include "Mp3Player.h"
#include "Config.h"

// Our global instance of the mode...
DiagnosticVolumeAdjustMode_ DiagnosticVolumeAdjustMode;

DiagnosticVolumeAdjustMode_::DiagnosticVolumeAdjustMode_()
{
}

void DiagnosticVolumeAdjustMode_::modeStart()
{
    Mp3Player.play(MP3_TRACK_VOLUME_ADJUST);
    DB(F("DiagnosticVolumeAdjustMode::modeStart volume="));
    DBLN(Mp3Player.volume());
}

void DiagnosticVolumeAdjustMode_::modeStop()
{
    Serial.println(F("DiagnosticVolumeAdjustMode::modeStop()"));
    // TODO: save to EEPROM
}

void DiagnosticVolumeAdjustMode_::modeUpdate()
{
    if (SW2.tapped()) {
        uint8_t volume = Mp3Player.volume();
        // loop through volumes between 0 and 30
        volume = (volume+1) % 31;
        DB(F("setting volume to "));
        DBLN(volume);
        Mp3Player.setVolume(volume);
        Mp3Player.play(MP3_TRACK_VOLUME_TRACK);
    }
}

bool DiagnosticVolumeAdjustMode_::isFinished()
{
    return SW1.tapped() != 0;
}

