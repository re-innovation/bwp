#include <SoftwareSerial.h>
#include <MutilaDebug.h>
#include <Arduino.h>
#include "Mp3Player.h"
#include "Config.h"

// A global object
Mp3Player_ Mp3Player;

Mp3Player_::Mp3Player_() :
    DFPReader(_serial, DFPlayerMini::PlayTf, MP3_BUSY_PIN),
    _serial(MP3_TX_PIN, MP3_RX_PIN)
{
}

void Mp3Player_::begin()
{
    _serial.begin(9600);
    delay(200);
    DFPReader::begin();
    // TODO: handle amp power control 
    pinMode(MP3_POWER_PIN, OUTPUT);
    enable(true);
    
    // TODO: load volume from EEPROM
    setVolume(MP3_VOLUME);
}

void Mp3Player_::play(uint16_t trackNumber)
{
#ifdef MP3DEBUG
    Serial.print(F("Mp3Player_::play track="));
    Serial.println(trackNumber);
#endif
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
    _volume = v;
    sendCmd(DFPlayerMini::SetVolume, v);
}

void Mp3Player_::enable(bool enabled)
{
    digitalWrite(MP3_POWER_PIN, enabled ? HIGH : LOW);
}

