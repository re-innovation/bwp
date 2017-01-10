#include <Arduino.h>
#include <Mode.h>

#include "ModeButton.h"
#include "Projector.h"
#include "ProjectorHeartbeat.h"
#include "Mp3Player.h"
#include "DiagnosticMode.h"
#include "NormalMode.h"

Mode* CurrentMode = &NormalMode;

void switchMode(Mode* newMode)
{
    CurrentMode->stop();
    CurrentMode = newMode;
    CurrentMode->start();
}

void setup()
{
    Serial.begin(115200);
    ModeButton.begin();
    ProjectorHeartbeat.begin();
    Mp3Player.begin();
    CurrentMode->start();
    Serial.println(F("E:setup()"));
}

void loop()
{
    ModeButton.update();
    ProjectorHeartbeat.update();
    CurrentMode->update();
}

