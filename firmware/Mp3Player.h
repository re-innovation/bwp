#pragma once

#include <DFPReader.h>
#include <SoftwareSerial.h>
#include <stdint.h>

class Mp3Player_ {
public:
    Mp3Player_();

    void begin();
    void update();
    //! Immediate play
    void play(uint16_t trackNumber);
    void stop();
    bool busy();
    void readNumber(double n, uint8_t dp);

private:
    SoftwareSerial _serial;
    DFPReader _mp3;

};

extern Mp3Player_ Mp3Player;

