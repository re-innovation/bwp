#include <Arduino.h>
#include "DiagnosticFrameSyncMode.h"
#include "SW1.h"
#include "SW2.h"
#include "SW3.h"
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
    DBLN(F("DiagnosticFrameSyncMode::modeStop()"));
    // TODO: save to EEPROM
}

void DiagnosticFrameSyncMode_::modeUpdate()
{
    Projector.update();
    if (SW3.tapped()) {
        int8_t offset = Projector.frameOffset();
        offset = (offset+1) % SHUTTER_SYNC_MAX_OFFSET;
        DB(F("setting frame offset to "));
        DBLN(offset);
        Projector.setFrameOffset(offset);
    }
}

bool DiagnosticFrameSyncMode_::isFinished()
{
    return SW1.tapped() != 0;
}

