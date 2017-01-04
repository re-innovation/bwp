#pragma once

// Stepper setup & constants
#define STEPPER_PIN_1               9
#define STEPPER_PIN_2               10
#define STEPPER_PIN_3               11
#define STEPPER_PIN_4               12
#define STEPPER_STEPS_PER_SEC       4 
#define STEPPER_MAX_SPEED           1000

#define SHUTTER_OPEN_MS             1000
#define SHUTTER_LED_PIN             4
#define SHUTTER_SYNC_PIN            A3
#define SHUTTER_SYNC_DIFF_THRESHOLD 200
#define SHUTTER_SYNC_MIN_STEPS      7

#define AUDIO_SYNC_PIN              A2
#define AUDIO_SYNC_THRESH           500
#define AUDIO_SYNC_ALPHA            0.50
#define AUDIO_SYNC_MAX_LEN          30
#define AUDIO_SYNC_ZERO_MIN_LEN     5
#define AUDIO_SYNC_ONE_MIN_LEN      15
#define AUDIO_SYNC_ONE_MAX_LEN      25
#define AUDIO_SYNC_BITS             12
#define AUDIO_SYNC_INCOMPLETE       -1
#define AUDIO_SYNC_INVALID          -2

#define MP3_RX_PIN                  6
#define MP3_TX_PIN                  5
#define MP3_VOLUME                  15

#define TEST_BUTTON_PIN             3


