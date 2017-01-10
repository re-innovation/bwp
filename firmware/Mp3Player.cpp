#include <SoftwareSerial.h>
#include <MutilaDebug.h>
#include <Arduino.h>
#include "Mp3Player.h"
#include "Config.h"

// A global object
Mp3Player_ Mp3Player;

Mp3Player_::Mp3Player_() :
    _serial(MP3_TX_PIN, MP3_RX_PIN),
    _mp3(_serial, MP3_BUSY_PIN)
{
}

void Mp3Player_::begin()
{
    _serial.begin(9600);
    _mp3.sendCmd(DFPlayerMini::SetVolume, MP3_VOLUME);
}

void Mp3Player_::play(uint16_t trackNumber)
{
#ifdef MP3DEBUG
    Serial.print(F("Mp3Player_::play track="));
    Serial.println(trackNumber);
#endif
    _mp3.sendCmd(DFPlayerMini::PlayTf, trackNumber);
}

bool Mp3Player_::busy()
{
    return _mp3.busy();
}

void Mp3Player_::sayDigit(uint8_t d)
{
    DB("sayDigit: ");
    DBLN(d);
    if (d < 10)
        Mp3Player.play(MP3_TRACK_ZERO + d);
}

void Mp3Player_::sayInteger(long i)
{
    uint8_t digits[10];
    int8_t ptr = 0;
    DB("readNumber: ");
    DBLN(i);
    if (i < 0) {
        Mp3Player.play(MP3_TRACK_MINUS);
        i = -i;
    }
    while(i > 0) {
        digits[ptr++] = i%10;
        i /= 10;
    }
    if (ptr == 0) {
        digits[ptr++] = 0;
    }
    for (ptr--; ptr>=0; ptr--) {
        sayDigit(digits[ptr]);
        waitUntilIdle();
    }
}

void Mp3Player_::sayDuration(long seconds)
{
    long hours=0;
    long minutes=0;

    if (seconds >= 3600) {
        hours = seconds/3600;
        seconds -= (hours*3600);
        sayInteger(hours);
        play(MP3_TRACK_HOURS);
        waitUntilIdle();
    }
    if (seconds >= 60) {
        minutes = seconds/60;
        seconds -= (minutes*60);
        sayInteger(minutes);
        play(MP3_TRACK_MINUTES);
        waitUntilIdle();
    }
    sayInteger(seconds);
    play(MP3_TRACK_SECONDS);
    waitUntilIdle();
}

void Mp3Player_::waitUntilIdle()
{
    delay(100); // wait for playing to commence
    while(busy()) { ; } // wait until not busy
}


