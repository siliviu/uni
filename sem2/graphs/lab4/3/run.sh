#!/bin/bash

for i in {1..5}; do
    ./p3 $i-in.txt $i-ok.txt
    diff -w $i-out.txt $i-ok.txt 
done