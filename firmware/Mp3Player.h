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
    uint8_t volume() { return _volume; }
    void setVolume(uint8_t v) { _volume = v; }

private:
    SoftwareSerial _serial;
    DFPReader _mp3;
    uint8_t _volume;

};

extern Mp3Player_ Mp3Player;

