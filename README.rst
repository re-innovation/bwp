===
BWP
===

This is the code and the design files for a low power LED projector
unit which utilises real film.  It is quite complex and probably best
explained via this link and video:

https://www.re-innovation.co.uk/portfolio/kinetiscopes-a-lost-paradise/

This repository has the full code (done by Matthew Mouse Gates) and the
full design files (done by Matthew Little).

The desgin files have been produced using Corel Draw, but have been also
saved as .dxf and .svg files.


*********
Operation
*********

When idle, the system will be in SleepMode. SleepMode ends when the crank 
is turned, and the system will enter WakeupMode

WakeupMode will monitor SW1 and SW2 and the crank speed:
- If the crank speed drops below the crank speed setting, WakeupMode will
  end and the system will enter SleepMode
- If SW1 or SW2 is pressed while in WakeupMode, the system will enter
  DiagnosticMode
- If the crank speed remains above the crank speed setting, and neither
  button is pressed for 2 seconds (set by WAKEUP_MS compile-time option in
  Config.h), the system will enter NormalMode

In NormalMode, the system will rnu the projector and play the track 
number stored in the track selection setting. If the track ends, it will
be restarted. NormalMode will continue until the crank speed drops below
the crank speed setting, at which point the system will enter TiredMode.

In TiredMode, the projector will stop, and audio will slowly fade out.
- If the crank speed raised above the crank speed setting, the system will
  re-enter NormalMode
- If the crank speed remains below the crank speed setting for 2 seconds
  (set by TIRED_MS in Config.h compile-time option in Config.h), TiredMode
  will end and the system will enter SleepMode

In DiagnosticMode, the system allows configuration of various settings 
and review of runtime statitics. It is not necessary to turn the crank
while in DiagnosticMode.
- Pressing SW1 cycles through the various options. Pressing SW2 performs
  and option-specfic operation, e.g. changing the volume level when the
  volume setting option is active.
- Options:
    - Volume adjust (SW2 cycles through volume levels 1-30)
    - Track select (SW2 cycles through tracks 1-10)
    - Manual feed (SW2 advances the film)
    - Frame sync (SW2 cycles through offset value 1-25)
    - Crank speed (SW cycles through speeds 10-30)
    - Statistic - read out number of uses since installation
    - Statistic - read out total runtime since installation
    - Statistic - read out avg seconds per use 

Pressing SW1 from the last option will put the system back into SleepMode.

Note: to enter DiagnosticMode, the following procedure is recommended:

1. Press and hold SW2
2. Turn the crank one full turn
3. Release SW2 and wait for a second or two

****************
Heartbeat States
****************

When ENABLE_HEARTBEAT is defined at compile time (in Config.h), the 
heartbeat LED will flash to indicate the state of the system:

- Quick (25ms on, 25ms off) - the system is in WakeupMode or TiredMode
- Normal (50ms on, 500ms off) - the projector is in NormalMode
- Slow (1000ms on, 1000ms off) - the system is in DiagnosticMode

It's a good idea to disable this for solar batter systems because the
heartbeat LED can stay in an ON state when the Arduino enters deep sleep,
which may drain battery power.

**************
Pre-requisites
**************

* Install the Arduino IDE 1.6.6 or later:
    * Windows & Mac users may find a download link here: 
      https://www.arduino.cc/en/Main/Software
    * Major Linux distros carry it in their software repositories, or the link 
      above may be used
* Install *AccelStepper* library with the Arduino IDE library manager
* Install *Mutila* library v1.2.0 through the Arduino IDE library manager

******************************
Building Using the Arduino IDE
******************************

This method is preferred on Windows and for casual users who just want
to build and use the project.

* Open Arduino IDE 
* Open Projection_Unit_Software/firmware/firmware.ino
* Set the board to "Arduino Nano" (under the Tools -> Board menu) 
* Connect Nano 
* Click the Upload button on the tool bar

*******************
Using make on Linux
*******************

This alternative build system may also be used. It is an alternative to
using the Arduino IDE and may be preferred by some users.

* Install the Arduino-Makefile system: 
  https://github.com/sudar/Arduino-Makefile
* Edit the arduino.mk file and set the include line to point at where you 
  installed Arduino-Makefile (or set the ARDUINO_MAKEFILE environment variable)
* In a shell, from the *firmware* directory, use the command "make upload" to 
  build and install the code


********************************
Installation in Projector System
********************************

The Arduino Nano fuses should be reset so the brownout voltage is changed from 
the low 2.7V value to the 4.7V setting (prevents hanging problems).

New SD cards should have everything from the Projection_Unit_Software/audio 
directory copied into them, and have a copy of all audio tracks put on them 
with numerical ID 0001-0010. The track may be selected as a setting from 
Diagnostic Mode.


