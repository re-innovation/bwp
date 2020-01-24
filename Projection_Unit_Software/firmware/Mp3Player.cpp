#include <Arduino.h>
#include <SoftwareSerial.h>
#include <MutilaDebug.h>
#include <Millis.h>
#include "Mp3Player.h"
#include "Config.h"
#include "Settings.h"

// A global object
Mp3Player_ Mp3Player;

Mp3Player_::Mp3Player_() :
    DFPReader(_serial, DFPlayerMini::PlayTf, MP3_BUSY_PIN),
    _serial(MP3_TX_PIN, MP3_RX_PIN),
    _enabledAt(0),
    _lastStart(0)
{
}

void Mp3Player_::begin()
{
    DBLN(F("Mp3Player_::begin"));
    _serial.begin(9600);
    // Turn on the amp
    pinMode(MP3_POWER_PIN, OUTPUT);
    enable(true);

    DFPReader::begin();
    DBLN(F("E:Mp3Player.begin"));
}

void Mp3Player_::play(uint16_t trackNumber)
{
    DB(F("Mp3Player::play track="));
    DBLN(trackNumber);
    if (reading()) {
        stop();
    }
    _lastStart = Millis();
    sendCmd(DFPlayerMini::PlayTf, trackNumber);
}

void Mp3Player_::stop()
{
    resetReaderBuf();
}

uint16_t Mp3Player_::volume()
{
    return _currentVolume;
}

void Mp3Player_::setVolume(uint8_t v)
{
    DB(F("Mp3Player::setVolume to "));
    DBLN(v);
    sendCmd(DFPlayerMini::SetVolume, v);
    _currentVolume = v;
}

void Mp3Player_::enable(bool enabled)
{
    DB(F("Mp3Player::enable to "));
    DBLN(enabled);
    digitalWrite(MP3_POWER_PIN, enabled ? HIGH : LOW);
    if (enabled) {
        _enabledAt = Millis()+1;
    }
}

void Mp3Player_::update()
{
    // the DFPlayerMini has a quirk - if you set the volume less than
    // a second after powering on the device, it doesn't "stick", so we
    // will set the volume if the device was powered on about a second ago
    if (_enabledAt != 0) {
        if (Millis() > _enabledAt + 1000) {
            setVolume(VolumeSetting.get());
            _enabledAt = 0;
        }
    }
    DFPReader::update();
}

bool Mp3Player_::busy()
{
    if (MillisSince(_lastStart) > 50) {
        return reading() || DFPlayerMini::busy();
    } else {
        DBLN(F("busy delay"));
        return true;
    }
}



