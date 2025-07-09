#!/bin/bash

for x in $(find -name "*.sh"); do
    cat $x | awk 'NF!=0 && $0 !~ /^#/ {print $0}'
    
done
