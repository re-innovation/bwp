#pragma once

#include <Arduino.h>

//#define ENABLE_HEARTBEAT            1

// Stepper setup & constants
#define STEPPER_PIN_1               8
#define STEPPER_PIN_2               7
#define STEPPER_PIN_3               6
#define STEPPER_PIN_4               5
#define STEPPER_STEPS_PER_SEC       550
#define STEPPER_MAX_SPEED           1000

#define SHUTTER_OPEN_MS             125
#define SHUTTER_LED_R_PIN           9
#define SHUTTER_LED_G_PIN           10
#define SHUTTER_LED_B_PIN           11
#define SHUTTER_SYNC_PIN            A3
#define SHUTTER_SYNC_DIFF_THRESHOLD 250
#define SHUTTER_SYNC_MIN_STEPS      17
#define SHUTTER_SYNC_MAX_OFFSET     25
#define SHUTTER_SYNC_LOW_TRIGGER    50

#define MANUAL_FEED_STEPS_PER_SEC   200

#define HEARTBEAT_LED_PIN           4

#define VIN_MONITOR_PIN             A1
#define VIN_R1                      10
#define VIN_R2                      680
#define VIN_REF                     3.3
#define VIN_PERIOD_MS               10
#define VIN_EMA_ALPHA               0.5
#define VIN_THRESH_LOW              8.0
#define VIN_THRESH_HIGH             10.0

#define VIN_INTERNAL_PIN            A2

#define CRANK_SENSOR_PIN            2
#define WAKEUP_MS                   2000
#define TIRED_MS                    2000

#define MP3_TX_PIN                  12
#define MP3_RX_PIN                  13
#define MP3_BUSY_PIN                A0
#define MP3_POWER_PIN               3
#define MP3_VOLUME                  13
#define MP3_TRACK_NUMBER_OF_USES    190
#define MP3_TRACK_AVERAGE_RUNTIME   191
#define MP3_TRACK_TOTAL_RUNTIME     192
#define MP3_TRACK_MANUAL_FEED       193
#define MP3_TRACK_FRAME_OFFSET      194
#define MP3_TRACK_VOLUME_ADJUST     195
#define MP3_TRACK_AUDIO_MARK_COUNT  196
#define MP3_TRACK_TRACK_SELECTION   197
#define MP3_TRACK_CRANK_SPEED       198
#define MP3_TRACK_VOLUME_TRACK      1
#define MP3_AUDIO_MARKS_MAX         10

#define SW1_PIN                     A5
#define SW2_PIN                     A6
#define SW3_PIN                     A7

#define NORMAL_MODE_AUDIO_CHECK_MS  150
#define DIAGNOSTIC_MODE_DELAY       2000

