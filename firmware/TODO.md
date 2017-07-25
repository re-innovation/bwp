To Do
=====

We have problems because the film is slipping and the sensor position is difficult to fine-tune to
get good data.  The result is frequent mis-reads of the audio marks.  Probably more than 50% of the
time the reads are failing, which is a pity, because it was working so well with the prototype
hardware...

Anyhow, as a possible fix for this, I propose the following:

1. The firmware should know the sequence of marks - the constraint will be that the marks are in
   numeric order, with a known number of marks, set as a setting which can be set and stored in
   EEPROM.

2. On startup, the firmware waits until it gets a successful read, and then keeps track of the last
   mark read.  On getting a partial (but failed) read, it plays the next sample in sequence.

3. Subsequency successful reads explicitly set the mark counter so it is re-synced.

Risks
-----

1. No successful reads means we don't know where we are in the sequence


Options / queries
-----------------

* Should the sequence nmber we written to EEPROM on brownout? Yes means high EEPROM wear, no means
  must get a successful read before any audio played


