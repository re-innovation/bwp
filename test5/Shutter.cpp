#include <Arduino.h>
#include "Shutter.h"
#include "Config.h"

Shutter_ Shutter;

Shutter_::Shutter_()
{
}

void Shutter_::begin() {
    pinMode(SHUTTER_LED_PIN, OUTPUT);
    close();
}

void Shutter_::open() {
    digitalWrite(SHUTTER_LED_PIN, HIGH);
}

void Shutter_::close() {
    digitalWrite(SHUTTER_LED_PIN, LOW);
}

