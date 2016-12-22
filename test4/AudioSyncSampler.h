#pragma once

#include <stdint.h>
#include <EMASampler.h>

/* Detects a stream of pulses from an analog sensor which encode some data
 * When average() passes threshold, a new pulse is available which has data
 * about the on/off state during the previous state, and how many ticks
 * that state was read for.
 */

class AudioSyncSampler : public EMASampler {
public:
    AudioSyncSampler(uint8_t pin, float alpha, uint16_t thresh);
    void begin();
    bool check();
    bool on();

    bool lastPulseState() { return _lastPulseState; }
    unsigned long lastPulseLength() { return _lastPulseLength; }

private:
    uint32_t _pulseCount;
    uint32_t _pulseStart;
    uint16_t _thresh;
    bool _state;
    bool _lastPulseState;
    unsigned long _lastPulseLength;

};

