#pragma once

#include <Mode.h>
#include "Projector.h"

/*! \brief Normal Mode Control Class
 * In normal operation, the projector runs and plays sound. If the crank turn rate
 * drops below some threshold, the mode will end and the projector will go into 
 * TiredMode.
 */
class NormalMode_ : public Mode {
public:
    NormalMode_();
    void modeStart();
    void modeStop();
    void modeUpdate();
    bool isFinished();

private:
    uint16_t runCount;
    uint32_t runSeconds;
    unsigned long lastAudioCheck;

};

extern NormalMode_ NormalMode;

