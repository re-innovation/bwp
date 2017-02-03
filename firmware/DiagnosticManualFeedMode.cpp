#include <Arduino.h>
#include "DiagnosticManualFeedMode.h"
#include "SW1.h"
#include "SW3.h"
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
    Projector.closeShutter();
    Mp3Player.play(MP3_TRACK_MANUAL_FEED);
    DBLN(F("DiagnosticManualFeedMode::modeStart"));
}

void DiagnosticManualFeedMode_::modeStop()
{
    DBLN(F("DiagnosticManualFeedMode::modeStop()"));
    // In case the button was pressed, called tappe() to 
    // collect it's pressed state (else the next read to
    // tapped in the next more will return true in a 
    // confusing way!
    SW3.tapped();
}

void DiagnosticManualFeedMode_::modeUpdate()
{
    if (SW3.on()) {
        Projector.update();
    }
}

bool DiagnosticManualFeedMode_::isFinished()
{
    return SW1.tapped() != 0;
}

