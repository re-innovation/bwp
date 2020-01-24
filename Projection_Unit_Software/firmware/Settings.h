#pragma once

#include <PersistentSetting.h>
#include <stdint.h>

//! \class Settings
//! Keeps track of usage statistics and other settings which are to
//! be stored in EEPROM
class Settings_ {
public:
    Settings_();

    void begin();  //!< Initialize
    void run();    //!< Notify we're running (start use timer)
    void stop();   //!< Notify we're stopping (save use stats)
    void dump();   //!< dump the values of the settings to Serial

private:
    void checkMagic();      //!< see if we should reset settings
    void load();            //!< loads values from EEPROM
    void reset(bool save);  //!< reset default values (and save to EEPROM or not)

    bool _running;
    unsigned long _runStart;

};

extern Settings_ Settings;

extern PersistentSetting<uint32_t> UseCountStat;
extern PersistentSetting<uint32_t> UseSecondsStat;
extern PersistentSetting<uint16_t> VolumeSetting;
extern PersistentSetting<uint8_t> FrameOffsetSetting;
extern PersistentSetting<uint8_t> AudioTrackSetting;
extern PersistentSetting<uint8_t> CrankSpeedSetting;

// The first time the device is booted with this firmware, we see if MagicSetting
// is set to MagicNumber. If it is, we deduce that this device has already been
// set up with these settings and does not need the defaults set.
extern PersistentSetting<uint16_t> MagicSetting;
const uint16_t MagicNumber = 0xFA7E; 


