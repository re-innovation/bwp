#pragma once

#include <DFPlayerMini.h>
#include <SoftwareSerial.h>
#include <stdint.h>

class Mp3Player_ {
public:
    Mp3Player_();

    void begin();
    void play(uint16_t trackNumber);
    bool busy();
    void sayDigit(uint8_t d);
    void sayInteger(long n);
    void sayDuration(long n);
    void waitUntilIdle();

private:
    SoftwareSerial _serial;
    DFPlayerMini _mp3;

};

extern Mp3Player_ Mp3Player;

