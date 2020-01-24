#pragma once

#include <Mode.h>

// defined in firmware.ino
extern Mode* CurrentMode;

void switchMode(Mode* newMode);

