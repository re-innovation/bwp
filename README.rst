===
BWP
===

********
Controls
********

SW1 cycles through modes as follows:

- Setup: manual feed (SW2 feeds film)
- Setup: frame offset adjustment (SW2 adjusts the frame offset)
- Setup: volume adjustment (SW2 adjusts the volume)
- Setup: number of uses (readout)
- Setup: total runtime (readout)
- Setup: average runtime (readout)
- Normal Mode

****************
Heartbeat States
****************

The indicator LED is used to convey the state of the system by flashing one of the following sequences:

- Normal (50ms on, 500ms off) - the projector is running
- Slow (1000ms on, 150ms off) - the system has browned out, but still running
- Quick (25ms on, 25ms off) - the system is in configuration mode
- Slowest (1000ms on, 1000ms off) - the system has just powered up, but not exited brownout mode yet

**************
Pre-requisites
**************

* Install the Arduino IDE 1.6.6 or later:
    * Windows & Mac users may find a download link here: https://www.arduino.cc/en/Main/Software
    * Major Linux distros carry it in their software repositories, or the link above may be used
* Install *AccelStepper* library.
* Install *Mutila* library, link: https://github.com/matthewg42/Mutila 

******************************
Building Using the Arduino IDE
******************************

This method is preferred on Windows and for casual users who just want to build and use the project.

* Open Arduino IDE 
* Open firmware/firmware.ino
* Set the board to "Arduino Nano" (under the Tools -> Board menu)
* Connect Nano 
* Click the Upload button on the tool bar

*******************
Using make on Linux
*******************

This alternative build system may also be used. It is an alternative to using the Arduino IDE and may be preferred by some users. 

* Install the Arduino-Makefile system: https://github.com/sudar/Arduino-Makefile
* Edit the arduino.mk file and set the include line to point at where you installed Arduino-Makefile (or set the ARDUINO_MAKEFILE environment variable)
* In a shell, from the *firmware* directory, use the command "make upload" to build and install the code


****************
Uploading Sounds
****************

Sounds must be within a folder called "mp3" on the SD card.
Sounds are numbers 0001 to 9999.
