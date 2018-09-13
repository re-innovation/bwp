#include <Arduino.h>
#include <MutilaDebug.h>
#include "Mp3Player.h"

void setup()
{
    Serial.begin(115200);
    delay(300);

    Serial.println("Hai there");

    Mp3Player.begin();

    int i=0;
    while (1) {
        DB("Playing ");
        DBLN(i);
        Mp3Player.play(i);
        i = (i+1)%11;
        delay(1000);
    }
}

void loop()
{
}

