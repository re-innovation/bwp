#pragma once

// from Mutila library
#include <Mode.h>  

/*! \brief Manual Feed Mode
 * When the set button is pressed and held, feed the projector without 
 * using the shutter (for loading and unloading film).
 */
class DiagnosticManualFeedMode_ : public Mode {
public:
    DiagnosticManualFeedMode_();
    void modeStart();
    void modeStop();
    void modeUpdate();
    bool isFinished();

};

// A global object for this class, in the same style as the Arduino Serial object
extern DiagnosticManualFeedMode_ DiagnosticManualFeedMode;

