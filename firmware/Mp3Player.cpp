#include <SoftwareSerial.h>
#include <MutilaDebug.h>
#include <Arduino.h>
#include "Mp3Player.h"
#include "Config.h"

// A global object
Mp3Player_ Mp3Player;

Mp3Player_::Mp3Player_() :
    DFPReader(_serial, DFPlayerMini::PlayTf, MP3_BUSY_PIN),
    _serial(MP3_TX_PIN, MP3_RX_PIN),
    _enabledAt(0)
{
}

void Mp3Player_::begin()
{
    DBLN(F("Mp3Player_::begin"));
    _serial.begin(9600);
    pinMode(MP3_POWER_PIN, OUTPUT);
    enable(true);
    DFPReader::begin();
    _volume = MP3_VOLUME;
    // Turn on the amp
}

void Mp3Player_::play(uint16_t trackNumber)
{
    DB(F("Mp3Player_::play track="));
    DBLN(trackNumber);
    if (reading()) {
        stop();
    }
    sendCmd(DFPlayerMini::PlayTf, trackNumber);
}

void Mp3Player_::stop()
{
    resetReaderBuf();
}

void Mp3Player_::setVolume(uint8_t v)
{
    DB(F("Mp3Player_::setVolume to "));
    DBLN(v);
    _volume = v;
    sendCmd(DFPlayerMini::SetVolume, v);
}

void Mp3Player_::enable(bool enabled)
{
    DB(F("Mp3Player_::enable to "));
    DBLN(enabled);
    digitalWrite(MP3_POWER_PIN, enabled);
    if (enabled) {
        _enabledAt = millis()+1;
    }
}

void Mp3Player_::update()
{
    // the DFPlayerMini has a quirk - if you set the volume less than
    // a second after powering on the device, it doesn't "stick", so we
    // will set the volume if the device was powered on about a second ago
    if (_enabledAt != 0) {
        if (millis() > _enabledAt + 1000) {
            setVolume(_volume);
            _enabledAt = 0;
        }
    }
    DFPReader::update();
}

