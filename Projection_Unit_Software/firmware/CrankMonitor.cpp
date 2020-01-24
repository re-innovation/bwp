#include <Arduino.h>
#include <Millis.h>
#include "CrankMonitor.h"
#include "Settings.h"

volatile uint32_t prevCrank = 1;
volatile uint32_t lastCrank = 2;

void onCrankSensor()
{
    prevCrank = lastCrank;
    lastCrank = Millis();
}

void crankWakeup()
{
    prevCrank = lastCrank;
}

float crankPulsePerSecond()
{
    return 1000.0 / ((Millis() - lastCrank) + (lastCrank - prevCrank));
}

bool crankSpeedAboveThreshold()
{
    return crankPulsePerSecond() >= (CrankSpeedSetting.get() / 10.0);
}
