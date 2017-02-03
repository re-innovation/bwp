#include <Arduino.h>
#include <MutilaDebug.h>
#include "AudioMarkReader.h"
#include "Config.h"

#define DBV(...) {;}

#define DBVLN(...) {;}

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
    DBV(F("AMR avg="));
    DBV(average());
    DBV(F(" l="));
    DBV(_pulseCount-_pulseStart);
    bool state = getState();
    if (state != _lastPulseState) {
        _lastPulseState = state;
        if (state) {
            // rising edge - start of new white stripe
            DBVLN(F(" START"));
        } else {
            // falling edge - end of white stripe
            DBV(F(" END: "));
            uint32_t pulseLength = _pulseCount - _pulseStart;
            if (pulseLength >= AUDIO_SYNC_ZERO_MIN_LEN && pulseLength < AUDIO_SYNC_ONE_MIN_LEN) {
                appendBitToBuffer(0);
                DBVLN(0);
            } else if (pulseLength >= AUDIO_SYNC_ONE_MIN_LEN && pulseLength <= AUDIO_SYNC_ONE_MAX_LEN) {
                appendBitToBuffer(1);
                DBVLN(1);
            } else {
                DBVLN('?');
            }
        }
        _pulseStart = _pulseCount;
    } else {
        if (_pulseCount - _pulseStart > AUDIO_SYNC_ONE_MAX_LEN && _bufPtr > 0) {
            DBVLN(F(" TimeO"));
            resetBuffer();
        } else {
            DBV(state ? F(" 0") : F(" 1"));
            DBV(F(" WT "));
        }
    }
}

int AudioMarkReader::get()
{
#ifdef DEBUG
    DBV(F("buf \""));
    for(uint8_t i=0; i<AUDIO_SYNC_BITS; i++) {
        if (_bufPtr>i) {
            DBV(_buffer[i]);
        } else {
            DBV('_');
        }
    }
    DBV('"');
#endif
    if (_bufPtr < AUDIO_SYNC_BITS) {
        DBVLN('.');
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
        DBVLN(F(" ERR"));
        resetBuffer();
        return(AUDIO_SYNC_INVALID);
    } else if (correction > 0) {
        DBVLN(F(" CORRECT"));
        _buffer[correction-1] = !_buffer[correction-1];
    } else {
        DBVLN(F(" OK"));
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
    DBVLN(F("AudioMarkReader::resetBuffer"));
    memset(_buffer, 0, sizeof(uint8_t) * AUDIO_SYNC_BITS);
    _bufPtr = 0;
}


