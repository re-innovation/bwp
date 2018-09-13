#pragma once

// from Mutila library
#include <Mode.h>  

/*! \brief Diagnostic Mode - Readout Usage Stats
 */
class DiagnosticStatUsesMode_ : public Mode {
public:
    DiagnosticStatUsesMode_();
    void modeStart();
    void modeStop();
    void modeUpdate() {;}
    bool isFinished();

};

// A global object for this class, in the same style as the Arduino Serial object
extern DiagnosticStatUsesMode_ DiagnosticStatUsesMode;

