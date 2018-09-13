#!/usr/bin/perl

$MAX = 1024;
$WIDTH = 150;

while(<>) {
    if (/sv=(\d+).*diff=(\d+)/) {
        $p = $1 / $MAX;
        $l = int($WIDTH * $p);
        $pd = $2 / $MAX;
        $ld = int($WIDTH * $pd);
        printf("SV: %s %d\n", '#' x $l,  $1);
        #printf("DI: %s %d\n", "'" x $ld, $2);
    } elsif (/openShutter/) {
        print;
    }
}

