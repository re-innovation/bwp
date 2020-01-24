#pragma once

// from Mutila library
#include <Mode.h>  

/*! \brief Diagnostic Mode Control Class
 *
 * Parent mode for all the other setting / diagnotic modes
 */
class DiagnosticMode_ : public Mode {
public:
    DiagnosticMode_();
    void modeStart();
    void modeStop();
    void modeUpdate();
    bool isFinished();

private:
    void switchSubMode(Mode* mode);
    Mode* subMode;
    bool _done;
    unsigned long _startTime;

};

// A global object for this class, in the same style as the Arduino Serial object
extern DiagnosticMode_ DiagnosticMode;

