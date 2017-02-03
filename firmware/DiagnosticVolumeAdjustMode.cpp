#include <Arduino.h>
#include "DiagnosticVolumeAdjustMode.h"
#include "SW1.h"
#include "SW2.h"
#include "SW3.h"
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
    DBLN(F("DiagnosticVolumeAdjustMode::modeStop()"));
    // TODO: save to EEPROM
}

void DiagnosticVolumeAdjustMode_::modeUpdate()
{
    uint8_t volume = Mp3Player.volume();
    if (SW3.tapped()) {
        volume = (volume+1) % 31;
    }
    if (SW2.tapped()) {
        volume = (volume-1);
        // we are using unsigned, so < 0 will cause 255
        if (volume > 30) {
            volume = 30;
        }
    }
    if (volume != Mp3Player.volume()) {
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

