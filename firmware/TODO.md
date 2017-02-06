To Do
=====

High Priority (while having access to prototype)
------------------------------------------------

-   Investigate frame sync skips
    -   trigger n half-steps after detecting frame hole
-   Audiomark reading fails to process last bit
-   Audio doesn't work unless MUTILADEBUG is turned on
-   Implement EEPROM save / load
-   Implement metrics

Lower Priority (can be done w/o prototype)
------------------------------------------

-   Metrics read-out:
    -   Write into EEPROM:
        -   Number of uses
        -   Total duration
        -   Audio readout of numbers...
-   Save to EEPROM on setting changes
-   Modes:
    -   Manual feed mode: use different speed from projector more
-   Mp3 only works in MUTILADEBUG mode, or rarely with no debug...
-   12th 0 or 1 is not appending to audio code!

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
-   Make Mp3Player inherit from DFPReader so we can call members directly - saves a little memory
