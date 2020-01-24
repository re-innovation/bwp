#include <Arduino.h>
#include <Millis.h>
#include "DiagnosticTrackSelectMode.h"
#include "SW1.h"
#include "SW2.h"
#include "SW3.h"
#include "MutilaDebug.h"
#include "Mp3Player.h"
#include "Config.h"
#include "Settings.h"

// Our global instance of the mode...
DiagnosticTrackSelectMode_ DiagnosticTrackSelectMode;

DiagnosticTrackSelectMode_::DiagnosticTrackSelectMode_()
{
}

void DiagnosticTrackSelectMode_::modeStart()
{
    Serial.print(F("DiagnosticTrackSelectMode track="));
    Serial.println(AudioTrackSetting.get());
    STOP_MP3;
    Mp3Player.appendElement(MP3_TRACK_TRACK_SELECTION);
    Mp3Player.readNumber(AudioTrackSetting.get());
    Mp3Player.appendElement(AudioTrackSetting.get());
}

void DiagnosticTrackSelectMode_::modeStop()
{
    AudioTrackSetting.save();
    Serial.print(F("SAVING track="));
    Serial.println(AudioTrackSetting.get());
}

void DiagnosticTrackSelectMode_::modeUpdate()
{
    if (SW3.tapped()) {
        AudioTrackSetting = (AudioTrackSetting.get() % AudioTrackSetting.getMaximum()) + 1;
        Mp3Player.stop();
        Mp3Player.readNumber(AudioTrackSetting.get());
        Mp3Player.appendElement(AudioTrackSetting.get());
    }
}

bool DiagnosticTrackSelectMode_::isFinished()
{
    return SW1.tapped() != 0;
}

