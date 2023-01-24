#!/bin/bash
cd ..
cd build
cd src
tests=$(find /home/kirill/localProjects/OSlabs/lab3/test -name "*.txt")
make
count=1
echo "multithreading algorithm"
for i in ${tests}
do
    echo "-------------------------test $count-------------------------"
    ./main 4 < "$i"
    let "count += 1"
done
count=1
echo "base algorithm"
for i in ${tests}
do
    echo "-------------------------test $count-------------------------"
    ./qs 4 < "$i"
    let "count += 1"
done

