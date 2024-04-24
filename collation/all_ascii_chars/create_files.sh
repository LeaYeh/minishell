#!/bin/bash

for i in {0..255}; do
    touch "$(printf "\\$(printf '%03o' $i)")"
done
