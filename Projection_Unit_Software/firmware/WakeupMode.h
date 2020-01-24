#pragma once

#include <Mode.h>

/*! \brief Wakeup Mode Control Class
 * Immediately after waking from sleep, WakeupMode is activated. While active,
 * the crank turn rate is monitored: 
 * - If it drops below the minimum turn rate, the system is put back into SleepMode
 * - If the rate is above the minimum rate for some time, NormalMode is set
 */
class WakeupMode_ : public Mode {
public:
    WakeupMode_();
    void modeStart();
    void modeStop();
    void modeUpdate();
    bool isFinished();

private:
    uint32_t _startTime;

};

// A global object for this class, in the same style as the Arduino Serial object
extern WakeupMode_ WakeupMode;

