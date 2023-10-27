#!/bin/bash

for x in $(find dir -type f -perm /o+w); do
    ls -l $x | awk '{print $1, $NF}'
    sudo chmod o-w $x
    ls -l $x | awk '{print $1, $NF}'
done
