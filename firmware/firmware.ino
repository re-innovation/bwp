#include <Arduino.h>
#include <Mode.h>

#include "Projector.h"
#include "ProjectorHeartbeat.h"
#include "Mp3Player.h"
#include "DiagnosticMode.h"

Mode* CurrentMode = &DiagnosticMode;

void switchMode(Mode* newMode)
{
    CurrentMode->stop();
    CurrentMode = newMode;
    CurrentMode->start();
}

void setup()
{
    Serial.begin(115200);
    ProjectorHeartbeat.begin();
    Mp3Player.begin();
    CurrentMode->start();
    Serial.println(F("E:setup()"));
}

void loop()
{
    ProjectorHeartbeat.update();
    CurrentMode->update();
}

