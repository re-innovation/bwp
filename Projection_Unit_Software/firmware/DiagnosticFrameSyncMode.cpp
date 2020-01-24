#include <Arduino.h>
#include "DiagnosticFrameSyncMode.h"
#include "Config.h"
#include "SW1.h"
#include "SW2.h"
#include "SW3.h"
#include "Projector.h"
#include "MutilaDebug.h"
#include "Mp3Player.h"
#include "Settings.h"

// Our global instance of the mode...
DiagnosticFrameSyncMode_ DiagnosticFrameSyncMode;

DiagnosticFrameSyncMode_::DiagnosticFrameSyncMode_()
{
}

void DiagnosticFrameSyncMode_::modeStart()
{
    Projector.setMute(true);
    Projector.setShutter(true);
    STOP_MP3;
    Mp3Player.play(MP3_TRACK_FRAME_OFFSET);
    Serial.print(F("DiagnosticFrameSyncMode offset="));
    Serial.println(FrameOffsetSetting.get());
}

void DiagnosticFrameSyncMode_::modeStop()
{
    Serial.print(F("SAVING offset="));
    Serial.println(FrameOffsetSetting.get());
    FrameOffsetSetting.save();
}

void DiagnosticFrameSyncMode_::modeUpdate()
{
    Projector.update();
    if (SW3.tapped()) {
        int8_t offset = FrameOffsetSetting.get();
        offset = (offset+1) % SHUTTER_SYNC_MAX_OFFSET;
        Mp3Player.stop();
        Mp3Player.readNumber(offset);
        FrameOffsetSetting = offset;
        Serial.print(F("offset="));
        Serial.println(offset);
    }
}

bool DiagnosticFrameSyncMode_::isFinished()
{
    return SW1.tapped() != 0;
}

