#!/bin/bash

for X in $*; do
    if test -f "$X"; then
        echo "$X e fisier"
    elif echo "$X" | grep -q -E "^[0-9]+$"; then
        echo "$X e numar natural"
    else
        echo "$X e altceva"
    fi
done
