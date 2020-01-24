#pragma once

// from Mutila library
#include <Mode.h>  

/*! \brief Setup mode for setting playback volume
 *
 */
class DiagnosticVolumeAdjustMode_ : public Mode {
public:
    DiagnosticVolumeAdjustMode_();
    void modeStart();
    void modeStop();
    void modeUpdate();
    bool isFinished();

private:
    unsigned long _startTime;

};

// A global object for this class, in the same style as the Arduino Serial object
extern DiagnosticVolumeAdjustMode_ DiagnosticVolumeAdjustMode;

