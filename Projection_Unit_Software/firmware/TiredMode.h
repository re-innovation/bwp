#pragma once

#include <Mode.h>

/*! \brief Tired Mode Control Class
 * TiredMode is entered from NormalMode when the crank turn rate drops below the
 * minimum turn rate. If the turn rate does not rise above the minimum for some
 * time, the system will go into SleepMode.  If the rate rises above the minimum 
 * level, NormalMode is resumed.  The idea is to give the user a short time to 
 * resume playback without having to go back to the start if they slow down 
 * cranking a bit too much.
 */
class TiredMode_ : public Mode {
public:
    TiredMode_();
    void modeStart();
    void modeStop();
    void modeUpdate();
    bool isFinished();

private:
    uint32_t _startTime;

};

// A global object for this class, in the same style as the Arduino Serial object
extern TiredMode_ TiredMode;

