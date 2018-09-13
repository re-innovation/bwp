#include <SoftwareSerial.h>
#include <MutilaDebug.h>
#include <Arduino.h>
#include "Mp3Player.h"
#include "Config.h"

// A global object
Mp3Player_ Mp3Player;

Mp3Player_::Mp3Player_() :
    _serial(MP3_TX_PIN, MP3_RX_PIN),
    _mp3(_serial)
{
}

void Mp3Player_::begin()
{
    _serial.begin(9600);
    _mp3.sendCmd(DFPlayerMini::Reset);
    delay(80);
    _mp3.sendCmd(DFPlayerMini::SetVolume, MP3_VOLUME);
}

void Mp3Player_::play(uint16_t trackNumber)
{
#ifdef MP3DEBUG
    Serial.print(F("Mp3Player_::play track="));
    Serial.println(trackNumber);
#endif
    _mp3.sendCmd(DFPlayerMini::PlayTf, trackNumber);
}



