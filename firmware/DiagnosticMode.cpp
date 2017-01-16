#include <Arduino.h>
#include "DiagnosticMode.h"
#include "ProjectorHeartbeat.h"
#include "ModeButton.h"
#include "DiagnosticFrameSyncMode.h"

// Our global instance of the mode...
DiagnosticMode_ DiagnosticMode;

DiagnosticMode_::DiagnosticMode_()
{
}

void DiagnosticMode_::modeStart()
{
    Serial.println(F("DiagnosticMode::modeStart()"));
    ProjectorHeartbeat.setMode(Heartbeat::Quick);
    subMode = &DiagnosticFrameSyncMode;
    subMode->start();
}

void DiagnosticMode_::modeStop()
{
    Serial.println(F("DiagnosticMode::modeStop()"));
    subMode->stop();
}

void DiagnosticMode_::modeUpdate()
{
    subMode->update();
}

bool DiagnosticMode_::isFinished()
{
    return ModeButton.tapped() != 0;
}

void DiagnosticMode_::switchSubMode(Mode* mode)
{
    subMode->stop();
    subMode = mode;
    subMode->start();
}

