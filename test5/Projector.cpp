#include <Arduino.h>
#include "Projector.h"
#include "Config.h"

// Arduino library class style global object
Projector_ Projector;

Projector_::Projector_() :
    _stepper(AccelStepper::HALF4WIRE, STEPPER_PIN_1, STEPPER_PIN_3, STEPPER_PIN_2, STEPPER_PIN_4),
    _stepsSinceFrame(0),
    _lastFrameSensorValue(512),
    _frameSyncFound(false),
    _shutterOpen(false),
    _shutterStart(0)
{
}

void Projector_::begin()
{
    _stepper.setMaxSpeed(STEPPER_MAX_SPEED);
    _stepper.setSpeed(STEPPER_STEPS_PER_SEC);
    pinMode(SHUTTER_LED_PIN, OUTPUT);
    closeShutter();
}

void Projector_::update()
{
    if (_shutterOpen) {
        if (millis() - _shutterStart >= SHUTTER_OPEN_MS) {
            closeShutter();
        }
    } else if (_stepper.runSpeed()) {
        step();
    }
}

void Projector_::step()
{
    _stepsSinceFrame++;
    int syncValue = analogRead(SHUTTER_SYNC_PIN);
    int diff = syncValue - _lastFrameSensorValue;
#ifdef DEBUG_VERBOSE
    Serial.print(F("Projector_::step f="));
    Serial.print(_stepsSinceFrame);
    Serial.print(F(" diff="));
    Serial.println(diff);
#endif
    if ((!_frameSyncFound || _stepsSinceFrame > SHUTTER_SYNC_MIN_STEPS) && diff >= SHUTTER_SYNC_DIFF_THRESHOLD) {
        openShutter();
    }
    _lastFrameSensorValue = syncValue;
}

void Projector_::openShutter()
{
#ifdef DEBUG_VERBOSE
    Serial.println(F("openShutter"));
#endif
    _shutterStart = millis();
    _stepsSinceFrame = 0;
    _frameSyncFound = true;
    _shutterOpen = true;
    digitalWrite(SHUTTER_LED_PIN, HIGH);
}

void Projector_::closeShutter()
{
#ifdef DEBUG_VERBOSE
    Serial.println(F("closeShutter"));
#endif
    digitalWrite(SHUTTER_LED_PIN, LOW);
    _shutterOpen = false;
}


