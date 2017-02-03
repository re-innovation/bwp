#include <Arduino.h>
#include "DiagnosticMode.h"
#include "ProjectorHeartbeat.h"
#include "SW1.h"
#include "DiagnosticFrameSyncMode.h"
#include "DiagnosticManualFeedMode.h"
#include "DiagnosticVolumeAdjustMode.h"

// Our global instance of the mode...
DiagnosticMode_ DiagnosticMode;

DiagnosticMode_::DiagnosticMode_()
{
}

void DiagnosticMode_::modeStart()
{
    DBLN(F("DiagnosticMode::modeStart()"));
    ProjectorHeartbeat.setMode(Heartbeat::Quick);
    subMode = &DiagnosticFrameSyncMode;
    subMode->start();
    _done = false;
}

void DiagnosticMode_::modeStop()
{
    DBLN(F("DiagnosticMode::modeStop()"));
    subMode->stop();
}

void DiagnosticMode_::modeUpdate()
{
    // Handle mode changes
    if (subMode->isFinished()) {
        if (subMode == &DiagnosticFrameSyncMode) {
            switchSubMode(&DiagnosticManualFeedMode);
        } else if (subMode == &DiagnosticManualFeedMode) {
            switchSubMode(&DiagnosticVolumeAdjustMode);
        } else if (subMode == &DiagnosticVolumeAdjustMode) {
            _done = true;
        }
    }

    // Give timeslice to current sub-mode
    subMode->update();
}

bool DiagnosticMode_::isFinished()
{
    return _done;
}

void DiagnosticMode_::switchSubMode(Mode* mode)
{
    subMode->stop();
    subMode = mode;
    subMode->start();
}

