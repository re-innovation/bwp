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
    bool busy();

private:
    SoftwareSerial _serial;
    unsigned long _enabledAt;
    uint8_t _currentVolume;
    unsigned long _lastStart;

};

#define STOP_MP3 do { Mp3Player.stop() ; for (int i=0; i<50; i++) { Mp3Player.update() ; delay(1); } } while (0)

extern Mp3Player_ Mp3Player;

