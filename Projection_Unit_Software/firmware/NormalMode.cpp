#include <Arduino.h>
#include <MutilaDebug.h>
#include "Config.h"
#include "NormalMode.h"
#ifdef ENABLE_HEARTBEAT
#include "ProjectorHeartbeat.h"
#endif
#include "SW1.h"
#include "Projector.h"
#include "Mp3Player.h"
#include "Settings.h"
#include "CrankMonitor.h"

// Our global mode object
NormalMode_ NormalMode;

NormalMode_::NormalMode_() 
{
}

void NormalMode_::modeStart()
{
    Serial.println(F("NormalMode"));
    Projector.setMute(false);
    Projector.setShutter(true);
#ifdef ENABLE_HEARTBEAT
    ProjectorHeartbeat.setMode(Heartbeat::Normal);
#endif
    Settings.run();
    VolumeSetting.load();
    lastAudioCheck = 0;
}

void NormalMode_::modeStop()
{
}

void NormalMode_::modeUpdate()
{
    Projector.update();

    if (MillisSince(lastAudioCheck) > NORMAL_MODE_AUDIO_CHECK_MS) {
        lastAudioCheck = Millis();
        if (!Mp3Player.busy()) {
            Serial.print(F("playing track #"));
            Serial.println(AudioTrackSetting.get());
            Mp3Player.play(AudioTrackSetting.get());
        }
        int8_t volume_adjust = 0;
        if (Mp3Player.volume() < VolumeSetting.get()) {
            volume_adjust = 1;
        } else if (Mp3Player.volume() > VolumeSetting.get()) {
            volume_adjust = -1;
        }
        DB(F("vol fade="));
        DBLN(volume_adjust);
        if (volume_adjust != 0) {
            Mp3Player.setVolume(Mp3Player.volume() + volume_adjust);
        }
    }
}

bool NormalMode_::isFinished()
{
    return !crankSpeedAboveThreshold();
}


