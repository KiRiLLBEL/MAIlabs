#!/bin/bash
cd ..
cd build
cd src
tests=$(find /home/kirill/localProjects/OSlabs/lab6/test -name "*.txt")
make
count=1
for i in ${tests}
do
    echo "-------------------------test $count-------------------------"
    ./client < "$i"
    let "count += 1"
done
