#include <Arduino.h>
#include <MutilaDebug.h>
#include "Mp3Player.h"
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
    _audioMarkSensor(AUDIO_SYNC_PIN, AUDIO_SYNC_ALPHA, AUDIO_SYNC_THRESH),
    _frameOffsetCounter(-1)
{
}

void Projector_::begin()
{
    _stepper.setMaxSpeed(STEPPER_MAX_SPEED);
    _stepper.setSpeed(STEPPER_STEPS_PER_SEC);
    pinMode(SHUTTER_LED_B_PIN, OUTPUT);
    closeShutter();
    _audioMarkSensor.begin();
    _frameOffsetCounter = -1;
    _shutter = true;
    _muted = false;
}

void Projector_::update()
{

    if (_shutterOpen) {
        if (millis() - _shutterStart >= SHUTTER_OPEN_MS) {
            closeShutter();
        }
    } else if (_stepper.runSpeed()) {
        frameStep();
        audioStep();
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
        if (_frameOffsetCounter++ == Settings.frameOffset() && _shutter || _frameOffsetCounter == 128) {
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
    // a negative integer indicates a partial, but failed read
    int track = _audioMarkSensor.get();

    // If we got a partial read, work out which track to play based
    // on the last played track and audio settings...
    if (track == AUDIO_SYNC_INVALID) {
        Serial.print(millis() / 1000);
        Serial.print(F(" Projector::audioStep bad read, last="));
        Serial.print(Settings.lastAudio());
        Serial.print(F(" count="));
        Serial.print(Settings.audioCount());
        Serial.print(F(" next="));

        if (Settings.lastAudio() > 0 && Settings.audioCount() > 0) {
            track = Settings.lastAudio() + 1;
            if (track > Settings.audioCount()) { 
                track = 1;
            }
            Serial.println(track);
        } else { 
            Serial.println('?');
        }
    }

    if (track >= 0) {
        Serial.print(millis()/1000);
        Serial.print(F(" Projector::audioStep playing track "));
        Serial.print(track);
        if (_muted) {
            Serial.println(F(" [muted]"));
        } else {
            Serial.println();
            Mp3Player.setVolume(Settings.volume());
            Mp3Player.play(track);
        }
        Settings.setLastAudio(track);
    }
}

void Projector_::openShutter()
{
    DBLN(F("openShutter"));
    _shutterStart = millis();
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


