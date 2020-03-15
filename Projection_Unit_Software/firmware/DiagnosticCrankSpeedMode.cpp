#include <Arduino.h>
#include <Millis.h>
#include "Config.h"
#include "DiagnosticCrankSpeedMode.h"
#include "SW1.h"
#include "SW2.h"
#include "SW3.h"
#include "MutilaDebug.h"
#include "Mp3Player.h"
#include "CrankMonitor.h"
#include "Projector.h"
#include "Settings.h"

// Our global instance of the mode...
DiagnosticCrankSpeedMode_ DiagnosticCrankSpeedMode;

DiagnosticCrankSpeedMode_::DiagnosticCrankSpeedMode_()
{
}

void DiagnosticCrankSpeedMode_::modeStart()
{
    Serial.print(F("DiagnosticCrankSpeedMode speed="));
    Serial.println(CrankSpeedSetting.get());
    //Mp3Player.appendElement(MP3_TRACK_CRANK_SPEED);
    STOP_MP3;
    Mp3Player.appendElement(MP3_TRACK_CRANK_SPEED);
    Mp3Player.readNumber(CrankSpeedSetting.get());
}

void DiagnosticCrankSpeedMode_::modeStop()
{
    Projector.closeShutter();
    CrankSpeedSetting.save();
    Serial.print(F("SAVING speed="));
    Serial.println(CrankSpeedSetting.get());
}

void DiagnosticCrankSpeedMode_::modeUpdate()
{
    if (SW3.tapped()) {
        uint8_t next = CrankSpeedSetting.get()+1;
        CrankSpeedSetting = next > CrankSpeedSetting.getMaximum() ? CrankSpeedSetting.getMinimum() : next;
        Mp3Player.stop();
        Mp3Player.readNumber(CrankSpeedSetting.get());
        Serial.print(F("speed="));
        Serial.println(CrankSpeedSetting.get());
    }
    if (crankSpeedAboveThreshold()) {
        Projector.openShutter();
    } else {
        Projector.closeShutter();
    }
}

bool DiagnosticCrankSpeedMode_::isFinished()
{
    return SW1.tapped() != 0;
}

