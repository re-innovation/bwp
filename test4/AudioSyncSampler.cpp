#include "AudioSyncSampler.h"
#include "Config.h"

AudioSyncSampler::AudioSyncSampler(uint8_t pin, float alpha, uint16_t thresh) :
    EMASampler(pin, 0, alpha),
    _pulseCount(0),
    _pulseStart(0),
    _thresh(thresh)
{
}

void AudioSyncSampler::begin()
{
    EMASampler::begin();
    _state = on();
    _lastPulseState = !_state;
    _lastPulseLength = 0;
}

bool AudioSyncSampler::check()
{
    EMASampler::update();
    _pulseCount++;
    if (_state != on()) {
        unsigned long pulseLength = _pulseCount - _pulseStart;
        bool valid = false;
        if (pulseLength <= AUDIO_SYNC_MAXLEN && pulseLength >= AUDIO_SYNC_MINLEN) {
            _lastPulseState = _state;
            _lastPulseLength = pulseLength;
            valid = true;
        }
        _state = on();
        _pulseStart = _pulseCount;
        return valid;
    }
    return false;
}

bool AudioSyncSampler::on()
{
    return average() <= _thresh;
}

