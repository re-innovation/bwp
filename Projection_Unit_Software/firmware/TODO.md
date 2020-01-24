To Do
=====

New version of system will not be powered by hand crank. Instead will be powered 
by solar/battery power system. 

Changes to firmware:

* Should enter sleep mode when not active. This means
  - Arduno in power saving mode, use interrupts to wake up
  - DFPlayer Mini should be powered off while in sleep mode
  - Interrupts can come from either of the push buttons or a new crank sensor switch

* Crank sensor switch shows the crank is being turned (reed switch) on pin 2 (?)
  - If crank sensor triggers more than some threshold number of times per second, 
    system wakes into movie mode.

* MovieMode
  - Plays one [long] audio file.
  - Advances projector at constant rate.
  - Continues until cranking sensor stops getting regular pulses.

* Audio marks system will be removed from firmware.

* When the unit become inactive, Arduino should be put into sleep mode.
  - DFPlayer Mini should also be powered down when entering sleep mode

* Unit should also come out of sleep when buttons pressed to service
  diagnostic modes. Stats should also be printed to serial port.

* Require fix for integer overflow bug when reading out minutes of use 
  statistic.

