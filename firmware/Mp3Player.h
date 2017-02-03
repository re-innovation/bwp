#pragma once

#include <DFPReader.h>
#include <SoftwareSerial.h>
#include <stdint.h>

class Mp3Player_ : public DFPReader {
public:
    Mp3Player_();
    void begin();
    void play(uint16_t trackNumber);
    void stop();
    uint8_t volume() { return _volume; }
    void setVolume(uint8_t v);
    void enable(bool enabled);

private:
    SoftwareSerial _serial;
    uint8_t _volume;

};

extern Mp3Player_ Mp3Player;

