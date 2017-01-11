#pragma once

// Stepper setup & constants
#define STEPPER_PIN_1               9
#define STEPPER_PIN_2               10
#define STEPPER_PIN_3               11
#define STEPPER_PIN_4               12
#define STEPPER_STEPS_PER_SEC       400
#define STEPPER_MAX_SPEED           1000

#define SHUTTER_OPEN_MS             50
#define SHUTTER_LED_PIN             4
#define SHUTTER_SYNC_PIN            A3
#define SHUTTER_SYNC_DIFF_THRESHOLD 300
#define SHUTTER_SYNC_MIN_STEPS      7
#define SHUTTER_SYNC_OFFSET         8 

#define AUDIO_SYNC_PIN              A2
#define AUDIO_SYNC_THRESH           390
#define AUDIO_SYNC_ALPHA            1.0
#define AUDIO_SYNC_MAX_LEN          30
#define AUDIO_SYNC_ZERO_MIN_LEN     3
#define AUDIO_SYNC_ONE_MIN_LEN      9
#define AUDIO_SYNC_ONE_MAX_LEN      20
#define AUDIO_SYNC_BITS             12
#define AUDIO_SYNC_INCOMPLETE       -1
#define AUDIO_SYNC_INVALID          -2

#define HEARTBEAT_LED_PIN           13

#define VIN_MONITOR_PIN             A4
#define VIN_R1                      10
#define VIN_R2                      100
#define VIN_REF                     5
#define VIN_PERIOD_MS               10
#define VIN_EMA_ALPHA               0.5
#define VIN_THRESH_LOW              5.0
#define VIN_THRESH_HIGH             10.0

#define MP3_RX_PIN                  6
#define MP3_TX_PIN                  5
#define MP3_BUSY_PIN                10
#define MP3_VOLUME                  10
#define MP3_TRACK_ZERO              200
#define MP3_TRACK_TEN               210
#define MP3_TRACK_TWENTY            220
#define MP3_TRACK_THIRTY            221
#define MP3_TRACK_FOURTY            222
#define MP3_TRACK_FIFTY             223
#define MP3_TRACK_SIXTY             224
#define MP3_TRACK_SEVENTY           225
#define MP3_TRACK_EIGHTY            226
#define MP3_TRACK_NINETY            227
#define MP3_TRACK_HUNDRED           228
#define MP3_TRACK_THOUSAND          229
#define MP3_TRACK_POINT             231
#define MP3_TRACK_MINUS             232
#define MP3_TRACK_HOUR              233
#define MP3_TRACK_HOURS             234
#define MP3_TRACK_MINUTE            235
#define MP3_TRACK_MINUTES           236
#define MP3_TRACK_SECOND            237
#define MP3_TRACK_SECONDS           238
#define MP3_TRACK_NUMBER_OF_USES    239
#define MP3_TRACK_AVERAGE_RUNTIME   240
#define MP3_TRACK_TOTAL_RUNTIME     241

#define TEST_BUTTON_PIN             3
#define MODE_BUTTON_PIN             7

