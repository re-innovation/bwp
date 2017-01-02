#include <Arduino.h>
#include <MutilaDebug.h>
#include "AudioMarkReader.h"
#include "Config.h"

AudioMarkReader::AudioMarkReader(uint8_t pin, float alpha, uint16_t thresh) :
    EMASampler(pin, 0, alpha),
    _pulseCount(0),
    _pulseStart(0),
    _thresh(thresh)
{
}

void AudioMarkReader::begin()
{
    EMASampler::begin();
    _lastPulseState = getState();
    reset();
}

void AudioMarkReader::update()
{
    EMASampler::update();
    _pulseCount++;
    DB(F("AudioMarkReader::update count="));
    DB(_pulseCount);
    bool state = getState();
    bool change = state != _lastPulseState;
    uint16_t pulseLength = _pulseCount - _pulseStart;
    _lastPulseState = state;
    DB(F(" state="));
    DB(state);
    DB(F(" last="));
    DBLN(_lastPulseState);

    // Test for timeout
    if (pulseLength > AUDIO_SYNC_MAX_LEN && _bufPtr > 0){
        DBLN(F("AudioMarkReader::update timeout"));
        reset();
        return;
    }

    // If the state has changed, handle that
    if (change) {
        _pulseStart = _pulseCount;
        if (pulseLength <= AUDIO_SYNC_SHORT_LEN) {
            DB(F("AudioMarkReader::update short pulse"));
            addBit(0);
        } else if (pulseLength <= AUDIO_SYNC_MAX_LEN) {
            DB(F("AudioMarkReader::update long pulse"));
            addBit(1);
        }
    }
}

bool AudioMarkReader::addBit(bool bit)
{
    if (_bufPtr >= AUDIO_SYNC_BITS) {
        DBLN(F("AudioMarkReader::addBit too many bits"));
        reset();
        return false;
    } else {
        _buffer[_bufPtr++] = bit;
#ifdef DEBUG
        DB(F(", buffer now: "));
        for(uint8_t i=0; i<_bufPtr; i++) {
            DB(_buffer[i]);
        }
        DBLN(' ');
#endif
        return true;
    }
}

int AudioMarkReader::get()
{
    if (_bufPtr != AUDIO_SYNC_BITS) {
        return AUDIO_SYNC_INCOMPLETE;
    }
    uint16_t v = 0;
    DBLN(F("AudioMarkReader::get bits: "));
    for (uint8_t i=0; i<_bufPtr; i++) {
        v += _buffer[i] << i;
        DB(_buffer[i]);
    }
    DB(F(" = 0x"));
    DBLN(v);
    reset();
    // TODO: validation/error correction of message
    // if (invalid) {
    //      return AUDIO_SYNC_INVALID;
    // }
    return v;
}

void AudioMarkReader::reset()
{
    DBLN(F("AudioMarkReader::reset"));
    memset(_buffer, 0, sizeof(uint8_t) * AUDIO_SYNC_BITS);
    _bufPtr = 0;
}


