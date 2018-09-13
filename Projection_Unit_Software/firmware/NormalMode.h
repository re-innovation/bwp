#pragma once

#include <BrownoutMode.h>
#include "Projector.h"

/*! \brief Normal Mode Control Class
 * In normal operation, the projector runs when powered, but monitors the input
 * voltage for brownout conditions.  When entering brownout, the mode saves 
 * various runtime statistics to EEPROM
 */
class NormalMode_ : public BrownoutMode {
public:
    NormalMode_(EMAVDivSampler& vSampler, const float vThreshLow, const float vThreshHigh);
    void modeStart();
    void modeStop();
    void enterBrownout();
    void exitBrownout();
    void modeUpdate();
    bool isFinished();

private:
    uint16_t runCount;
    uint32_t runSeconds;

};

extern NormalMode_ NormalMode;

