#pragma once

#include <DFPlayerMini.h>
#include <SoftwareSerial.h>

class Mp3Player_ {
public:
    Mp3Player_();

    void begin();
    void play(uint16_t trackNumber);

private:
    SoftwareSerial _serial;
    DFPlayerMini _mp3;

};

extern Mp3Player_ Mp3Player;

