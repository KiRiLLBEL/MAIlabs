#!/bin/bash
cd ..
cd build
make
cd src
echo "> Tests first program"
./main1 1 10 0.0001
./main1 1 1 0.01
./main1 1 323 0.00001
./main1 2 3
./main1 2 5
./main1 2 10
echo "> Tests second program"
./main2 1 10 0.0001
./main2 1 1 0.01
./main2 2 5
./main2 2 10
./main2 0 1 10 0.0001
./main2 0 1 1 0.01
./main2 0 2 3
./main2 0 2 7