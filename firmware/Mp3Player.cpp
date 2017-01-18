#include <SoftwareSerial.h>
#include <MutilaDebug.h>
#include <Arduino.h>
#include "Mp3Player.h"
#include "Config.h"

// A global object
Mp3Player_ Mp3Player;

Mp3Player_::Mp3Player_() :
    _serial(MP3_TX_PIN, MP3_RX_PIN),
    _mp3(_serial, DFPlayerMini::PlayTf, MP3_BUSY_PIN)
{
}

void Mp3Player_::begin()
{
    _serial.begin(9600);
    _mp3.begin();
    _mp3.sendCmd(DFPlayerMini::SetVolume, MP3_VOLUME);
}

void Mp3Player_::update()
{
    _mp3.update();
}

void Mp3Player_::play(uint16_t trackNumber)
{
#ifdef MP3DEBUG
    Serial.print(F("Mp3Player_::play track="));
    Serial.println(trackNumber);
#endif
    if (busy()) {
        stop();
    }
    _mp3.sendCmd(DFPlayerMini::PlayTf, trackNumber);
}

void Mp3Player_::stop()
{
    _mp3.resetReaderBuf();
}

bool Mp3Player_::busy()
{
    return !_mp3.reading();
}

void Mp3Player_::readNumber(double n, uint8_t dp)
{
    readNumber(n, dp);
}

