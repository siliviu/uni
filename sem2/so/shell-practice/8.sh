#!/bin/bash

while read p; do
    size=$(echo $p | awk '{print $2}' | sed 's/M//')
    usage=$(echo $p | awk '{print $5}' | sed 's/%//')
    name=$(echo $p | awk '{print $NF}')
    if [[ $size -lt 1024 || $usage -ge 80 ]]; then
        echo $name
    fi
done < <(cat df.fake | tail -n +2)

