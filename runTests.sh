#!/bin/bash

make clean && make || exit 1

for i in {1..100}; do
    echo "Iteration $i"
    ./bin/test || { echo "Failed on iteration $i"; break; }
done