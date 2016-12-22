#include <Arduino.h>
#include <AccelStepper.h>
#include <stdint.h>
#include "Config.h"
#include "AudioSyncSampler.h"

// Proof of concept frame synchonisation test

AccelStepper stepper(AccelStepper::HALF4WIRE, STEPPER_PIN_1, STEPPER_PIN_3, STEPPER_PIN_2, STEPPER_PIN_4);
AudioSyncSampler audioSync(AUDIO_SYNC_PIN, AUDIO_SYNC_ALPHA, AUDIO_SYNC_THRESH);

void setup()
{
    Serial.begin(115200);
    stepper.setMaxSpeed(1000);
    stepper.setSpeed(STEPS_PER_SECOND); 
    audioSync.begin();
    delay(300);
    Serial.println(F("e:setup"));
}

void loop()
{
    if (stepper.runSpeed()) {
        audioSync.check();
    }
}

