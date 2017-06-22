#!/usr/bin/perl

$MAX = 1024;
$WIDTH = 150;

while(<>) {
    if (/sv=(\d+)/) {
        $p = $1 / $MAX;
        $l = int($WIDTH * $p);
        printf("SV: %s %d\n", '#' x $l, $1);
    } elsif (/(close|open)Shutter/) {
        print;
    }
}

