# Hamming code test (Linux)

Quick test of Hamming decoding functions in a stand-alone program which should build on any modern *nix system with gcc/C++ installed.

Goals:

1.  Decode sequences of 0's and 1's from a buffer
2.  Correct / error detect with Hamming code 8/12 method
3.  Endian-agnostic 

## Building

Running ''make test'' will build the program and run some tests (output should be manually reviewed).

