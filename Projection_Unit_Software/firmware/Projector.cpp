#include <Arduino.h>
#include <MutilaDebug.h>
#include <Millis.h>
#include "Projector.h"
#include "Config.h"
#include "Settings.h"

// Arduino library class style global object
Projector_ Projector;

Projector_::Projector_() :
    _stepper(AccelStepper::HALF4WIRE, STEPPER_PIN_1, STEPPER_PIN_3, STEPPER_PIN_2, STEPPER_PIN_4),
    _stepsSinceFrame(0),
    _lastFrameSensorValue(512),
    _lastFrameSensorValue2(512),
    _frameSyncFound(false),
    _shutterOpen(false),
    _shutterStart(0),
    _frameOffsetCounter(-1),
    _muted(false)
{
}

void Projector_::begin()
{
    _stepper.setMaxSpeed(STEPPER_MAX_SPEED);
    _stepper.setSpeed(STEPPER_STEPS_PER_SEC);
    pinMode(SHUTTER_LED_B_PIN, OUTPUT);
    closeShutter();
    _frameOffsetCounter = -1;
    _shutter = true;
    DBLN(F("E:Projector.begin"));
}

void Projector_::update()
{

    if (_shutterOpen) {
        if (Millis() - _shutterStart >= SHUTTER_OPEN_MS) {
            closeShutter();
        }
    } else if (_stepper.runSpeed()) {
        frameStep();
    }
}

void Projector_::frameStep()
{
    _stepsSinceFrame++;
    int syncValue = analogRead(SHUTTER_SYNC_PIN);
    int diff = syncValue - _lastFrameSensorValue2;

    DB(F("Projector_::frameStep f="));
    DB(_stepsSinceFrame);
    DB(F(" sv="));
    DB(syncValue);
    DB(F(" diff="));
    DBLN(diff);

    if ((!_frameSyncFound || _stepsSinceFrame > SHUTTER_SYNC_MIN_STEPS) && diff >= SHUTTER_SYNC_DIFF_THRESHOLD && _lastFrameSensorValue2 < SHUTTER_SYNC_LOW_TRIGGER) {
        // Start the frame offset counter
        _frameOffsetCounter = 0;
    }
    _lastFrameSensorValue2 = _lastFrameSensorValue;
    _lastFrameSensorValue = syncValue;

    // open the shutter _frameOffset steps after fram hole detected
    if (_frameOffsetCounter >= 0) {
        if ((_frameOffsetCounter++ == FrameOffsetSetting.get() && _shutter) || _frameOffsetCounter == 128) {
            openShutter();
            _frameOffsetCounter = -1;
        }
    }
}

void Projector_::openShutter()
{
    DBLN(F("openShutter"));
    _shutterStart = Millis();
    _stepsSinceFrame = 0;
    _frameSyncFound = true;
    _shutterOpen = true;
    digitalWrite(SHUTTER_LED_R_PIN, HIGH);
    digitalWrite(SHUTTER_LED_G_PIN, HIGH);
    digitalWrite(SHUTTER_LED_B_PIN, HIGH);
}

void Projector_::closeShutter()
{
    DBLN(F("closeShutter"));
    digitalWrite(SHUTTER_LED_R_PIN, LOW);
    digitalWrite(SHUTTER_LED_G_PIN, LOW);
    digitalWrite(SHUTTER_LED_B_PIN, LOW);
    _shutterOpen = false;
}


