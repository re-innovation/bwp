#pragma once

#include <stdint.h>

//! \class Settings
//! Keeps track of usage statistics and other settings which are to
//! be stored in EEPROM
class Settings_ {
public:
    Settings_() {;}

    void begin();  //!< Initialize
    void run();    //!< Notify we're running
    void stop();   //!< Notify we're stopping (browning out)
    void save();   //!< saves values to EEPROM

    // Accessors
    unsigned long getUseCount() { return _useCount + (_useCounted ? 0 : 1); }
    unsigned long getUseSecondaThisRun();
    unsigned long getUseSeconds() { return _useSeconds + getUseSecondaThisRun(); }

    uint16_t volume() { return _volume; }
    uint8_t frameOffset() { return _frameOffset; }
    uint8_t audioCount() { return _audioCount; }
    uint8_t lastAudio() { return _lastAudio; }

    void setVolume(uint16_t volume) { _volume = volume; }
    void setFrameOffset(uint8_t frameOffset) { _frameOffset = frameOffset; }
    void setAudioCount(uint8_t count) { _audioCount = count; }
    void setLastAudio(uint8_t n) { _lastAudio = n; }

private:
    void checkMagic(); //!< see if we should reset settings
    void load();       //!< loads values from EEPROM

    unsigned long _useCount;
    unsigned long _useSeconds;
    uint16_t _volume;
    uint8_t _frameOffset;
    uint8_t _audioCount;
    uint8_t _lastAudio;
    bool _useCounted;
    bool _running;
    unsigned long _runStart;
    unsigned long _secondsThisRun;

};

extern Settings_ Settings;

