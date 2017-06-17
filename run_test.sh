#!/bin/bash

if [ ! -d debug ]
then
    mkdir debug
fi
pushd debug

if [ ! -f CMakeCache.txt ]; then
    cmake -DCMAKE_BUILD_TYPE=Debug ../cpp
fi
make
if [ $? -eq 0 ]; then
    ./test/run_tests
else
    echo "Compilation failed"
fi
popd
