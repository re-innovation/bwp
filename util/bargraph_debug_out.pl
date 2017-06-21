#!/usr/bin/perl

$MAX = 1000;
$WIDTH = 150;

while(<>) {
    if (/avg=(\d+\.\d+) .*l=(\d+) .*buf (\"............\")/) {
        $p = $1 / $MAX;
        $l = int($WIDTH * $p);
        printf("l=%5d %s %s %5.2f\n", $2, $3, '#' x $l, $1);
    }
}

