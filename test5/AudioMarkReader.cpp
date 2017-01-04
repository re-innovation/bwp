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
    resetBuffer();
}

void AudioMarkReader::update()
{
    EMASampler::update();
    _pulseCount++;
    DB(F("AudioMarkReader::update count="));
    DB(_pulseCount);
    DB(F(" len="));
    DB(_pulseCount-_pulseStart);
    bool state = getState();
    if (state != _lastPulseState) {
        _lastPulseState = state;
        if (state) {
            // rising edge - start of new white stripe
            DBLN(F(" start stripe"));
        } else {
            // falling edge - end of white stripe
            DB(F(" end stripe: "));
            uint32_t pulseLength = _pulseCount - _pulseStart;
            if (pulseLength >= AUDIO_SYNC_ZERO_MIN_LEN && pulseLength < AUDIO_SYNC_ONE_MIN_LEN) {
                appendBitToBuffer(0);
                DBLN(0);
            } else if (pulseLength >= AUDIO_SYNC_ONE_MIN_LEN && pulseLength <= AUDIO_SYNC_ONE_MAX_LEN) {
                appendBitToBuffer(1);
                DBLN(1);
            } else {
                DBLN('?');
            }
        }
        _pulseStart = _pulseCount;
    } else {
        if (_pulseCount - _pulseStart > AUDIO_SYNC_ONE_MAX_LEN && _bufPtr > 0) {
            DBLN(F(" timeout"));
            resetBuffer();
        } else {
            DBLN(F(" dark wait"));
        }
    }
}

int AudioMarkReader::get()
{
#ifdef DEBUG
    DB(F("AudioMarkReader::get buf \""));
    for(uint8_t i=0; i<AUDIO_SYNC_BITS; i++) {
        if (_bufPtr>i) 
            DB(_buffer[i]);
        else
            DB('_');
    }
    DB('"');
#endif
    if (_bufPtr < AUDIO_SYNC_BITS) {
        DBLN(F(" incomplete"));
        return AUDIO_SYNC_INCOMPLETE;
    }
    uint8_t correction = 0;
    uint8_t bitValue = 1;
    for (uint8_t i=0; i<AUDIO_SYNC_BITS; i++) {
        if (bitIsParityBit(i)) {
            correction += bitValue * hammingParity(i);
            bitValue *= 2;
        }
    }
    if (correction >= AUDIO_SYNC_BITS) {
        // More than one error
        DBLN(F("AudioMarkReader::get ERROR"));
        resetBuffer();
        return(AUDIO_SYNC_INVALID);
    } else if (correction > 0) {
        DBLN(F("AudioMarkReader::get CORRECTION"));
        _buffer[correction-1] = !_buffer[correction-1];
    } else {
        DBLN(F("AudioMarkReader::get OK"));
    }
    // Extract the encoded value
    bitValue = 1;
    uint8_t value = 0;
    for (uint8_t i=0; i<AUDIO_SYNC_BITS; i++) {
        if (!bitIsParityBit(i)) {
            value += _buffer[i]*bitValue;
            bitValue *= 2;
        }
    }
    resetBuffer();
    return value;
}

bool AudioMarkReader::appendBitToBuffer(bool bit) 
{
    if (_bufPtr >=AUDIO_SYNC_BITS) {
        return false;
    } else {
        _buffer[_bufPtr++] = bit;
    }
}

bool AudioMarkReader::bitIsParityBit(uint8_t bitPos) 
{
    bitPos++;
    while (((bitPos % 2) == 0) && bitPos > 1) { 
        bitPos /= 2;
    }
    return (bitPos == 1);
}

uint8_t AudioMarkReader::hammingParity(uint8_t bitPos)
{   
    // don't worry about non-parity bits...
    if (!bitIsParityBit(bitPos)) {
        return 0;
    }

    // Iterate over bits and calulate parity, starting at our parity bit
    uint8_t parity = 0;
    uint8_t left = bitPos+1;
    bool check = true;
    for (uint8_t i=bitPos; i<AUDIO_SYNC_BITS; i++) {
        if (left == 0) {
            left = bitPos+1;
            check = !check;
        }
        if (check) {
            parity += _buffer[i];
        }
        left--;
    }
    return parity % 2;
}

void AudioMarkReader::resetBuffer()
{
    DBLN(F("AudioMarkReader::resetBuffer"));
    memset(_buffer, 0, sizeof(uint8_t) * AUDIO_SYNC_BITS);
    _bufPtr = 0;
}


