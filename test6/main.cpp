#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define AUDIO_SYNC_BITS 12

// These are global here, but when integrated into firmware will be data
// members of the AudioMarkReader class, or similar.
uint8_t _buffer[AUDIO_SYNC_BITS];
uint8_t _bufPtr = 0;

//! clear the audio mark code buffer
void resetBuffer()
{
    memset(_buffer, 0, sizeof(uint8_t) * AUDIO_SYNC_BITS);
    _bufPtr = 0;
}

//! Append a bit to the audio make buffer
//! \return true if the bit was appened, else false (i.e. if the buffer if full)
bool appendBitToBuffer(bool bit) 
{
    if (_bufPtr >=AUDIO_SYNC_BITS) {
        return false;
    } else {
        _buffer[_bufPtr++] = bit;
    }
}

//! Test bit position in buffer to tell if it a parity bit
//! \param bitPos the index of the bit in the buffer
//! \param bufSiz the maximum length of the buffer
//! \return true if the bit position is a partiy bit, else false
//!
//! Hamming codes use bits which are an integer power of 2 for parity
//! we add one because we're using zero-indexed array, not 1-indexed.
//! 
bool bitIsParityBit(uint8_t bitPos) {
    bitPos++;
    while (((bitPos % 2) == 0) && bitPos > 1) { 
        bitPos /= 2;
    }
    return (bitPos == 1);
}

//! Check a parity bit in a buffer containing a Hamming code
//! \param bitPos the position of the bit in the buffer (zero-indexed)
//! \return 1 if the bit is a hamming partiy bit, else 0
uint8_t hammingParity(uint8_t bitPos)
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

//! Decode the buffer
//! \return -1 if buffer is incomplete
//!         -2 on error (too many error bits)
//!         0-255 on successful decode of 12/8 bit hamming code
int decodeBuffer()
{
    uint8_t correction = 0;
    uint8_t bitValue = 1;
    for (uint8_t i=0; i<AUDIO_SYNC_BITS; i++) {
        if (bitIsParityBit(i)) {
            correction += bitValue * hammingParity(i);
            bitValue *= 2;
        }
        printf("BIT %2d %5s = %d, isParity=%d, parity=%d, correction=%d\n", 
                    i, 
                    i<_bufPtr ? "SET" : "unset", 
                    _buffer[i],
                    bitIsParityBit(i),
                    hammingParity(i),
                    correction);
    }
    if (correction >= AUDIO_SYNC_BITS) {
        // More than one error
        printf("ERROR - unfixable amount of errors\n");
        return(-2);
    } else if (correction > 0) {
        printf("Fixable error at bit at index %d\n", correction-1);
        _buffer[correction-1] = !_buffer[correction-1];
    } else {
        printf("No errors\n");
    }
    bitValue = 1;
    uint8_t value = 0;
    for (uint8_t i=0; i<AUDIO_SYNC_BITS; i++) {
        if (!bitIsParityBit(i)) {
            value += _buffer[i]*bitValue;
            bitValue *= 2;
        }
    }
    return value;
}

int main(int argc, char** argv)
{
    for (uint8_t i=1; i<argc; i++) {
        appendBitToBuffer(argv[i][0] == '0' ? 0 : 1);
    }
    int v = decodeBuffer();
    printf("value is %d\n", v);

    return 0;
}


