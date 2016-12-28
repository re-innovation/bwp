#include <Arduino.h>

// Import global objects which go up to make our projector
#include "Shutter.h"
#include "Mp3Player.h"
#include "Stepper.h"

void setup()
{
    Serial.begin(115200);
    Shutter.begin();
    Mp3Player.begin();
    Stepper.begin();
    Serial.println(F("E:setup()"));
}

void loop()
{
    if (Stepper.step()) {
        Serial.println(F("Step"));
    }
}

