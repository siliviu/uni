#!/bin/bash

while read p; do
    s="$s,$p@scs.ubbcluj.ro"
done < test.txt

s=$(echo $s | sed 's/^,//')

echo $s
