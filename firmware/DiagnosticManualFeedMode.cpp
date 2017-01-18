#include <Arduino.h>
#include "DiagnosticManualFeedMode.h"
#include "SW1.h"
#include "SW2.h"
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
    if (SW2.held()) {
        Projector.update();
    }
}

bool DiagnosticManualFeedMode_::isFinished()
{
    return SW1.tapped() != 0;
}

