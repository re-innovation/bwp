#pragma once

// from Mutila library
#include <Mode.h>  

/*! \brief Track Selection Mode
 *
 * Allows for selection of the track to be played when the projector is running.
 */
class DiagnosticTrackSelectMode_ : public Mode {
public:
    DiagnosticTrackSelectMode_();
    void modeStart();
    void modeStop();
    void modeUpdate();
    bool isFinished();

};

// A global object for this class, in the same style as the Arduino Serial object
extern DiagnosticTrackSelectMode_ DiagnosticTrackSelectMode;

