#include <Arduino.h>
#include <Millis.h>
#include "DiagnosticVolumeAdjustMode.h"
#include "SW1.h"
#include "SW2.h"
#include "SW3.h"
#include "MutilaDebug.h"
#include "Mp3Player.h"
#include "Config.h"
#include "Settings.h"

// Our global instance of the mode...
DiagnosticVolumeAdjustMode_ DiagnosticVolumeAdjustMode;

DiagnosticVolumeAdjustMode_::DiagnosticVolumeAdjustMode_()
{
}

void DiagnosticVolumeAdjustMode_::modeStart()
{
    Serial.print(F("DiagnosticVolumeAdjustMode volume="));
    Serial.println(Mp3Player.volume());
    STOP_MP3;
    Mp3Player.play(MP3_TRACK_VOLUME_ADJUST);
    _startTime = Millis();
}

void DiagnosticVolumeAdjustMode_::modeStop()
{
    VolumeSetting.set(Mp3Player.volume(), true);
    Serial.print(F("SAVING volume="));
    Serial.println(VolumeSetting.get());
}

void DiagnosticVolumeAdjustMode_::modeUpdate()
{
    if (MillisSince(_startTime) > 500 && !Mp3Player.busy()) {
        Mp3Player.play(AudioTrackSetting.get());
    }
    uint8_t volume = Mp3Player.volume();
    if (SW3.tapped()) {
        volume = (volume % VolumeSetting.getMaximum()) + 1;
    }
    if (SW2.tapped()) {
        volume = (volume-1);
        // handle uint8_t underflow wrap-around
        if (volume > VolumeSetting.getMaximum()) {
            volume = VolumeSetting.getMaximum();
        }
    }
    if (volume != Mp3Player.volume()) {
        Serial.print(F("volume="));
        Serial.println(volume);
        Mp3Player.setVolume(volume);
    }
}

bool DiagnosticVolumeAdjustMode_::isFinished()
{
    return SW1.tapped() != 0;
}

