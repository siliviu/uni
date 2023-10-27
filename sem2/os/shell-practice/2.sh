#!/bin/bash

CNT=0

for x in $(find dir -type f -name "*.c"); do
    if [ $(wc -l $x | awk '{print $1}') -gt 500 ]; then
        CNT=$[CNT+1]
        echo $x
    fi
    if [ $CNT -eq 2 ]; then
        break
    fi
done
