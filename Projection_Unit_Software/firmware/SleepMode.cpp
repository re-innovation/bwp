#include <Arduino.h>
#include <avr/sleep.h>
#include <MutilaDebug.h>
#include <Millis.h>
#include "SleepMode.h"
#include "CrankMonitor.h"
#include "ProjectorHeartbeat.h"
#include "Projector.h"
#include "Mp3Player.h"
#include "Settings.h"
#include "Config.h"

// Our global instance of the mode...
SleepMode_ SleepMode;

SleepMode_::SleepMode_()
{
    setUpdatePeriod(100);
}

void SleepMode_::begin()
{
}

void SleepMode_::modeStart()
{
    Serial.println(F("SleepMode"));

    // power down everything we can
    ProjectorHeartbeat.setMode(Heartbeat::Off);
    Projector.closeShutter();
    Projector.setStepperEnabled(false);
    Mp3Player.stop();
    Mp3Player.enable(false);
    Settings.stop();

    // Allow serial messages to clear
    delay(10);

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();     // ready, set...
    sleep_mode();       // sleep

    sleep_disable();
    Serial.println(F("Arduino wakeup"));

    // power up components
    Mp3Player.enable(true);
    Projector.setStepperEnabled(true);
    crankWakeup();

    // This mode can now end
    _state = Mode::RunState::Finished;
}

void SleepMode_::modeStop()
{
}

void SleepMode_::modeUpdate()
{
}

