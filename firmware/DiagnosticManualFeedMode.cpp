#include <Arduino.h>
#include "DiagnosticManualFeedMode.h"
#include "ModeButton.h"
#include "SetButton.h"
#include "Projector.h"
#include "MutilaDebug.h"
#include "Mp3Player.h"

// Our global instance of the mode...
DiagnosticManualFeedMode_ DiagnosticManualFeedMode;

DiagnosticManualFeedMode_::DiagnosticManualFeedMode_()
{
}

void DiagnosticManualFeedMode_::modeStart()
{
    Projector.setMute(true);
    Projector.setShutter(false);
    Mp3Player.play(MP3_TRACK_MANUAL_FEED);
    DBLN(F("DiagnosticManualFeedMode::modeStart"));
}

void DiagnosticManualFeedMode_::modeStop()
{
    Serial.println(F("DiagnosticManualFeedMode::modeStop()"));
}

void DiagnosticManualFeedMode_::modeUpdate()
{
    if (SetButton.held()) {
        Projector.update();
    }
}

bool DiagnosticManualFeedMode_::isFinished()
{
    return ModeButton.tapped() != 0;
}

