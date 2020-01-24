#pragma once

#include <Mode.h>

/*! \brief Sleep Mode Control Class
 * When the installation is inacitve, it is put into SleepMode, which will
 * set the Arduino into a low power usage sleep mode. The Arduino wakes up on 
 * an interrupt from the crank sensor, and SleepMode ends, going into 
 * WakeupMode.
 */
class SleepMode_ : public Mode {
public:
    SleepMode_();
    void begin();
    void modeStart();
    void modeStop();
    void modeUpdate();

};

// A global object for this class, in the same style as the Arduino Serial object
extern SleepMode_ SleepMode;

