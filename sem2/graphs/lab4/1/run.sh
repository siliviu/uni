#!/bin/bash

for i in {1..9}; do
    ./p1 $i-in.txt $i-ok.txt
    diff -w $i-out.txt $i-ok.txt 
done
