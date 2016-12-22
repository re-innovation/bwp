#include <Arduino.h>
#include "AudioSyncSampler.h"

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
}

bool AudioSyncSampler::check()
{
    EMASampler::update();
    _pulseCount++;
    if (_state != on()) {
        Serial.print("State ");
        Serial.print(_state);
        Serial.print(" dur=");
        Serial.println(_pulseCount - _pulseStart);
        _state = on();
        _pulseStart = _pulseCount;
        return true;
    }
    return false;
}

bool AudioSyncSampler::on()
{
    return average() <= _thresh;
}

