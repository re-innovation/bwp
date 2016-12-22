#pragma once

// Stepper setup & constants
#define STEPPER_PIN_1               9
#define STEPPER_PIN_2               10
#define STEPPER_PIN_3               11
#define STEPPER_PIN_4               12
#define STEPS_PER_SECOND            300 

#define FRAME_ON_MS                 100
#define FRAME_SYNC_PIN              A3
#define FRANE_SYNC_LOW_THRESHOLD    50
#define FRAME_SYNC_DIFF_THRESHOLD   200
#define FRAME_SYNC_MIN_FRAME_STEPS  7
#define FRAME_SYNC_MAX_FRAME_STEPS  13

#define AUDIO_SYNC_PIN              A2
#define AUDIO_SYNC_THRESH           500
#define AUDIO_SYNC_ALPHA            0.50
#define AUDIO_SYNC_MAXLEN           200
#define AUDIO_SYNC_MINLEN           10

#define MP3_RX_PIN                  6
#define MP3_TX_PIN                  5

#define LED_PIN                     4

