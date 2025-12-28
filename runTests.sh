#!/bin/bash

OUTPUT_FILE="test_results.txt"

make clean && make || exit 1

echo "Running 100 iterations. Please wait..."

(
for i in {1..100}; do
    echo "Iteration $i"
    ./bin/test || { echo "FAILED on iteration $i"; break; }
done
) > "$OUTPUT_FILE" 2>&1

if grep -q "FAILED" "$OUTPUT_FILE"; then
    echo "Error: A test failure occurred. Check $OUTPUT_FILE for details."
    exit 1
else
    echo "Success: All tests passed."
    rm $OUTPUT_FILE
    exit 0
fi