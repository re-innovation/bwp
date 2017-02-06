#pragma once

// from Mutila library
#include <Mode.h>  

/*! \brief Diagnostic Mode Control Class
 * This mode responds to button presses to change settings and read
 * out diagnostic information which is stored in EEPROM memory.
 */
class DiagnosticFrameSyncMode_ : public Mode {
public:
    DiagnosticFrameSyncMode_();
    void modeStart();
    void modeStop();
    void modeUpdate();
    bool isFinished();

};

// A global object for this class, in the same style as the Arduino Serial object
extern DiagnosticFrameSyncMode_ DiagnosticFrameSyncMode;

