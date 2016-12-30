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
        if (millis() - _shutterStart >= FRAME_ON_MS) {
            closeShutter();
        }
    } else if (_stepper.runSpeed()) {
        step();
    }
}

void Projector_::step()
{
    _stepsSinceFrame++;
    int syncValue = analogRead(FRAME_SYNC_PIN);
    int diff = syncValue - _lastFrameSensorValue;
    if ((!_frameSyncFound || _stepsSinceFrame > FRAME_SYNC_MIN_FRAME_STEPS) && diff >= FRAME_SYNC_DIFF_THRESHOLD) {
        openShutter();
        _stepsSinceFrame = 0;
        _frameSyncFound = true;
    }
    _lastFrameSensorValue = syncValue;
}

void Projector_::openShutter()
{
    _shutterStart = millis();
    _shutterOpen = true;
    digitalWrite(SHUTTER_LED_PIN, HIGH);
}

void Projector_::closeShutter()
{
    digitalWrite(SHUTTER_LED_PIN, LOW);
    _shutterOpen = false;
}


