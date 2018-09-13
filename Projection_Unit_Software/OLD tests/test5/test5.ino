#include <Arduino.h>

// Import global objects which go up to make our projector
#include "Projector.h"
#include "Mp3Player.h"

void setup()
{
    Serial.begin(115200);
    Projector.begin();
    Mp3Player.begin();
    Serial.println(F("E:setup()"));
}

void loop()
{
    Projector.update();
}

