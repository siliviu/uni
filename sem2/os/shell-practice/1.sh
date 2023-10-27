#!/bin/bash

for x in $(awk '{print $1}' who.fake); do
    echo $x $(awk '$1 ~ '/^$x/' {cnt++} END{print cnt}' ps.fake)
done
