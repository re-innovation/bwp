#pragma once

// from Mutila library
#include <Mode.h>  

/*! \brief Manual Feed Mode
 *
 * Allows projector feed to be manually moved. For use when loading new film.
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

