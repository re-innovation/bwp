#pragma once

#include <Arduino.h>

// Stepper setup & constants
#define STEPPER_PIN_1               8
#define STEPPER_PIN_2               7
#define STEPPER_PIN_3               6
#define STEPPER_PIN_4               5
#define STEPPER_STEPS_PER_SEC       800
#define STEPPER_MAX_SPEED           1000

#define SHUTTER_OPEN_MS             100
#define SHUTTER_LED_R_PIN           9
#define SHUTTER_LED_G_PIN           10
#define SHUTTER_LED_B_PIN           11
#define SHUTTER_SYNC_PIN            A3
#define SHUTTER_SYNC_DIFF_THRESHOLD 300
#define SHUTTER_SYNC_MIN_STEPS      7
#define SHUTTER_SYNC_MAX_OFFSET     25

#define AUDIO_SYNC_PIN              A4
#define AUDIO_SYNC_THRESH           390
#define AUDIO_SYNC_ALPHA            1.0
#define AUDIO_SYNC_MAX_LEN          30
#define AUDIO_SYNC_ZERO_MIN_LEN     3
#define AUDIO_SYNC_ONE_MIN_LEN      9
#define AUDIO_SYNC_ONE_MAX_LEN      20
#define AUDIO_SYNC_BITS             12
#define AUDIO_SYNC_INCOMPLETE       -1
#define AUDIO_SYNC_INVALID          -2

#define HEARTBEAT_LED_PIN           4

#define VIN_MONITOR_PIN             A1
#define VIN_R1                      10
#define VIN_R2                      680
#define VIN_REF                     5
#define VIN_PERIOD_MS               10
#define VIN_EMA_ALPHA               0.5
#define VIN_THRESH_LOW              7.0
#define VIN_THRESH_HIGH             10.0

#define VIN_INTERNAL_PIN            A2

#define MP3_TX_PIN                  12
#define MP3_RX_PIN                  13
#define MP3_BUSY_PIN                A0
#define MP3_POWER_PIN               3
#define MP3_VOLUME                  10
#define MP3_TRACK_NUMBER_OF_USES    190
#define MP3_TRACK_AVERAGE_RUNTIME   191
#define MP3_TRACK_TOTAL_RUNTIME     192
#define MP3_TRACK_MANUAL_FEED       193
#define MP3_TRACK_FRAME_OFFSET      194
#define MP3_TRACK_VOLUME_ADJUST     195
#define MP3_TRACK_VOLUME_TRACK      1

#define SW1_PIN                     A5
#define SW2_PIN                     A6
#define SW3_PIN                     A7

