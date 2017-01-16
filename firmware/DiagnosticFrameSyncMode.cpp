#include <Arduino.h>
#include "DiagnosticFrameSyncMode.h"
#include "ModeButton.h"
#include "SetButton.h"
#include "Projector.h"
#include "MutilaDebug.h"

// Our global instance of the mode...
DiagnosticFrameSyncMode_ DiagnosticFrameSyncMode;

DiagnosticFrameSyncMode_::DiagnosticFrameSyncMode_()
{
}

void DiagnosticFrameSyncMode_::modeStart()
{
    Projector.setMute(true);
    Projector.setShutter(true);
    DB(F("DiagnosticFrameSyncMode::modeStart, offset="));
    DBLN(Projector.frameOffset());
}

void DiagnosticFrameSyncMode_::modeStop()
{
    Serial.println(F("DiagnosticFrameSyncMode::modeStop()"));
}

void DiagnosticFrameSyncMode_::modeUpdate()
{
    Serial.println(F("DiagnosticFrameSyncMode::modeUpdate()"));
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

