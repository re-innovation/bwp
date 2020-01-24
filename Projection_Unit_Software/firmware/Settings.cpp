#include <stdint.h>
#include <EEPROM.h>
#include <MutilaDebug.h>
#include <Millis.h>
#include "Settings.h"
#include "Config.h"

Settings_ Settings;

// On Arduino Nano:
// sizeof char:       1
// sizeof short:      2
// sizeof int:        2
// sizeof long:       4
// sizeof long long:  8
// sizeof float:      4
// sizeof double:     4
//                                                  Min     Max         Default Wear
//                                                  value   value       value   level
PersistentSetting<uint32_t> UseCountStat        (   0,      UINT32_MAX, 0,      10);
PersistentSetting<uint32_t> UseSecondsStat      (   0,      UINT32_MAX, 0,      10);
PersistentSetting<uint16_t> VolumeSetting       (   1,      30,         15,     3);
PersistentSetting<uint8_t> FrameOffsetSetting   (   0,      25,         0,      3);
PersistentSetting<uint8_t> AudioTrackSetting    (   1,      10,         1,      3);
PersistentSetting<uint8_t> CrankSpeedSetting    (   1,      30,         10,     3);

// This is not a real setting - we use it to determine if the EEPROM has been
// used before with this set of settings, or if we should load the defaults
PersistentSetting<uint16_t> MagicSetting        (   0,      UINT16_MAX, MagicNumber);

Settings_::Settings_() 
{
}

void Settings_::begin()
{
    checkMagic(); // see if we want to load defaults or from EEPROM

    // we're not running until we're explicitly told that we are
    _running = false;
    _runStart = 0;
    DBLN(F("E:Settings.begin"));
}

void Settings_::run()
{
    if (!_running) {
        _running = true;
        _runStart = Millis();
    }
}

void Settings_::stop()
{
    if (_running) {
        _running = false;
        // update and save run stats
        uint32_t count = UseCountStat.get() + 1;
        uint32_t seconds = (Millis() - _runStart) / 1000;
        Serial.print(F("SAVING STATS: count="));
        Serial.print(count);
        Serial.print(F(" this-run-sec="));
        Serial.print(seconds);
        Serial.print(F(" total-sec="));
        Serial.println(UseSecondsStat.get() + seconds);
        UseCountStat.set(count, true);
        UseSecondsStat.set(UseSecondsStat.get() + seconds, true);
    }
}

void Settings_::checkMagic()
{
    // This is an indicator that the device has never had the settings saved, as
    // the default value in the EEPROM is probably 0x00, 0xFF, or at least some random
    // value which is not MagicNumber...
    if (MagicSetting.get() != MagicNumber) {
        // Save all the settings with their default values
        Serial.println(F("FRESH EEPROM!"));
        reset(true);
        MagicSetting.reset(true);
    } else {
        load();
    }   
}

void Settings_::load()
{
    Serial.println(F("\nEEPROM LOAD"));
    UseCountStat.load();
    UseSecondsStat.load();
    VolumeSetting.load();
    FrameOffsetSetting.load();
    AudioTrackSetting.load();
    CrankSpeedSetting.load();
}

void Settings_::reset(bool save)
{
    Serial.println();
    Serial.print(F("EEPROM RESET "));
    Serial.println(save ? F("(save)") : F("(no save)"));
    UseCountStat.reset(save);
    UseSecondsStat.reset(save);
    VolumeSetting.reset(save);
    FrameOffsetSetting.reset(save);
    AudioTrackSetting.reset(save);
    CrankSpeedSetting.reset(save);
}

void Settings_::dump()
{
    Serial.println();
    Serial.print(F("UseCountStat       "));
    Serial.println(UseCountStat.get());
    Serial.print(F("UseSecondsStat     "));
    Serial.println(UseSecondsStat.get());
    Serial.print(F("VolumeSetting      "));
    Serial.println(VolumeSetting.get());
    Serial.print(F("FrameOffsetSetting "));
    Serial.println(FrameOffsetSetting.get());
    Serial.print(F("AudioTrackSetting  "));
    Serial.println(AudioTrackSetting.get());
    Serial.print(F("CrankSpeedSetting  "));
    Serial.println(CrankSpeedSetting.get());
}


