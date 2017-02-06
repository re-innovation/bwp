#include <EEPROM.h>
#include <MutilaDebug.h>
#include "Settings.h"
#include "Config.h"

Settings_ Settings;

void Settings_::begin()
{
    // load values from EEPROM
    load();
    checkMagic(); // verify we don't need to use default values...
    _useCounted = false;

    // we're not running until we're explicitly told that we are
    _running = false;
    _runStart = 0;
    _secondsThisRun = 0;
}

void Settings_::run()
{
    _running = true;
    _runStart = millis();
}

void Settings_::stop()
{
    if (!_useCounted) {
        _useCount++;
        _useCounted = true;
    }
    if (_running) {
        _secondsThisRun += (millis()-_runStart)/1000;
        _running = false;
    }
}

void Settings_::checkMagic()
{
    unsigned long magic;
    EEPROM.get(EEPROM_ADDRESS_MAGIC, magic);
    if (magic != EEPROM_MAGIC) {
        DBLN(F("Settings::checkMagic resetting values"));
        _useCount = 0;
        _useSeconds = 0;
        _volume = 15;
        magic = EEPROM_MAGIC;
        EEPROM.put(EEPROM_ADDRESS_MAGIC, magic);
        save();
    }
}

void Settings_::load()
{
    EEPROM.get(EEPROM_ADDRESS_USE_COUNT, _useCount);
    EEPROM.get(EEPROM_ADDRESS_USE_SECONDS, _useSeconds);
    EEPROM.get(EEPROM_ADDRESS_VOLUME, _volume);
    DB(F("Settings::load() uses="));
    DB(_useCount);
    DB(F(" seconds="));
    DB(_useSeconds);
    DB(F(" volume="));
    DBLN(_volume);
}

void Settings_::save()
{
    unsigned long tmp = getUseSeconds();
    DB(F("Settings::save() uses="));
    DB(_useCount);
    DB(F(" seconds="));
    DB(tmp);
    DB(F(" volume="));
    DBLN(_volume);
    // Note: EEPROM.put uses EEPROM.update(), which only writes a
    // value if it is different from the value already saved to EEPROM
    EEPROM.put(EEPROM_ADDRESS_USE_COUNT, _useCount);
    EEPROM.put(EEPROM_ADDRESS_USE_SECONDS, tmp);
    EEPROM.put(EEPROM_ADDRESS_VOLUME, _volume);
}

unsigned long Settings_::getUseSecondaThisRun() 
{
    if (_running) {
        return _secondsThisRun + (millis()-_runStart)/1000;
    } else {
        return _secondsThisRun;
    }
}

