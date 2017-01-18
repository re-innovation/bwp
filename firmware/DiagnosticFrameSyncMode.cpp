#include <Arduino.h>
#include "DiagnosticFrameSyncMode.h"
#include "ModeButton.h"
#include "SetButton.h"
#include "Projector.h"
#include "MutilaDebug.h"
#include "Mp3Player.h"

// Our global instance of the mode...
DiagnosticFrameSyncMode_ DiagnosticFrameSyncMode;

DiagnosticFrameSyncMode_::DiagnosticFrameSyncMode_()
{
}

void DiagnosticFrameSyncMode_::modeStart()
{
    Projector.setMute(true);
    Projector.setShutter(true);
    Mp3Player.play(MP3_TRACK_FRAME_OFFSET);
    DB(F("DiagnosticFrameSyncMode::modeStart, offset="));
    DBLN(Projector.frameOffset());
}

void DiagnosticFrameSyncMode_::modeStop()
{
    Serial.println(F("DiagnosticFrameSyncMode::modeStop()"));
    // TODO: save to EEPROM
}

void DiagnosticFrameSyncMode_::modeUpdate()
{
    Projector.update();
    if (SetButton.tapped()) {
        int8_t offset = Projector.frameOffset();
        offset = (offset+1) % SHUTTER_SYNC_MAX_OFFSET;
        DB(F("setting frame offset to "));
        DBLN(offset);
        Projector.setFrameOffset(offset);
    }
}

bool DiagnosticFrameSyncMode_::isFinished()
{
    return ModeButton.tapped() != 0;
}

