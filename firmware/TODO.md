To Do
=====

-   Frame offset - trigger n half-steps after detecting frame hole
    -   Load value from EEPROM at startup (use a setting object)
-   Brownout control 
    -   save runtime / usage count to EEPROM (use a setting object)
        -   do not increment usage count if already saved this run
-   Volume setting mode: 
    -   investigate control of headphone output, otherwise:
    -   volume in hardware
-   Modes:
    -   Manual feed mode: use different speed from projector more
-   Metrics read-out:
    -   Write into EEPROM:
        -   Number of uses
        -   Total duration
        -   Audio readout of numbers...
-   Fix: DEBUG disables audio for some reason
-   Make Mp3Player inherit from DFPReader so we can call members directly - saves a little memory

Testing
=======

-   With new prototype:
    -   Levels:
        -   Graph / select levels for frame sensor
        -   Graph / select levels for audio sensor
    -   Investigate frame skips

Done
====

-   Frame offset - trigger n half-steps after detecting frame hole
    -   Prototype use Config.h value, then: [done]
-   Brownout control 
    -   reset audio [done]
    -   stop feed [done]
-   Manual feed mode [done]
-   Volume setting mode [done]
