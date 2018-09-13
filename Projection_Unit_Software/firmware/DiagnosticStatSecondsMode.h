#pragma once

// from Mutila library
#include <Mode.h>  

/*! \brief Diagnostic Mode - Readout Usage Stats
 */
class DiagnosticStatSecondsMode_ : public Mode {
public:
    DiagnosticStatSecondsMode_();
    void modeStart();
    void modeStop();
    void modeUpdate() {;}
    bool isFinished();

};

// A global object for this class, in the same style as the Arduino Serial object
extern DiagnosticStatSecondsMode_ DiagnosticStatSecondsMode;

