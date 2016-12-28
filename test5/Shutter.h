#pragma once

class Shutter_ {
public:
    Shutter_();

    /*! Initialize
     * Call from setup() to set pinModes and such
     */
    void begin();

    /*! Open the shutter
     * i.e. turn on the light
     */
    void open();

    /*! Close the shutter
     * i.e. turn off the light
     */
    void close();

};

extern Shutter_ Shutter;

