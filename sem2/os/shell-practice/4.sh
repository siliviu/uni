#!/bin/bash

for x in $(find testdir);do
    if [[ -L $x && ! -e $x ]] ; then
        echo $x
    fi
done
