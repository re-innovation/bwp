#pragma once

// from Mutila library
#include <Mode.h>  

/*! \brief Frame Sync Mode Setting
 *
 * Allows for adjustment of the frame sync offset.
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

