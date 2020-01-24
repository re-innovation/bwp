#pragma once

extern volatile uint32_t prevCrank;
extern volatile uint32_t lastCrank;

// Triggered by interrupt when the crank sensor activates
void onCrankSensor(); 

void crankWakeup();

// Returns current "pulses per second" from the crank sensor
// note - no de-bouncing is done, so this might be more than 
// expected, but should give some indication of rate of cranking
float crankPulsePerSecond();

// return true if the crank speed is above the current threshold
// as defined by the CrankSpeedSetting value
bool crankSpeedAboveThreshold();

