#include <Arduino.h>
#include "DiagnosticMode.h"
#include "ProjectorHeartbeat.h"


// Our global instance of the mode...
DiagnosticMode_ DiagnosticMode;

DiagnosticMode_::DiagnosticMode_()
{
}

void DiagnosticMode_::modeStart()
{
    Serial.println(F("DiagnosticMode::modeStart()"));
    ProjectorHeartbeat.setMode(Heartbeat::Quick);
}

void DiagnosticMode_::modeStop()
{
    Serial.println(F("DiagnosticMode::modeStop()"));
    ProjectorHeartbeat.setMode(Heartbeat::Normal);
}

void DiagnosticMode_::modeUpdate()
{
    Serial.println(F("DiagnosticMode::modeUpdate()"));
}

bool DiagnosticMode_::isFinished()
{
}

