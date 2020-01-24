#include <Arduino.h>
#include "DiagnosticMode.h"

#include "Config.h"

#ifdef ENABLE_HEARTBEAT
#include "ProjectorHeartbeat.h"
#endif
#include "SW1.h"
#include "DiagnosticTrackSelectMode.h"
#include "DiagnosticVolumeAdjustMode.h"
#include "DiagnosticManualFeedMode.h"
#include "DiagnosticFrameSyncMode.h"
#include "DiagnosticCrankSpeedMode.h"
#include "DiagnosticStatUsesMode.h"
#include "DiagnosticStatSecondsMode.h"
#include "DiagnosticStatAvgSecondsMode.h"
#include "Mp3Player.h"
#include "Settings.h"

// Our global instance of the mode...
DiagnosticMode_ DiagnosticMode;

DiagnosticMode_::DiagnosticMode_() 
{
}

void DiagnosticMode_::modeStart()
{
    Serial.println(F("DiagnosticMode"));

#ifdef ENABLE_HEARTBEAT
    ProjectorHeartbeat.setMode(Heartbeat::Slower);
#endif
    Mp3Player.setVolume(VolumeSetting.load());
    subMode = NULL;
    _done = false;
    _startTime = Millis();
    Settings.dump();
}

void DiagnosticMode_::modeStop()
{
    subMode->stop();
}

void DiagnosticMode_::modeUpdate()
{
    if (subMode == NULL) {
        // only start the first sub mode after a short delay
        // this is necessary for Mp3Player to wake up
        if (MillisSince(_startTime) > DIAGNOSTIC_MODE_DELAY) {
            subMode = &DiagnosticVolumeAdjustMode;
            subMode->start();
        }
    } else {
        if (subMode->isFinished()) {
            if (subMode == &DiagnosticVolumeAdjustMode) {
                switchSubMode(&DiagnosticTrackSelectMode);
            } else if (subMode == &DiagnosticTrackSelectMode) {
                switchSubMode(&DiagnosticManualFeedMode);
            } else if (subMode == &DiagnosticManualFeedMode) {
                switchSubMode(&DiagnosticFrameSyncMode);
            } else if (subMode == &DiagnosticFrameSyncMode) {
                switchSubMode(&DiagnosticCrankSpeedMode);
            } else if (subMode == &DiagnosticCrankSpeedMode) {
                switchSubMode(&DiagnosticStatUsesMode);
            } else if (subMode == &DiagnosticStatUsesMode) {
                switchSubMode(&DiagnosticStatSecondsMode);
            } else if (subMode == &DiagnosticStatSecondsMode) {
                switchSubMode(&DiagnosticStatAvgSecondsMode);
            } else if (subMode == &DiagnosticStatAvgSecondsMode) {
                _done = true;
            }
        }

        // Give timeslice to current sub-mode
        subMode->update();
    }

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

