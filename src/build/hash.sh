#!/bin/bash

shopt -s globstar

cd $BOOKPATH/src

for f in **/*.?pp; do
    hash=$(cpp -dD -P -fpreprocessed 2> /dev/null < $f \
        | tr -d '[:space:]' | md5sum | cut -c-6)
    echo "$hash $f"
done
