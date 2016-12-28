#pragma once

#include <AccelStepper.h>

class Stepper_ {
public:
    /*! Constructor
     * Note will take pin definitions from Config.h constants STEPPER_PIN_1
     * STEPPER_PIN_2 STEPPER_PIN_3 STEPPER_PIN_4 
     */
    Stepper_();

    /*! Initialize
     * Should be called before use - probably from setup(). Note: will
     * use values of STEPPER_STEPS_PER_SEC and STEPPER_MAX_SPEED from Config.h
     */
    void begin();

    /*! Check for (half) step
     * Should be called as often as possible. Will return true when 
     * the stepper has been advanced a half step, else false
     */
    bool step();

private:
    AccelStepper _stepper;

};

// Arduino library class style global object
extern Stepper_ Stepper;

