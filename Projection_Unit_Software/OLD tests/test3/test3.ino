#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Config.h"
#include "DFPlayerMini.h"

// Getting the MP3 player working
SoftwareSerial mp3Serial(MP3_TX_PIN, MP3_RX_PIN);
DFPlayerMini mp3(mp3Serial);

void setup()
{
    Serial.begin(115200);
    mp3Serial.begin(9600);
    delay(300);
    DFPResponse r;
    mp3.sendCmd(DFPlayerMini::SetVolume, 15);
    r = mp3.query(DFPlayerMini::GetVolume);
    Serial.print("GetVolume=");
    if (r.status == DFPResponse::Ok) { Serial.println(r.arg); }
    else { Serial.println("ERR"); }
    Serial.println(F("e:setup"));
}

void loop()
{
    Serial.println("Next");
    mp3.sendCmd(DFPlayerMini::Next);
    delay(5000);
}

