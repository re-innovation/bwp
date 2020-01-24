Modifictions to functionality, Jan 2020 (use solar-battery)
===========================================================

New version of system will not be powered by hand crank. Instead will be powered 
by solar/battery power system. The crank will only be used as a sensor to show 
that someone is operating the projector. The crank will be fitted with a magnet
and reed switch, which will be closed and opened repeatedly when the crank is 
turned. 

Changes to firmware:

* Should enter SleepMode when not active. This means
  - Arduino in power saving mode, use interrupts to wake up
  - DFPlayer Mini should be powered off while in sleep mode
  - Interrupts can come from either of the push buttons or a new crank sensor 
    switch
    - Question: are push button pins ones which support interrupts on the nano?

* Crank sensor switch shows the crank is being turned (reed switch) on pin 2 
  - If crank sensor triggers more than some threshold number of times per second, 
    system wakes into movie mode.

* NormalMode changes:
  - Plays one [long] audio file.
  - Advances projector at constant rate.
  - Continues until cranking sensor stops getting regular pulses, then enter 
    SleepMode

* Audio marks system will be removed from firmware.

* When the unit become inactive, Arduino should be put into SleepMode.
  - DFPlayer Mini should also be powered down when entering SleepMode

* Unit should also come out of sleep when buttons pressed to service
  DiagnosticMode. Stats should also be printed to serial port.

* Require fix for integer overflow bug when reading out minutes of use 
  statistic.

TO TEST
-------

FrameOffsetAdjust
Crank speed ajustment

DEPLOYMENT
----------

* Recommend pre-installing firmware on new Arduino Nanos:
  - desolder power LED
  - set fuses to allow graceful powerdown in case of battery drain

* Pre-load all SD cards with:
  - new sounds from `Projection_Unit_Software/audio`
  - tracks for all projectors (can then be selected in settings mode)


