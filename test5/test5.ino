#include <Arduino.h>

// Import global objects which go up to make our projector
#include "Projector.h"

void setup()
{
    Serial.begin(115200);
    Projector.begin();
    Serial.println(F("E:setup()"));
}

void loop()
{
    Projector.update();
}

