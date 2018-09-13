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
    uint16_t volume();
    void setVolume(uint8_t v);
    void enable(bool enabled);
    void update();

private:
    SoftwareSerial _serial;
    unsigned long _enabledAt;

};

extern Mp3Player_ Mp3Player;

