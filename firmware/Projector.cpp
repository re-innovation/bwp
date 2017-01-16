#include <Arduino.h>
#include <MutilaDebug.h>
#include "Mp3Player.h"
#include "Projector.h"
#include "Config.h"

// Arduino library class style global object
Projector_ Projector;

Projector_::Projector_() :
    _stepper(AccelStepper::HALF4WIRE, STEPPER_PIN_1, STEPPER_PIN_3, STEPPER_PIN_2, STEPPER_PIN_4),
#ifdef TESTMODE
    _testButton(TEST_BUTTON_PIN),
#endif
    _stepsSinceFrame(0),
    _lastFrameSensorValue(512),
    _frameSyncFound(false),
    _shutterOpen(false),
    _shutterStart(0),
    _audioMarkSensor(AUDIO_SYNC_PIN, AUDIO_SYNC_ALPHA, AUDIO_SYNC_THRESH),
    _frameOffsetCounter(-1),
    _frameOffset(SHUTTER_SYNC_OFFSET)
{
}

void Projector_::begin()
{
    _stepper.setMaxSpeed(STEPPER_MAX_SPEED);
    _stepper.setSpeed(STEPPER_STEPS_PER_SEC);
    pinMode(SHUTTER_LED_PIN, OUTPUT);
    closeShutter();
    _audioMarkSensor.begin();
    _frameOffsetCounter = -1;
#ifdef TESTMODE
    _testButton.begin();
#endif
    _shutter = true;
    _muted = true;
}

void Projector_::update()
{
#ifdef TESTMODE
    _testButton.update();
#endif

    if (_shutterOpen) {
        if (millis() - _shutterStart >= SHUTTER_OPEN_MS) {
            closeShutter();
        }
#ifdef TESTMODE
    } else if (_testButton.tapped()) {
#else
    } else if (_stepper.runSpeed()) {
#endif
        frameStep();
        audioStep();
    }
}

void Projector_::frameStep()
{
    _stepsSinceFrame++;
    int syncValue = analogRead(SHUTTER_SYNC_PIN);
    int diff = syncValue - _lastFrameSensorValue;
    //DB(F("Projector_::frameStep f="));
    //DB(_stepsSinceFrame);
    //DB(F(" diff="));
    //DBLN(diff);
    if ((!_frameSyncFound || _stepsSinceFrame > SHUTTER_SYNC_MIN_STEPS) && diff >= SHUTTER_SYNC_DIFF_THRESHOLD) {
        // Start the frame offset counter
        _frameOffsetCounter = 0;
    }
    _lastFrameSensorValue = syncValue;

    // open the shutter _frameOffset steps after fram hole detected
    if (_frameOffsetCounter >= 0) {
        if (_frameOffsetCounter++ == _frameOffset && _shutter) {
            openShutter();
            _frameOffsetCounter = -1;
        }
    }
}

void Projector_::audioStep()
{
    // Read the sensor and update state
    _audioMarkSensor.update();

    // Gets the audio track to play if there is one.
    // The value will be 0 if there is no track to play, else
    // a positive integer if a mark has been ready successfully
    int track = _audioMarkSensor.get();
    if (track >= 0 && ! _muted) {
        DB(F("Projector_::audioStep playing track "));
        DBLN(track);
        Mp3Player.play(track);
    }
}

void Projector_::openShutter()
{
    DBLN(F("openShutter"));
    _shutterStart = millis();
    _stepsSinceFrame = 0;
    _frameSyncFound = true;
    _shutterOpen = true;
    digitalWrite(SHUTTER_LED_PIN, HIGH);
}

void Projector_::closeShutter()
{
    DBLN(F("closeShutter"));
    digitalWrite(SHUTTER_LED_PIN, LOW);
    _shutterOpen = false;
}


