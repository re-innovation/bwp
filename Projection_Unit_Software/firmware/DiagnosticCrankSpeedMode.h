#pragma once

// from Mutila library
#include <Mode.h>  

/*! \brief Settings update mode: Crank Speed
 *
 * Allows for configuration of the crank speed. The setting is how many
 * crank reed switch activations per second are necessary to keep the
 * projector running. The numerica value should be divided by 10, so
 * a value of 10 means 1 crank reed switch activation per second, a setting
 * of 20 means 2 per seconds and so on.
 */
class DiagnosticCrankSpeedMode_ : public Mode {
public:
    DiagnosticCrankSpeedMode_();
    void modeStart();
    void modeStop();
    void modeUpdate();
    bool isFinished();

};

// A global object for this class, in the same style as the Arduino Serial object
extern DiagnosticCrankSpeedMode_ DiagnosticCrankSpeedMode;

