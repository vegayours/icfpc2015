#!/bin/bash

PROBLEM_START=0
PROBLEM_END=23

PROBLEMS_DIR="../problems"

for i in $(seq $PROBLEM_START $PROBLEM_END); do
    FILENAME="problem_${i}.json"
    wget "http://icfpcontest.org/problems/$FILENAME" -O "$PROBLEMS_DIR/$FILENAME"
done
