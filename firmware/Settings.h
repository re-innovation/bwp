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
    unsigned long getUseCount() { return _useCount; }
    unsigned long getUseSecondaThisRun();
    unsigned long getUseSeconds() { return _useSeconds + getUseSecondaThisRun(); }
    uint16_t volume() { return _volume; }
    void setVolume(uint16_t volume) { _volume = volume; }

private:
    void checkMagic(); //!< see if we should reset settings
    void load();       //!< loads values from EEPROM

    unsigned long _useCount;
    unsigned long _useSeconds;
    uint16_t _volume;
    bool _useCounted;
    bool _running;
    unsigned long _runStart;
    unsigned long _secondsThisRun;

};

extern Settings_ Settings;

