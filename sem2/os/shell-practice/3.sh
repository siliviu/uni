#!/bin/bash

for x in $(find dir -type f -name "*.log"); do
    cat $x | sort > temp
    mv temp $x
done
