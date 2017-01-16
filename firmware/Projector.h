#pragma once

#include <AccelStepper.h>
#ifdef TESTMODE
#include <DebouncedButton.h>
#endif
#include "AudioMarkReader.h"

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

    /*! Stop the shutter open sequence (turn off LED, resume film movement)
     */
    void closeShutter();

    /*! Get the current frame offset value */
    int8_t frameOffset() { return _frameOffset; }

    /*! Set the frame offset value */
    void setFrameOffset(int8_t o) { _frameOffset = o; }

    /*! Get the current mute state */
    bool muted() { return _muted; }

    /*! Get the current mute state */
    void setMute(bool muted) { _muted = muted; }

    /*! Get the current shutter mode */
    bool shutter() { return _shutter; }

    /*! Get the current shutter mode */
    void setShutter(bool on) { _shutter = on; }

private:
    /*! Start the shutter open sequence (stop film movement, turn on LED)
     */
    void openShutter();

    /*! Call when a stepper [half] step is triggered - updates state relating
     * to frame sensing / display.
     */
    void frameStep();

    /*! Call when a stepper [half] step is triggered - updates state relating
     * to audio mark sensing / playback.
     */
    void audioStep();

    //////////// Data members
    //! Object to control the stepper motor which moves the film sprocket
    AccelStepper _stepper;

#ifdef TESTMODE
    //! When TESTMODE is defined, steps are triggered by the
    //! press of a button, not by stepper motor activity.
    DebouncedButton _testButton;
#endif

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

    //! For monitoring the state of the audio mark sensor
    AudioMarkReader _audioMarkSensor;

    int8_t _frameOffsetCounter;
    int8_t _frameOffset;

    bool _muted;
    bool _shutter;

};

// Arduino library class style global object
extern Projector_ Projector;

