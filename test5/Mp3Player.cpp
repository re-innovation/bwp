#include <DFPlayerMini.h>
#include <SoftwareSerial.h>
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
    _mp3.sendCmd(DFPlayerMini::SetVolume, MP3_VOLUME);
}

void Mp3Player_::play(uint16_t trackNumber)
{
    _mp3.sendCmd(DFPlayerMini::Play, trackNumber);
}



