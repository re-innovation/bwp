#include <Arduino.h>
#include <Mode.h>

#include "ModeButton.h"
#include "SetButton.h"
#include "ProjectorHeartbeat.h"
#include "Mp3Player.h"
#include "Projector.h"

#include "NormalMode.h"
#include "DiagnosticMode.h"

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
    SetButton.begin();
    ProjectorHeartbeat.begin();
    Mp3Player.begin();
    Projector.begin();

    CurrentMode->start();
    Serial.println(F("E:setup()"));
}

void loop()
{
    ModeButton.update();
    SetButton.update();
    ProjectorHeartbeat.update();
    CurrentMode->update();
    Mp3Player.update();
    if (CurrentMode->isFinished()) {
        if (CurrentMode == &NormalMode) {
            switchMode(&DiagnosticMode);
        } else if (CurrentMode == &DiagnosticMode) {
            switchMode(&NormalMode);
        } else {
            DBLN(F("ERROR - we're in an unknown mode :s"));
        }
    }
}

