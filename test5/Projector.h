#pragma once

#include <AccelStepper.h>

/*! \brief model/control the projector
 * This class, and associated global Projector singleton instance, model the projector.
 * The projector has the following components:
 * -# Stepper motor for advancing film
 * -# Shutter (LED controlled via a digital output)
 * -# Optical sensor for reading frame synchronization holes in film
 * -# Optical sensor for reading audio codes
 *
 * The projector class advances the film using the stepper motor until a frame
 * synchronication hole is read by the appropriate sensor. It then halt the stepper,
 * "opens" the shutter for some fixed period of time, "closes" the shutter and 
 * then resumes the stepper.
 *
 * It also monitors the optical sensor for reading audio codes, populating a
 * buffer with code bits as they are read, and triggering audio playback
 * with a global singleton instance, Mp3Player.
 */
class Projector_ {
public:
    /*! Constructor
     * Note will take pin definitions from Config.h constants STEPPER_PIN_1
     * STEPPER_PIN_2 STEPPER_PIN_3 STEPPER_PIN_4 
     */
    Projector_();

    /*! Initialize
     * Should be called before use - probably from setup(). Note: will
     * use values of STEPPER_STEPS_PER_SEC and STEPPER_MAX_SPEED from Config.h
     */
    void begin();

    /*! Allocate timeslice
     * Should be called frequently from loop()
     */
    void update();

private:
    /*! Called when a stepper [half] step is triggered. Used to increment
     * counters, test for frame sync, and read the audio marker sensor.
     */
    void step();

    /*! Start the shutter open sequence (stop film movement, turn on LED)
     */
    void openShutter();

    /*! Stop the shutter open sequence (turn off LED, resume film movement)
     */
    void closeShutter();

    //! Object to control the stepper motor which moves the film sprocket
    AccelStepper _stepper;

    //! How many steps have happened since the last frame was displayed
    uint8_t _stepsSinceFrame;

    //! The previously read value from the frame hole sensor
    int _lastFrameSensorValue;

    //! Special flag to say if we've never found a sync - in this case
    //! we are more permissive about detecting a hole the first time...
    bool _frameSyncFound;

    //! Indicator to say the shutter sequence is in progress
    bool _shutterOpen;

    //! For timing shutter sequence
    unsigned long _shutterStart;

};

// Arduino library class style global object
extern Projector_ Projector;

