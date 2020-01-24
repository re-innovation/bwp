#include "ModeSwitch.h"
#include "SleepMode.h"

void switchMode(Mode* newMode)
{
    CurrentMode->stop();
    CurrentMode = newMode;
    CurrentMode->start();
}


