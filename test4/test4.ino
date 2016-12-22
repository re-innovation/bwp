#include <Arduino.h>
#include <AccelStepper.h>
#include <stdint.h>
#include "Config.h"
#include "AudioSyncSampler.h"

// Shutter synchronisation and audio pulse reading

AccelStepper stepper(AccelStepper::HALF4WIRE, STEPPER_PIN_1, STEPPER_PIN_3, STEPPER_PIN_2, STEPPER_PIN_4);
uint8_t frameCounter = 0;
int lastSyncValue = 512;
bool syncFound = false;
AudioSyncSampler audioSync(AUDIO_SYNC_PIN, AUDIO_SYNC_ALPHA, AUDIO_SYNC_THRESH);

void setup()
{
    Serial.begin(115200);
    stepper.setMaxSpeed(1000);
    stepper.setSpeed(STEPS_PER_SECOND); 
    audioSync.begin();
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, 0);
    delay(300);
    Serial.println(F("millis,state,duration"));
}

void showFrame()
{
    digitalWrite(LED_PIN, 1);
    delay(FRAME_ON_MS);
    digitalWrite(LED_PIN, 0);
}

void loop()
{
    if (stepper.runSpeed()) {
        if (audioSync.check()) {
            Serial.print(millis());
            Serial.print(',');
            Serial.print(audioSync.lastPulseState());
            Serial.print(',');
            Serial.println(audioSync.lastPulseLength());
        }
        frameCounter++;
        int syncValue = analogRead(FRAME_SYNC_PIN);
        int diff = syncValue - lastSyncValue;
        //Serial.print("fc=");
        //Serial.print(frameCounter);
        //Serial.print(" d=");
        //Serial.println(diff);
        if ((!syncFound || frameCounter > FRAME_SYNC_MIN_FRAME_STEPS) && diff >= FRAME_SYNC_DIFF_THRESHOLD) {
            showFrame();
            frameCounter = 0;
            syncFound = true;
        }
        lastSyncValue = syncValue;
    }
}

