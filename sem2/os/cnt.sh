#!/bin/bash

for x in $(find); do
    if [[ -d $x ]]; then
        cnt=0;sum=0
        for y in $(find $x); do
            if echo $y | grep -q ".txt$" ; then 
                sum=$[sum+1]
            fi
            cnt=$[cnt+1]
        done
        echo $cnt $sum
    fi
done
