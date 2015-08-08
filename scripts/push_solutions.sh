#!/bin/bash

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}"  )" && pwd  )
PROBLEMS_DIR="$DIR/../problems"
BUILD_DIR="$DIR/../build"

for problem in $(ls $PROBLEMS_DIR/*.json); do
    ID=$(echo "${problem%.*}" | awk -F "_" '{print $2}')
    RESULT_FN="result_${ID}.json"
    $BUILD_DIR/icfpc/solver $problem $ID $RESULT_FN
    curl --user :TzEFNFCbeYwqpgcDPfz0xXuynPZkXdCvIFbGFe9X1y4= -X POST -H "Content-Type: application/json"  \
        --data-binary @$RESULT_FN https://davar.icfpcontest.org/teams/223/solutions
done
