#include <Arduino.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <AccelStepper.h>
#include <MutilaDebug.h>
#include <Mode.h>
#include <avr/wdt.h>

#include "SW1.h"
#include "SW2.h"
#include "SW3.h"
#include "ProjectorHeartbeat.h"
#include "Mp3Player.h"
#include "Projector.h"
#include "Settings.h"

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

    // We use an external reference for the VIN measurements
    analogReference(EXTERNAL);

    // Settings must be first because Mp3Player takes the volume from it.
    Settings.begin();

    Mp3Player.begin();
    if (!Mp3Player.check()) {
        Serial.println(F("WARNING: Mp3Player.check() failed"));
    }


    SW1.begin();
    SW2.begin();
    SW3.begin();
    ProjectorHeartbeat.begin();
    ProjectorHeartbeat.setMode(Heartbeat::Slower);
    Projector.begin();

    CurrentMode->start();

    // Enable watchdog timer
    wdt_enable(WDTO_500MS);

    DBLN(F("E:setup()"));
}

void loop()
{
    // Feed the watchdog
    wdt_reset();

    // Give timeslice to various components
    SW1.update();
    SW2.update();
    SW3.update();
    ProjectorHeartbeat.update();
    CurrentMode->update();
    Mp3Player.update();

    // Mode selection
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

