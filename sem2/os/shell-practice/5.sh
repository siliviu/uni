#!/bin/bash

if [ $# -eq 0 ]; then
   echo Not enough arguments!
    exit
fi

while true; do
    ps > temp.txt
    while read p; do
         for x in $*; do
            if [ "$x" == "$(echo $p | awk '{print $NF}')" ]; then
               echo $p is bad
               kill $(echo $p | awk '{print $1}')
               break
           fi        
         done
     done < temp.txt
done
