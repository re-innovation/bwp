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
        _frameOffset = 0;
        _audioCount = 0;
        _lastAudio = 0;
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
    EEPROM.get(EEPROM_ADDRESS_FRAME_OFFSET, _frameOffset);
    EEPROM.get(EEPROM_ADDRESS_AUDIO_COUNT, _audioCount);
    EEPROM.get(EEPROM_ADDRESS_LAST_AUDIO, _lastAudio);
    DB(F("Settings::load() uses="));
    DB(_useCount);
    DB(F(" seconds="));
    DB(_useSeconds);
    DB(F(" volume="));
    DB(_volume);
    DB(F(" frameOffset="));
    DB(_frameOffset);
    DB(F(" audioCount="));
    DB(_audioCount);
    DB(F(" lastAudio="));
    DBLN(_lastAudio);
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
    DB(F(" frameOffset="));
    DB(_frameOffset);
    DB(F(" audioCount="));
    DB(_audioCount);
    DB(F(" lastAudio="));
    DBLN(_lastAudio);
    // Note: EEPROM.put uses EEPROM.update(), which only writes a
    // value if it is different from the value already saved to EEPROM
    EEPROM.put(EEPROM_ADDRESS_USE_COUNT, _useCount);
    EEPROM.put(EEPROM_ADDRESS_USE_SECONDS, tmp);
    EEPROM.put(EEPROM_ADDRESS_VOLUME, _volume);
    EEPROM.put(EEPROM_ADDRESS_FRAME_OFFSET, _frameOffset);
    EEPROM.put(EEPROM_ADDRESS_AUDIO_COUNT, _audioCount);
    EEPROM.put(EEPROM_ADDRESS_LAST_AUDIO, _lastAudio);
}

unsigned long Settings_::getUseSecondaThisRun() 
{
    if (_running) {
        return _secondsThisRun + (millis()-_runStart)/1000;
    } else {
        return _secondsThisRun;
    }
}

