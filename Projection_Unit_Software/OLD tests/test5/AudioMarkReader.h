#pragma once

#include <stdint.h>
#include <EMASampler.h>
#include "Config.h"

/*! \brief Detect and decode audio marks (with an optical sensor)
 * Marks are read by detecting a transistion of the sensor going from
 * one state to another.  The sensor provides an analog value.  A 
 * threshold is used to determine if the state has changed (with
 * some averaging done using the Exponential Moving Average method).
 *
 * Measurements are taken once per update() call, and the number of
 * update() calls since the last state transition recorded. This 
 * counter is used to determine the "length" of a state.  Short
 * periods between state transitions are interpretted as zeros, longer 
 * periods as a one. 
 *
 * Zeros and ones read in this manner are appended to a buffer until one
 * of the following conditions is true:
 *
 * -# The number of update() calls since the last state transition 
 *    exceeds some threshold. In this case the buffer is resetBuffer.
 * -# The buffer is full with 9 bits of information in it. The values
 *    in the buffer consitiute a valid message, which is read using
 *    the getTrack() method.
 * -# The buffer is full with 9 bits of information in it. The values
 *    in the buffer constitute an invalid message.  In this case
 *    the 
 * If the length between state transitions is 
 * longer than some threshold, 
 */

class AudioMarkReader : public EMASampler {
public:
    /*! Constructor
     * \param pin the analog pin the audio mark sensor is attached to.
     * \param alpha EMA sample longevity, 0.0 - 1.0, where larger values
     *        ages values more rapidly.
     * \param thresh the mid-point of the mark/no mark sensor output
     */
    AudioMarkReader(uint8_t pin, float alpha, uint16_t thresh);

    /*! Initialize
     * Initializes pin modes and such, might be called from setup() if
     * an AudioMarkReader is used directly in sketch, or in the begin()
     * of another class if the AudioMarkReader is encapsulated elsewhere.
     */
    void begin();

    /*! Update sensor
     * 1. Checks the state of the sensor and update the moving average
     *    as necessary
     * 2. If the state has changed since the last update():
     *    2.1. And the buffer is not full
     *         2.1.1. And the length of the previous state was short, 
     *                append 0 to but buffer.
     *         2.1.2. And the length of the previous state was long,
     *                append 1 to the buffer.
     * 3. If the state has not changed since the last update() and the
     *    length of the last state is over some threshold, resetBuffer the 
     *    buffer and update counter.
     *
     */
    void update();

    /*! Decode the buffer
     * \return AUDIO_SYNC_INCOMPLETE if buffer is incomplete
     *         AUDIO_SYNC_INVALID on error (too many error bits)
     *         0-255 on successful decode of 12/8 bit hamming code
     */
    int get();

private:
    bool getState() { return average() <= _thresh; }
    /*! Reset the buffer */
    void resetBuffer();
    /*! Append a bit to the buffer of bits read recently
     * \return true if the bit was appened, else false (i.e. if the buffer if full)
     */
    bool appendBitToBuffer(bool bit);
    /*! Test if bit position in buffer is a hamming parity bit
     * \param bitPos the index of the bit in the buffer
     * \return true if the bit position is a partiy bit, else false
     */ 
    bool bitIsParityBit(uint8_t bitPos);
    /*! Calculate Hamming parity for a specified bit in the buffer
     * \param bitPos the position of the bit in the buffer (zero-indexed)
     * \return 0 if the bit is not a hamming partiy bit, or the calculate 
     *         Hamming partity value of the bit if it is a Hamming
     *         parity bit (either 0 or 1)
     */
    uint8_t hammingParity(uint8_t bitPos);

    /// Data members
    uint32_t _pulseCount;               //! How many times update() has been called which should be how many stepper steps have
    uint32_t _pulseStart;               //! Measured in stepper steps, not millis
    uint16_t _thresh;                   //! Sensor value mid point between dark and light
    bool _lastPulseState;               //! State after last update()
    uint8_t _buffer[AUDIO_SYNC_BITS];   //! Accumulated bits read so far
    uint8_t _bufPtr;                    //! Pointer into buffer
    bool _partialReadFlag;              //! Flag to say we had an aborted read (picked up by get())

};

