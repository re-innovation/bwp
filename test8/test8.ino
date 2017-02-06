#include <Arduino.h>
#include <MutilaDebug.h>
#include <ToggleButton.h>
#include "Mp3Player.h"
#include "Config.h"

void sayDigit(uint8_t d)
{
    DB("sayDigit: ");
    DBLN(d);
    if (d < 10)
        Mp3Player.play(MP3_TRACK_ZERO + d);
}

void readNumber(uint32_t i)
{
    uint8_t digits[10];
    int8_t ptr = 0;
    DB("readNumber: ");
    DBLN(i);
    while(i > 0) {
        digits[ptr++] = i%10;
        i /= 10;
    }
    if (ptr == 0) {
        digits[ptr++] = 0;
    }
    for (ptr--; ptr>=0; ptr--) {
        sayDigit(digits[ptr]);
        delay(100); // allow playback to get started
        while(Mp3Player.busy()) { ; } // wait for end of playback
    }
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Hai there");
    Mp3Player.begin();
}

void loop()
{
    readNumber(random(10000,65535));
    DBLN("Next number...");
    delay(5000);
}

